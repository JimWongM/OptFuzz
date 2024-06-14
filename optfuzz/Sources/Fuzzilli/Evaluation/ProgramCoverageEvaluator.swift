// Copyright 2019 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

import Foundation
import libcoverage

/// Represents a set of newly discovered CFG edges in the target program.
public class CovEdgeSet: ProgramAspects {
    private var numEdges: UInt32
    fileprivate var edges: UnsafeMutablePointer<UInt32>?

    init(edges: UnsafeMutablePointer<UInt32>?, numEdges: UInt32) {
        self.numEdges = numEdges
        self.edges = edges
        super.init(outcome: .succeeded)
    }

    deinit {
        free(edges)
    }

    /// The number of aspects is simply the number of newly discovered coverage edges.
    public override var count: UInt32 {
        return numEdges
    }

    public override var description: String {
        return "new coverage: \(count) newly discovered edge\(count > 1 ? "s" : "") in the CFG of the target"
    }

    /// Returns an array of all the newly discovered edges of this CovEdgeSet.
    ///
    /// This adds additional copies, but is only hit when new programs are added to the corpus
    /// It is used by corpus schedulers such as MarkovCorpus that require knowledge of which samples trigger which edges
    public func getEdges() -> [UInt32] {
        return Array(UnsafeBufferPointer(start: edges, count: Int(count)))
    }

    public static func == (lhsEdges: CovEdgeSet, rhsEdges: CovEdgeSet) -> Bool {
        if lhsEdges.outcome != rhsEdges.outcome { return false }
        if lhsEdges.count != rhsEdges.count { return false }
        for i in 0..<Int(lhsEdges.count) {
            if lhsEdges.edges![i] != rhsEdges.edges![i] {
                return false
            }
        }
        return true
    }

    // Updates the internal state to match the provided collection
    fileprivate func setEdges<T: Collection>(_ collection: T) where T.Element == UInt32 {
        precondition(collection.count <= self.count)
        self.numEdges = UInt32(collection.count)
        for (i, edge) in collection.enumerated() {
            self.edges![i] = edge
        }
    }
}

public class CovPathSet: ProgramAspects {
    public var phaseID: UInt32
    private var numPath: UInt32
    fileprivate var path: UnsafeMutablePointer<UInt32>?

    init(path: UnsafeMutablePointer<UInt32>?, numPath: UInt32, phaseID: UInt32) {
        self.phaseID = phaseID
        self.numPath = numPath
        self.path = path
        super.init(outcome: .succeeded)
    }

    deinit {
        free(path)
    }

    /// The number of aspects is simply the number of newly discovered coverage paths.
    public override var count: UInt32 {
        return numPath
    }

    public override var description: String {
        return "new path: \(count) newly discovered path\(count > 1 ? "s" : "") in the CFG of the target"
    }

    /// Returns an array of all the newly discovered edges of this CovEdgeSet.
    ///
    /// This adds additional copies, but is only hit when new programs are added to the corpus
    /// It is used by corpus schedulers such as MarkovCorpus that require knowledge of which samples trigger which edges
    public func getPath() -> [UInt32] {
        return Array(UnsafeBufferPointer(start: path, count: Int(count)))
    }

    public static func == (lhsEdges: CovPathSet, rhsEdges: CovPathSet) -> Bool {
        if lhsEdges.outcome != rhsEdges.outcome { return false }
        if lhsEdges.count != rhsEdges.count { return false }
        if lhsEdges.phaseID != rhsEdges.phaseID { return false }
        for i in 0..<Int(lhsEdges.count) {
            if lhsEdges.path![i] != rhsEdges.path![i] {
                return false
            }
        }
        return true
    }
}


public class PhaseAspects: ProgramAspects {
    public var phase_index: UInt32

    init(phase_index: UInt32) {
        self.phase_index = phase_index
        super.init(outcome: .succeeded)
    }


    /// The number of aspects is simply the number of newly discovered coverage edges.
    public override var count: UInt32 {
        return 1
    }

    public override var description: String {
        //return "new coverage: \(count) newly discovered edge\(count > 1 ? "s" : "") in the CFG of the target"
        return "phase evaluation"
    }
}

public class ProgramCoverageEvaluator: ComponentBase, ProgramEvaluator {
    /// Counts the number of instances. Used to create unique shared memory regions in every instance.
    private static var instances = 0

    /// Whether per-edge hit counts should be tracked as well.
    /// These are expensive to compute, so this need to be enabled explicitly.
    private var shouldTrackEdgeCounts : Bool

    /// Keep track of how often an edge has been reset. Frequently set/cleared edges will be ignored
    private var resetCounts : [UInt32:UInt64] = [:]

    /// How often an edge may be reset at most before it is considered non-deterministic.
    /// In that case, the edge is marked as found, but will not be considered an aspect of any program.
    private let maxResetCount : UInt64 = 1000

    /// The current edge coverage percentage.
    public var currentScore: Double {
        return Double(context.found_edges) / Double(context.num_edges)
    }

    /// Context for the C library.
    private var context = libcoverage.cov_context()

    public init(runner: ScriptRunner) {
        // In order to keep clean abstractions, any corpus scheduler requiring edge counting
        // needs to call EnableEdgeTracking(), via downcasting of ProgramEvaluator
        self.shouldTrackEdgeCounts = false

        super.init(name: "Coverage")

        let id = ProgramCoverageEvaluator.instances
        ProgramCoverageEvaluator.instances += 1

        context.id = Int32(id)
        guard libcoverage.cov_initialize(&context) == 0 else {
            fatalError("Could not initialize libcoverage")
        }
#if os(Windows)
        runner.setEnvironmentVariable("SHM_ID", to: "shm_id_\(GetCurrentProcessId())_\(id)")
#else
        runner.setEnvironmentVariable("SHM_ID", to: "shm_id_\(getpid())_\(id)")
        runner.setEnvironmentVariable("SHM_ID2", to: "shm_id_\(getpid())_\(id)_200")

        for i in 0..<58 {
            runner.setEnvironmentVariable("SHM_ID0\(i)", to: "shm_id_\(getpid())_\(id)_\(i)")
        }
            
        
#endif

    }

    public func enableEdgeTracking() {
        assert(!isInitialized) // This should only be called prior to initialization
        shouldTrackEdgeCounts = true
    }


    public func getEdgeHitCounts() -> [UInt32] {
        var edgeCounts = libcoverage.edge_counts()
        let result = libcoverage.cov_get_edge_counts(&context, &edgeCounts)
        if result == -1 {
            logger.error("Error retrifying smallest hit count edges")
            return []
        }
        var edgeArray = Array(UnsafeBufferPointer(start: edgeCounts.edge_hit_count, count: Int(edgeCounts.count)))

        // Clear all edges that have hit their reset limits
        for (edge, count) in resetCounts {
            if count >= maxResetCount {
                edgeArray[Int(edge)] = 0
            }
        }

        return edgeArray
    }

    public func getPathHitCounts(_ index: UInt32) -> [UInt32] {
        var pathCounts = libcoverage.edge_counts()
        let result = libcoverage.cov_get_path_counts(&context, &pathCounts, index)
        if result == -1 {
            logger.error("Error retrifying smallest hit count edges")
            return []
        }
        var edgeArray = Array(UnsafeBufferPointer(start: pathCounts.edge_hit_count, count: Int(pathCounts.count)))

        return edgeArray
    }

    override func initialize() {
        // Must clear the shared memory bitmap before every execution
        fuzzer.registerEventListener(for: fuzzer.events.PreExecute) { execution in
            libcoverage.cov_clear_bitmap(&self.context)
            //libcoverage.pass_clear_bitmap(&self.context)
        }
        
        fuzzer.registerEventListener(for: fuzzer.events.myPreExecute) { execution in
            //libcoverage.pass_clear_bitmap(&self.context)
        }

        // Unlink the shared memory regions on shutdown
        fuzzer.registerEventListener(for: fuzzer.events.Shutdown) { _ in
            libcoverage.cov_shutdown(&self.context)
        }

        let _ = fuzzer.execute(Program())
        libcoverage.cov_finish_initialization(&context, shouldTrackEdgeCounts ? 1 : 0)
        logger.info("Initialized, \(context.num_edges) edges")
        
        fuzzer.registerEventListener(for: fuzzer.events.myPostExecute) { program in

            var passFlags = libcoverage.pass_data2()
            libcoverage.pass_compute_bitmap(&self.context, &passFlags)
            let passArray = Array(UnsafeBufferPointer(start: passFlags.pass_flags, count: Int(30)))
                    
            if let stats = Statistics.instance(for: self.fuzzer) {
                stats.update(passArray: passArray)
            }
                    
        }
    }

    public func evaluate(_ execution: Execution, _ program: Program) -> ProgramAspects? {
        assert(execution.outcome == .succeeded)
        var newEdgeSet = libcoverage.edge_set()
        let result = libcoverage.cov_evaluate(&context, &newEdgeSet)
        guard result != -1 else {
            logger.error("Could not evaluate sample")
            return nil
        }
        /*
        var newEdgeSet18 = libcoverage.edge_set()
        libcoverage.cov_evaluate18(&context, &newEdgeSet18)
        fuzzer.dispatchEvent(fuzzer.events.AddBitmap18_total, data: newEdgeSet18.count)
        */
        //var resultArray:[UInt32] = []
        for i in 0..<58 {
            var newEdgeSet18 = libcoverage.edge_set()
            let result2 = libcoverage.cov_evaluate2(&context, &newEdgeSet18, UInt32(i))
            //resultArray.append(newEdgeSet18.count)
            if i >= 29 && result2 == 1 {
                let tempValue = i - 29
                var tempAspect = CovPathSet(path: newEdgeSet18.edge_indices, numPath: newEdgeSet18.count, phaseID: UInt32(tempValue))
                //self.fuzzer.corpus.addMyProgram(program, tempAspect)
                

                self.fuzzer.fuzzGroup.enter()
                self.fuzzer.minimizer.myMinimize(program, withAspects: tempAspect){ minimizedProgram in
                    self.fuzzer.fuzzGroup.leave()
                    //print("minimized")
                    self.fuzzer.corpus.addMyProgram(minimizedProgram, tempAspect)
                }
                
            }
        }

        //fuzzer.dispatchEvent(fuzzer.events.AddBitmap_total, data: resultArray)

    
        if result == 1 {
            /*
            fuzzer.dispatchEvent(fuzzer.events.AddBitmap3_hit, data: newEdgeSet3.count)
            fuzzer.dispatchEvent(fuzzer.events.AddBitmap6_hit, data: newEdgeSet6.count)
            fuzzer.dispatchEvent(fuzzer.events.AddBitmap9_hit, data: newEdgeSet9.count)
            fuzzer.dispatchEvent(fuzzer.events.AddBitmap12_hit, data: newEdgeSet12.count)
            fuzzer.dispatchEvent(fuzzer.events.AddBitmap15_hit, data: newEdgeSet15.count)
            fuzzer.dispatchEvent(fuzzer.events.AddBitmap18_hit, data: newEdgeSet18.count)
            */
            //fuzzer.dispatchEvent(fuzzer.events.AddBitmap_hit, data: resultArray)
            return CovEdgeSet(edges: newEdgeSet.edge_indices, numEdges: newEdgeSet.count)
        } else {
            assert(newEdgeSet.edge_indices == nil && newEdgeSet.count == 0)
            return nil
        }
    }

    public func evaluateCrash(_ execution: Execution) -> ProgramAspects? {
        assert(execution.outcome.isCrash())
        let result = libcoverage.cov_evaluate_crash(&context)
        guard result != -1 else {
            logger.error("Could not evaluate crash")
            return nil
        }

        if result == 1 {
            // For minimization of crashes we only care about the outcome, not the edges covered.
            return ProgramAspects(outcome: execution.outcome)
        } else {
            return nil
        }
    }

    public func hasAspects(_ execution: Execution, _ aspects: ProgramAspects) -> Bool {
        guard execution.outcome == aspects.outcome else {
            return false
        }

        if execution.outcome.isCrash() {
            // For crashes, we don't care about the edges that were triggered, just about the outcome itself.
            return true
        }

        guard let edgeSet = aspects as? CovEdgeSet else {
            fatalError("Invalid aspects passed to hasAspects")
        }

        let result = libcoverage.cov_compare_equal(&context, edgeSet.edges, edgeSet.count)
        if result == -1 {
            logger.error("Could not compare progam executions")
        }
        return result == 1
    }

    public func hasAspects2(_ execution: Execution, _ aspects: ProgramAspects) -> Bool {
        guard execution.outcome == aspects.outcome else {
            return false
        }

        if execution.outcome.isCrash() {
            // For crashes, we don't care about the edges that were triggered, just about the outcome itself.
            return true
        }

        guard let pathSet = aspects as? CovPathSet else {
            fatalError("Invalid aspects passed to hasAspects")
        }

        let result = libcoverage.cov_compare_equal2(&context, pathSet.path, pathSet.count, pathSet.phaseID)
        if result == -1 {
            logger.error("Could not compare progam executions")
        }
        return result == 1
    }
    
    /*
    public func hasAspects2(_ execution: Execution, _ aspects: ProgramAspects) -> Bool {
            guard execution.outcome == aspects.outcome else {
                return false
            }
            //print("has aspects")
            if let phaseAspects = aspects as? PhaseAspects {
                assert(!aspects.outcome.isCrash())
                var passFlags4 = libcoverage.pass_data2()
                let pass_result3 = libcoverage.pass_combine_bitmap(&self.context, &passFlags4, 0)
                if phaseAspects.phase_index == UInt32(pass_result3) {
                    return true
                } else {
                    return false
                }
            } else {
                return false
            }
    }
    */

    public func computeAspectIntersection(of program: Program, with aspects: ProgramAspects) -> ProgramAspects? {
        guard let firstCovEdgeSet = aspects as? CovEdgeSet else {
            logger.fatal("Coverage Evaluator received non coverage aspects")
        }

        // Mark all edges in the provided aspects as undiscovered so they can be retriggered during the next execution.
        resetAspects(firstCovEdgeSet)

        // Execute the program and collect coverage information.
        let execution = fuzzer.execute(program)
        guard execution.outcome == .succeeded else { return nil }
        guard let secondCovEdgeSet = evaluate(execution, program) as? CovEdgeSet else { return nil }

        let firstEdgeSet = Set(UnsafeBufferPointer(start: firstCovEdgeSet.edges, count: Int(firstCovEdgeSet.count)))
        let secondEdgeSet = Set(UnsafeBufferPointer(start: secondCovEdgeSet.edges, count: Int(secondCovEdgeSet.count)))

        // Reset all edges that were only triggered by the 2nd execution (those only triggered by the 1st execution were already reset earlier).
        for edge in secondEdgeSet.subtracting(firstEdgeSet) {
            resetEdge(edge)
        }

        // Compute the intersection of the edges.
        let intersectedEdgeSet = secondEdgeSet.intersection(firstEdgeSet)
        guard intersectedEdgeSet.count != 0 else { return nil }

        // Here we reuse one of the existing CovEdgeSets instead of creating a new one to avoid a malloc() and free() of the backing buffer.
        let intersectedCovEdgeSet = secondCovEdgeSet
        intersectedCovEdgeSet.setEdges(intersectedEdgeSet)

        return intersectedCovEdgeSet
    }

    public func exportState() -> Data {
        var state = Data()
        state.append(Data(bytes: &context.num_edges, count: 4))
        state.append(Data(bytes: &context.bitmap_size, count: 4))
        state.append(Data(bytes: &context.found_edges, count: 4))
        state.append(context.virgin_bits, count: Int(context.bitmap_size))
        state.append(context.crash_bits, count: Int(context.bitmap_size))
        return state
    }

    public func importState(_ state: Data) throws {
        assert(isInitialized)
        let headerSize = 12     // 3 x 4 bytes: num_edges, bitmap_size, found_edges. See exportState() above

        guard state.count == headerSize + Int(context.bitmap_size) * 2 else {
            throw FuzzilliError.evaluatorStateImportError("Cannot import coverage state as it has an unexpected size. Ensure all instances use the same build of the target")
        }

        let numEdges = state.withUnsafeBytes { $0.load(fromByteOffset: 0, as: UInt32.self) }
        let bitmapSize = state.withUnsafeBytes { $0.load(fromByteOffset: 4, as: UInt32.self) }
        let foundEdges = state.withUnsafeBytes { $0.load(fromByteOffset: 8, as: UInt32.self) }

        guard bitmapSize == context.bitmap_size && numEdges == context.num_edges else {
            throw FuzzilliError.evaluatorStateImportError("Cannot import coverage state due to different bitmap sizes. Ensure all instances use the same build of the target")
        }

        context.found_edges = foundEdges

        var start = state.startIndex + headerSize
        state.copyBytes(to: context.virgin_bits, from: start..<start + Int(bitmapSize))
        start += Int(bitmapSize)
        state.copyBytes(to: context.crash_bits, from: start..<start + Int(bitmapSize))

        logger.info("Imported existing coverage state with \(foundEdges) edges already discovered")
    }

    public func resetState() {
        resetCounts = [:]
        libcoverage.cov_reset_state(&context)
    }

    public func writePath() {
        libcoverage.writePath(&context)
    }


    // TODO See if we want to count the number of non-deterministic edges and expose them through the fuzzer statistics (if deterministic mode is enabled)
    private func resetEdge(_ edge: UInt32) {
        resetCounts[edge] = (resetCounts[edge] ?? 0) + 1
        if resetCounts[edge]! <= maxResetCount {
            libcoverage.cov_clear_edge_data(&context, edge)
        }
    }

    private func resetAspects(_ aspects: CovEdgeSet) {
        for i in 0..<Int(aspects.count) {
            resetEdge(aspects.edges![i])
        }
    }
    
    public func clearMyBitmap() {
            //libcoverage.pass_clear_bitmap(&self.context)
    }

    public func clearMyVirgin() {
        logger.info("3 hours, update seeds for optimization path")
        libcoverage.clear_my_virgin(&self.context)
    }
}
