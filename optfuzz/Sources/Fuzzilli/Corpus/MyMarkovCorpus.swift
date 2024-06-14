import Foundation

/// Corpus & Scheduler based on
/// Coverage-based Greybox Fuzzing as Markov Chain paper
/// https://mboehme.github.io/paper/TSE18.pdf
/// Simply put, the corpus keeps track of which paths have been found, and prioritizes seeds
/// whose path has been hit less than average. Ideally, this allows the fuzzer to prioritize
/// less explored coverage.
/// In the paper, a number of iterations is assigned to each sample, and each sample is then
/// scheduled that number of times. This implementation finds 1 / desiredSelectionProportion
/// of the least hit edges, and schedules those. After those have been mutated and evalutated,
/// the list is regenerated.
/// TODO:
/// - In order to properly implement the paper, the number of executions of each sample needs
///     to be scaled by its execution time (e.g. multiple by timeout / execution time), to
///     prioritize faster samples

public class MyMarkovCorpus: ComponentBase, Corpus {
    // All programs that were added to the corpus so far
    private var allIncludedPrograms: [Program] = []
    // Queue of programs to be executed next, all of which hit a rare edge
    private var programExecutionQueue: [Program] = []

    // Basic Corpus 
    private let phaseNum = 29
    private let minSize = 1000
    private let maxSize = Int.max
    private let minMutationsPerSample = 25
    private var programs: RingBuffer<Program>
    private var ages: RingBuffer<Int>

    private var execLimit = 750
    // For each edge encountered thus far, track which program initially discovered it
    private var edgeMap: [UInt32:Program] = [:]
    private var myEdgeMap: [[UInt32:Program]] = [[UInt32:Program]]()
    private var mySize: [UInt32] = []

    // This scheduler tracks the total number of samples it has returned
    // This allows it to build an initial baseline by randomly selecting a program to mutate
    // before switching to the more computationally expensive selection of programs that
    // hit infreqent edges
    private var totalExecs: UInt32 = 0

    // This scheduler returns one base program multiple times, in order to compensate the overhead caused by tracking
    // edge counts
    private var currentProg: Program
    private var remainingEnergy: UInt32 = 0

    // Markov corpus requires an evaluator that tracks edge coverage
    // Thus, the corpus object keeps a reference to the evaluator, in order to only downcast once
    private var covEvaluator: ProgramCoverageEvaluator

    // Rate at which selected samples will be included, to promote diversity between instances
    // Equivalent to 1 - dropoutRate
    private var dropoutRate: Double

    // The scheduler will initially selectd the 1 / desiredSelectionProportion samples with the least frequent
    // edge hits in each round, before dropout is applied
    private let desiredSelectionProportion = 10

    public init(covEvaluator: ProgramCoverageEvaluator, dropoutRate: Double) {
        self.dropoutRate = dropoutRate
        //covEvaluator.enableEdgeTracking()
        self.covEvaluator = covEvaluator
        self.currentProg = Program()

        self.programs = RingBuffer(maxSize: maxSize)
        self.ages = RingBuffer(maxSize: maxSize)
        for i in 0..<phaseNum {
            var tempMap: [UInt32:Program] = [:]
            myEdgeMap.append(tempMap)
            mySize.append(0)
        }

        super.init(name: "MyMarkovCorpus")
    }

    override func initialize() {
        assert(covEvaluator === fuzzer.evaluator as! ProgramCoverageEvaluator)
        fuzzer.timers.scheduleTask(every: 30 * Minutes, cleanup)
        //fuzzer.timers.scheduleTask(every:  72 * 60 * Minutes, byby)
        //fuzzer.timers.scheduleTask(every: 5 * 24 * 60 * Minutes, fuzzer.evaluator.clearMyVirgin)
    }
    
    private func byby() {
        exit(-1)
    }
    
    private func cleanup() {
        var newPrograms = RingBuffer<Program>(maxSize: programs.maxSize)
        var newAges = RingBuffer<Int>(maxSize: ages.maxSize)

        for i in 0..<programs.count {
            let remaining = programs.count - i
            if ages[i] < minMutationsPerSample || remaining <= (minSize - newPrograms.count) {
                newPrograms.append(programs[i])
                newAges.append(ages[i])
            }
        }

        logger.info("Edge Corpus cleanup finished: \(self.programs.count) -> \(newPrograms.count)")
        programs = newPrograms
        ages = newAges
    }

    // add new path (minimized program) to corpus
    // add for every phase, minimize for every phase
    public func addMyProgram(_ program: Program, _ aspects: ProgramAspects) {
        guard program.size > 0 else { return }

        guard let origCov = aspects as? CovPathSet else {
            logger.fatal("Markov Corpus needs to be provided a CovPathSet when adding a program")
        }

        prepareProgramForInclusion(program, index: self.size)

        allIncludedPrograms.append(program)
        //print("path id: \(origCov.phaseID)")
        for e in origCov.getPath() {
            myEdgeMap[Int(origCov.phaseID)][e] = program
            mySize[Int(origCov.phaseID)] += 1

            //print("add path bitmap:\(origCov.phaseID)")
        }
    }

    // add new edge to corpus
    public func add(_ program: Program, _ aspects: ProgramAspects) {
        if program.size > 0 {
            prepareProgramForInclusion(program, index: programs.count)
            programs.append(program)
            ages.append(0)
            //print("add edge")
        }
    }
    
    /// Split evenly between programs in the current queue and all programs available to the corpus
    public func randomElementForSplicing() -> Program {

        let idx = Int.random(in: 0..<100)
        //if idx < 50 {
            let idx2 = Int.random(in: 0..<programs.count)
            let program = programs[idx2]
            assert(!program.isEmpty)
            return program
        //}
        /*
        else {
            var prog = programExecutionQueue.randomElement()
            if prog == nil || probability(0.5) {
                prog = allIncludedPrograms.randomElement()
            }
            assert(prog != nil && prog!.size > 0)
            return prog!
        }
        */
        
        
    }

    /// For the first 250 executions, randomly choose a program. This is done to build a base list of edge counts
    /// Once that base is acquired, provide samples that trigger an infrequently hit edge
    public func randomElementForMutating() -> Program {
        //print("select seed from corpus")
        let idx = Int.random(in: 0..<100)
        if idx < 50 {
            let idx2 = Int.random(in: 0..<programs.count)
            ages[idx2] += 1
            let program = programs[idx2]
            assert(!program.isEmpty)
            return program
        }
        totalExecs += 1
        // Only do computationally expensive work choosing the next program when there is a solid
        // baseline of execution data. The data tracked in the statistics module is not used, as modules are intended
        // to not be required for the fuzzer to function.
        if allIncludedPrograms.count > 50 {
            // Check if more programs are needed
            if programExecutionQueue.isEmpty {
                regenProgramList()
            }
            if remainingEnergy > 0 {
                remainingEnergy -= 1
            } else {
                remainingEnergy = energyBase()
                currentProg = programExecutionQueue.popLast()!
            }
            //print("select path seed from queue")
            return currentProg
        } else {
            let idx2 = Int.random(in: 0..<programs.count)
            ages[idx2] += 1
            let program = programs[idx2]
            assert(!program.isEmpty)
            return program
        }
    }

    private func regenProgramList() {
        if programExecutionQueue.count != 0 {
            logger.fatal("Attempted to generate execution list while it still has programs")
        }
        for i in 0..<phaseNum {
            regenProgramListInternal(UInt32(i))
        }
        if programExecutionQueue.count == 0 {
            logger.fatal("[Modified] RegenProgramList Failed!")
        }
        logger.info("MyMarkov Corpus selected \(programExecutionQueue.count) new programs")
    }

    private func regenProgramListInternal(_ index: UInt32) -> Bool {
        
        let pathCounts = covEvaluator.getPathHitCounts(index)
        let pathCountsSorted = pathCounts.sorted()

        // Find the edge with the smallest count
        var startIndex = -1
        for (i, val) in pathCountsSorted.enumerated() {
            if val != 0 {
                startIndex = i
                break
            }
        }
        if startIndex == -1 {
            return false
        }

        // Find the nth interesting edge's count
        let desiredPathCount = min(max(Int(mySize[Int(index)]) / desiredSelectionProportion, 1), 80)
        var endIndex = min(startIndex + desiredPathCount, pathCountsSorted.count - 1)
        var maxPathCountToFind = pathCountsSorted[endIndex]

        logger.info("select seed from phase: \(index):")
        logger.info("startIndex: \(startIndex)  endIndex: \(endIndex)")
        var limit_count = 0
        // Find the n edges with counts <= maxEdgeCountToFind.
        for (i, val) in pathCounts.enumerated() {
            if limit_count > 80 {
                break
            }
            // Applies dropout on otherwise valid samples, to ensure variety between instances
            // This will likely select some samples multiple times, which is acceptable as
            // it is proportional to how many infrquently hit edges the sample has
            if val != 0 && val <= maxPathCountToFind && (probability(1 - dropoutRate) || programExecutionQueue.isEmpty) {
                if let prog = myEdgeMap[Int(index)][UInt32(i)] {
                    if prog.selectedTimes > 100 { // if a seed is selected over 5 times, then do not select it again
                        endIndex = min(endIndex + 1, pathCountsSorted.count - 1)
                        maxPathCountToFind = pathCountsSorted[endIndex]
                        logger.info("abandon \(i), new endIndex: \(endIndex)")
                        continue;
                    }
                    prog.selectedTimes += 1
                    programExecutionQueue.append(prog)
                    limit_count += 1
                    logger.info("\(i)")
                }
            }
        }

        // Determine how many edges have been leaked and produce a warning if over 1% of total edges
        // Done as second pass for code clarity
        // Testing on v8 shows that < 0.01% of total edges are leaked
        // Potential causes:
        //  - Libcoverage iterates over the edge map twice, once for new coverage, and once for edge counts.
        //      This occurs while the target JS engine is running, so the coverage may be slightly different between the passes
        //      However, this is unlikely to be useful coverage for the purposes of Fuzzilli
        //  - Crashing samples may find new coverage and thus increment counters, but are not added to the corpus
        var missingPathCount = 0
        for (i, val) in pathCounts.enumerated() {
            if val != 0 && myEdgeMap[Int(index)][UInt32(i)] == nil {
                missingPathCount += 1
            }
        }
        if missingPathCount > (pathCounts.count / 10) {
            let missingPercentage = Double(missingPathCount) / Double(pathCounts.count) * 100.0
            logger.warning("\(missingPercentage)% of total paths have been leaked")
        }
        
        return true
    }

    public func addPhaseQueue(_ program: Program, _ index: Int) {

    }
    

    public var size: Int {
        return programs.count
        
    }
    
    public var size2: Int {
        return allIncludedPrograms.count
    }

    public var isEmpty: Bool {
        return size == 0
    }

    public subscript(index: Int) -> Program {
        return allIncludedPrograms[index]
    }

    public func allPrograms() -> [Program] {
        return allIncludedPrograms
    }

    // We don't currently support fast state synchronization.
    // Instead, we need to import every sample separately (potentially
    // multiple times for determinism) to determine the edges it triggers.
    public var supportsFastStateSynchronization: Bool {
        return false
    }

    // Note that this exports all programs, but does not include edge counts
    public func exportState() throws -> Data {
        fatalError("Not Supported")
    }

    public func importState(_ buffer: Data) throws {
        fatalError("Not Supported")
    }

    // Ramp up the number of times a sample is used as the initial seed over time
    private func energyBase() -> UInt32 {
        return UInt32(Foundation.log10(Float(totalExecs))) + 1
    }
}
