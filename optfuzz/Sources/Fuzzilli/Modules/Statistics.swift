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

public class Statistics: Module {
    /// The data just for this instance.
    private var ownData = Fuzzilli_Protobuf_Statistics()

    /// Logger used to print some internal statistics in regular intervals.
    private let logger = Logger(withLabel: "Statistics")

    /// Data required to compute executions per second.
    private var currentExecs = 0.0
    private var lastEpsUpdate = Date()
    private var lastExecsPerSecond = 0.0

    /// Data required to compute the fuzzer overhead (i.e. the fraction of the total time that is not spent executing generated programs in the target engine).
    /// This includes time required for worker synchronization, to mutate/generate a program, to lift it, to restart the target process after crashes/timeouts, etc.
    private var overheadAvg = MovingAverage(n: 1000)
    private var lastPreExecDate = Date()
    private var lastExecDate = Date()

    /// Moving average to keep track of average program size.
    private var programSizeAvg = MovingAverage(n: 1000)

    /// Moving average to keep track of average program size in the corpus.
    /// Only computed locally, not across workers.
    private var corpusProgramSizeAvg = MovingAverage(n: 1000)

    /// Moving average of the number of valid programs in the last 1000 generated programs.
    private var correctnessRate = MovingAverage(n: 1000)

    /// Moving average of the number of timeoouts in the last 1000 generated programs.
    private var timeoutRate = MovingAverage(n: 1000)

    /// All data from connected workers.
    private var workers = [UUID: Fuzzilli_Protobuf_Statistics]()

    /// The IDs of workers that are currently inactive.
    private var inactiveWorkers = Set<UUID>()

    public init() {}

    /// Computes and returns the statistical data for this instance and all connected workers.
    public func compute() -> Fuzzilli_Protobuf_Statistics {
        assert(workers.count - inactiveWorkers.count == ownData.numWorkers)

        // Compute local statistics data
        ownData.avgProgramSize = programSizeAvg.currentValue
        ownData.avgCorpusProgramSize = corpusProgramSizeAvg.currentValue
        ownData.fuzzerOverhead = overheadAvg.currentValue
        ownData.correctnessRate = correctnessRate.currentValue
        ownData.timeoutRate = timeoutRate.currentValue

        // Compute global statistics data
        var data = ownData
        for (id, workerData) in workers {
            // Add "global" fields, even from workers that are no longer active
            data.totalSamples += workerData.totalSamples
            data.validSamples += workerData.validSamples
            data.timedOutSamples += workerData.timedOutSamples
            data.totalExecs += workerData.totalExecs

            /*
            for k in 0..<30 {
                data.bitmap_hit[k] += workerData.bitmap_hit[k]
                data.bitmap_total[k] += workerData.bitmap_total[k]
            }
            */

            /*
            data.DFG += workerData.DFG
            data.Fixup += workerData.Fixup
            data.TypeCheckHoisting += workerData.TypeCheckHoisting
            data.StrengthReduction += workerData.StrengthReduction
            data.ConstantFolding += workerData.ConstantFolding
            data.CFGSimplification += workerData.CFGSimplification
            data.LocalCSE += workerData.LocalCSE
            data.PhantomInsertion += workerData.PhantomInsertion
            data.CriticalEdgeBreaking += workerData.CriticalEdgeBreaking
            data.AugumentsElimination += workerData.AugumentsElimination
            data.PutStackSinking += workerData.PutStackSinking
            data.ConstantHoisting += workerData.ConstantHoisting
            data.GlobalCSE += workerData.GlobalCSE
            data.ObjectAllocationSinking += workerData.ObjectAllocationSinking
            data.ValueRepReduction += workerData.ValueRepReduction
            data.LICM += workerData.LICM
            data.IntegerRangeOptimization += workerData.IntegerRangeOptimization
            data.IntegerCheckCombining += workerData.IntegerCheckCombining
            data.FTL += workerData.FTL
            data.MyTotal += workerData.MyTotal
            */

            if !self.inactiveWorkers.contains(id) {
                // Add fields that only have meaning for active workers
                data.numWorkers += workerData.numWorkers
                data.avgProgramSize += workerData.avgProgramSize
                data.execsPerSecond += workerData.execsPerSecond
                data.fuzzerOverhead += workerData.fuzzerOverhead
                data.correctnessRate += workerData.correctnessRate
                data.timeoutRate += workerData.timeoutRate
            }

            // All other fields are already indirectly synchronized (e.g. number of interesting samples founds)
        }

        data.avgProgramSize /= Double(ownData.numWorkers + 1)
        data.fuzzerOverhead /= Double(ownData.numWorkers + 1)
        data.correctnessRate /= Double(ownData.numWorkers + 1)
        data.timeoutRate /= Double(ownData.numWorkers + 1)

        return data
    }
    public func update(passArray:[UInt32]) {
            self.ownData.MyTotal += 1
            self.ownData.DFG += Int(passArray[0])
            self.ownData.Fixup += Int(passArray[1])
            self.ownData.TypeCheckHoisting += Int(passArray[2])
            self.ownData.StrengthReduction += Int(passArray[3])
            self.ownData.ConstantFolding += Int(passArray[4])
            self.ownData.CFGSimplification += Int(passArray[5])
            self.ownData.LocalCSE += Int(passArray[6])
            self.ownData.PhantomInsertion += Int(passArray[8])
            self.ownData.CriticalEdgeBreaking += Int(passArray[9])
            self.ownData.AugumentsElimination += Int(passArray[10])
            self.ownData.PutStackSinking += Int(passArray[11])
            self.ownData.ConstantHoisting += Int(passArray[12])
            self.ownData.GlobalCSE += Int(passArray[13])
            self.ownData.ObjectAllocationSinking += Int(passArray[17])
            self.ownData.ValueRepReduction += Int(passArray[18])
            self.ownData.LICM += Int(passArray[19])
            self.ownData.IntegerRangeOptimization += Int(passArray[20])
            self.ownData.IntegerCheckCombining += Int(passArray[21])
            self.ownData.FTL += Int(passArray[23])
            if self.ownData.LocalCSE != 0 {
                    var tmp = self.ownData.Fixup
                    self.ownData.phaseFlag = 1
                    if self.ownData.TypeCheckHoisting <= tmp && self.ownData.TypeCheckHoisting != 0 {
                        tmp = self.ownData.TypeCheckHoisting
                        self.ownData.phaseFlag = 2
                    }
                    if self.ownData.StrengthReduction <= tmp && self.ownData.StrengthReduction != 0 {
                        tmp = self.ownData.StrengthReduction
                        self.ownData.phaseFlag = 3
                    }
                    if self.ownData.ConstantFolding <= tmp && self.ownData.ConstantFolding != 0 {
                        tmp = self.ownData.ConstantFolding
                        self.ownData.phaseFlag = 4
                    }
                    if self.ownData.CFGSimplification <= tmp && self.ownData.CFGSimplification != 0 {
                        tmp = self.ownData.CFGSimplification
                        self.ownData.phaseFlag = 5
                    }
                    if self.ownData.LocalCSE <= tmp && self.ownData.LocalCSE != 0 {
                        tmp = self.ownData.LocalCSE
                        self.ownData.phaseFlag = 6
                    }
            }
        }

    public func initialize(with fuzzer: Fuzzer) {
        fuzzer.registerEventListener(for: fuzzer.events.CrashFound) { _ in
            self.ownData.crashingSamples += 1
        }
        fuzzer.registerEventListener(for: fuzzer.events.TimeOutFound) { _ in
            self.ownData.timedOutSamples += 1
            self.correctnessRate.add(0.0)
            self.timeoutRate.add(1.0)
        }
        fuzzer.registerEventListener(for: fuzzer.events.InvalidProgramFound) { _ in
            self.correctnessRate.add(0.0)
            self.timeoutRate.add(0.0)
        }
        fuzzer.registerEventListener(for: fuzzer.events.ValidProgramFound) { _ in
            self.ownData.validSamples += 1
            self.correctnessRate.add(1.0)
            self.timeoutRate.add(0.0)
        }

        fuzzer.registerEventListener(for: fuzzer.events.AddBitmap_hit) { value in
            for i in 0..<30 {
                self.ownData.bitmap_hit[i] += value[i]
            }
            
        }
        fuzzer.registerEventListener(for: fuzzer.events.AddBitmap_total) { value in
            for i in 0..<30 {
                self.ownData.bitmap_total[i] += value[i]
            }
        }

       

        fuzzer.registerEventListener(for: fuzzer.events.PostExecute) { exec in
            self.ownData.totalExecs += 1
            self.currentExecs += 1

            let now = Date()
            let totalTime = now.timeIntervalSince(self.lastExecDate)
            self.lastExecDate = now

            let overhead = 1.0 - (exec.execTime / totalTime)
            self.overheadAvg.add(overhead)
        }
        
        fuzzer.registerEventListener(for: fuzzer.events.myUpdateStatics) { passArray in
                    self.ownData.MyTotal += 1
                    self.ownData.DFG += Int(passArray[0])
                    self.ownData.Fixup += Int(passArray[1])
                    self.ownData.TypeCheckHoisting += Int(passArray[2])
                    self.ownData.StrengthReduction += Int(passArray[3])
                    self.ownData.ConstantFolding += Int(passArray[4])
                    self.ownData.CFGSimplification += Int(passArray[5])
                    self.ownData.LocalCSE += Int(passArray[6])
                    self.ownData.PhantomInsertion += Int(passArray[8])
                    self.ownData.CriticalEdgeBreaking += Int(passArray[9])
                    self.ownData.AugumentsElimination += Int(passArray[10])
                    self.ownData.PutStackSinking += Int(passArray[11])
                    self.ownData.ConstantHoisting += Int(passArray[12])
                    self.ownData.GlobalCSE += Int(passArray[13])
                    self.ownData.ObjectAllocationSinking += Int(passArray[17])
                    self.ownData.ValueRepReduction += Int(passArray[18])
                    self.ownData.LICM += Int(passArray[19])
                    self.ownData.IntegerRangeOptimization += Int(passArray[20])
                    self.ownData.IntegerCheckCombining += Int(passArray[21])
                    self.ownData.FTL += Int(passArray[23])
                    if self.ownData.LocalCSE != 0 {
                        var tmp = self.ownData.Fixup
                        self.ownData.phaseFlag = 1
                        if self.ownData.TypeCheckHoisting <= tmp && self.ownData.TypeCheckHoisting != 0 {
                            tmp = self.ownData.TypeCheckHoisting
                            self.ownData.phaseFlag = 2
                        }
                        if self.ownData.StrengthReduction <= tmp && self.ownData.StrengthReduction != 0 {
                            tmp = self.ownData.StrengthReduction
                            self.ownData.phaseFlag = 3
                        }
                        if self.ownData.ConstantFolding <= tmp && self.ownData.ConstantFolding != 0 {
                            tmp = self.ownData.ConstantFolding
                            self.ownData.phaseFlag = 4
                        }
                        if self.ownData.CFGSimplification <= tmp && self.ownData.CFGSimplification != 0 {
                            tmp = self.ownData.CFGSimplification
                            self.ownData.phaseFlag = 5
                        }
                        if self.ownData.LocalCSE <= tmp && self.ownData.LocalCSE != 0 {
                            tmp = self.ownData.LocalCSE
                            self.ownData.phaseFlag = 6
                        }
                    }

                    //self.ownData.DFG += 1 testcase number
                }
        fuzzer.registerEventListener(for: fuzzer.events.InterestingProgramFound) { ev in
            self.ownData.interestingSamples += 1
            self.ownData.coverage = fuzzer.evaluator.currentScore
            self.corpusProgramSizeAvg.add(ev.program.size)
        }
        fuzzer.registerEventListener(for: fuzzer.events.ProgramGenerated) { program in
            self.ownData.totalSamples += 1
            self.programSizeAvg.add(program.size)
        }
        fuzzer.registerEventListener(for: fuzzer.events.WorkerConnected) { id in
            self.ownData.numWorkers += 1
            self.workers[id] = Fuzzilli_Protobuf_Statistics()
            self.inactiveWorkers.remove(id)
        }
        fuzzer.registerEventListener(for: fuzzer.events.WorkerDisconnected) { id in
            self.ownData.numWorkers -= 1
            self.inactiveWorkers.insert(id)
        }
        fuzzer.timers.scheduleTask(every: 30 * Seconds) {
            let now = Date()
            let interval = Double(now.timeIntervalSince(self.lastEpsUpdate))
            guard interval >= 1.0 else {
                return // This can happen due to delays in queue processing
            }

            let execsPerSecond = self.currentExecs / interval
            self.ownData.execsPerSecond += execsPerSecond - self.lastExecsPerSecond
            self.lastExecsPerSecond = execsPerSecond

            self.lastEpsUpdate = now
            self.currentExecs = 0.0
        }

        // Also schedule timers to print internal statistics in regular intervals.
        if fuzzer.config.logLevel.isAtLeast(.info) {
            fuzzer.timers.scheduleTask(every: 15 * Minutes) {
                self.logger.info("Mutator Statistics:")
                let nameMaxLength = fuzzer.mutators.map({ $0.name.count }).max()!
                let maxSamplesGeneratedStringLength = fuzzer.mutators.map({ String($0.totalSamples).count }).max()!
                for mutator in fuzzer.mutators {
                    let name = mutator.name.rightPadded(toLength: nameMaxLength)
                    let correctnessRate = String(format: "%.2f%%", mutator.correctnessRate * 100).leftPadded(toLength: 7)
                    let failureRate = String(format: "%.2f%%", mutator.failureRate * 100).leftPadded(toLength: 7)
                    let timeoutRate = String(format: "%.2f%%", mutator.timeoutRate * 100).leftPadded(toLength: 6)
                    let interestingSamplesRate = String(format: "%.2f%%", mutator.interestingSamplesRate * 100).leftPadded(toLength: 7)
                    let avgInstructionsAdded = String(format: "%.2f", mutator.avgNumberOfInstructionsGenerated).leftPadded(toLength: 5)
                    let samplesGenerated = String(mutator.totalSamples).leftPadded(toLength: maxSamplesGeneratedStringLength)
                    let crashesFound = mutator.crashesFound
                    self.logger.info("    \(name) : Correctness rate: \(correctnessRate), Failure rate: \(failureRate), Interesting sample rate: \(interestingSamplesRate), Timeout rate: \(timeoutRate), Avg. # of instructions added: \(avgInstructionsAdded), Total # of generated samples: \(samplesGenerated), Total # of crashes found: \(crashesFound)")
                }
            }

        }
        if fuzzer.config.logLevel.isAtLeast(.verbose) {
            fuzzer.timers.scheduleTask(every: 30 * Minutes) {
                self.logger.verbose("Code Generator Statistics:")
                let nameMaxLength = fuzzer.codeGenerators.map({ $0.name.count }).max()!
                for generator in fuzzer.codeGenerators {
                    let name = generator.name.rightPadded(toLength: nameMaxLength)
                    let correctnessRate = String(format: "%.2f%%", generator.correctnessRate * 100).leftPadded(toLength: 7)
                    let interestingSamplesRate = String(format: "%.2f%%", generator.interestingSamplesRate * 100).leftPadded(toLength: 7)
                    let timeoutRate = String(format: "%.2f%%", generator.timeoutRate * 100).leftPadded(toLength: 6)
                    let avgInstructionsAdded = String(format: "%.2f", generator.avgNumberOfInstructionsGenerated).leftPadded(toLength: 5)
                    let samplesGenerated = generator.totalSamples
                    self.logger.verbose("    \(name) : Correctness rate: \(correctnessRate), Interesting sample rate: \(interestingSamplesRate), Timeout rate: \(timeoutRate), Avg. # of instructions added: \(avgInstructionsAdded), Total # of generated samples: \(samplesGenerated)")
                }
            }
        }
    }

    /// Import statistics data from a worker.
    public func importData(_ stats: Fuzzilli_Protobuf_Statistics, from worker: UUID) {
        workers[worker] = stats
    }
    public func getPhaseFlag() -> Int {
        return ownData.phaseFlag
    }
}

extension Fuzzilli_Protobuf_Statistics {
    /// The ratio of valid samples to produced samples over the entire runtime of the fuzzer.
    public var globalCorrectnessRate: Double {
        return Double(validSamples) / Double(totalSamples)
    }

    /// The ratio of timed-out samples to produced samples over the entire runtime of the fuzzer.
    public var globalTimeoutRate: Double {
        return Double(timedOutSamples) / Double(totalSamples)
    }
}
