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

/// Reducer to remove inputs from variadic operations.
struct VariadicInputReducer: Reducer {
    func reduce(_ code: inout Code, with helper: MinimizationHelper) {
        for instr in code {
            guard instr.isVariadic else { continue }
            let index = instr.index

            var instr = instr
            repeat {
                assert(instr.isVariadic)
                // Remove the last variadic input (if it exists)
                guard instr.numInputs > instr.firstVariadicInput else { break }

                let newOp: Operation
                switch instr.op.opcode {
                case .createObject(let op):
                    newOp = CreateObject(propertyNames: op.propertyNames.dropLast())
                case .createArray(let op):
                    newOp = CreateArray(numInitialValues: op.numInitialValues - 1)
                case .createObjectWithSpread(let op):
                    if op.numSpreads > 0 {
                        newOp = CreateObjectWithSpread(propertyNames: op.propertyNames, numSpreads: op.numSpreads - 1)
                    } else {
                        newOp = CreateObjectWithSpread(propertyNames: op.propertyNames.dropLast(), numSpreads: op.numSpreads)
                    }
                case .createArrayWithSpread(let op):
                    newOp = CreateArrayWithSpread(spreads: op.spreads.dropLast())
                case .callFunction(let op):
                    newOp = CallFunction(numArguments: op.numArguments - 1)
                case .callFunctionWithSpread(let op):
                    if op.numArguments == 1 {
                        newOp = CallFunction(numArguments: 0)
                    } else {
                        newOp = CallFunctionWithSpread(numArguments: op.numArguments - 1, spreads: op.spreads.dropLast())
                    }
                case .construct(let op):
                    newOp = Construct(numArguments: op.numArguments - 1)
                case .constructWithSpread(let op):
                    if op.numArguments == 1 {
                        newOp = Construct(numArguments: 0)
                    } else {
                        newOp = ConstructWithSpread(numArguments: op.numArguments - 1, spreads: op.spreads.dropLast())
                    }
                case .callMethod(let op):
                    newOp = CallMethod(methodName: op.methodName, numArguments: op.numArguments - 1)
                case .callMethodWithSpread(let op):
                    if op.numArguments == 1 {
                        newOp = CallMethod(methodName: op.methodName, numArguments: 0)
                    } else {
                        newOp = CallMethodWithSpread(methodName: op.methodName, numArguments: op.numArguments - 1, spreads: op.spreads.dropLast())
                    }
                case .callComputedMethod(let op):
                    newOp = CallComputedMethod(numArguments: op.numArguments - 1)
                case .callComputedMethodWithSpread(let op):
                    if op.numArguments == 1 {
                        newOp = CallComputedMethod(numArguments: 0)
                    } else {
                        newOp = CallComputedMethodWithSpread(numArguments: op.numArguments - 1, spreads: op.spreads.dropLast())
                    }
                case .callSuperConstructor(let op):
                    newOp = CallSuperConstructor(numArguments: op.numArguments - 1)
                case .callSuperMethod(let op):
                    newOp = CallSuperMethod(methodName: op.methodName, numArguments: op.numArguments - 1)
                case .createTemplateString(let op):
                    newOp = CreateTemplateString(parts: op.parts.dropLast())
                default:
                    fatalError("Unknown variadic operation \(instr.op)")
                }

                let inouts = instr.inputs.dropLast() + instr.outputs + instr.innerOutputs
                instr = Instruction(newOp, inouts: inouts)
            } while helper.tryReplacing(instructionAt: index, with: instr, in: &code)
        }
    }
    
    func myReduce(_ code: inout Code, with helper: MinimizationHelper) {
        for instr in code {
            guard instr.isVariadic else { continue }
            let index = instr.index

            var instr = instr
            repeat {
                assert(instr.isVariadic)
                // Remove the last variadic input (if it exists)
                guard instr.numInputs > instr.firstVariadicInput else { break }

                let newOp: Operation
                switch instr.op.opcode {
                case .createObject(let op):
                    newOp = CreateObject(propertyNames: op.propertyNames.dropLast())
                case .createArray(let op):
                    newOp = CreateArray(numInitialValues: op.numInitialValues - 1)
                case .createObjectWithSpread(let op):
                    if op.numSpreads > 0 {
                        newOp = CreateObjectWithSpread(propertyNames: op.propertyNames, numSpreads: op.numSpreads - 1)
                    } else {
                        newOp = CreateObjectWithSpread(propertyNames: op.propertyNames.dropLast(), numSpreads: op.numSpreads)
                    }
                case .createArrayWithSpread(let op):
                    newOp = CreateArrayWithSpread(spreads: op.spreads.dropLast())
                case .callFunction(let op):
                    newOp = CallFunction(numArguments: op.numArguments - 1)
                case .callFunctionWithSpread(let op):
                    if op.numArguments == 1 {
                        newOp = CallFunction(numArguments: 0)
                    } else {
                        newOp = CallFunctionWithSpread(numArguments: op.numArguments - 1, spreads: op.spreads.dropLast())
                    }
                case .construct(let op):
                    newOp = Construct(numArguments: op.numArguments - 1)
                case .constructWithSpread(let op):
                    if op.numArguments == 1 {
                        newOp = Construct(numArguments: 0)
                    } else {
                        newOp = ConstructWithSpread(numArguments: op.numArguments - 1, spreads: op.spreads.dropLast())
                    }
                case .callMethod(let op):
                    newOp = CallMethod(methodName: op.methodName, numArguments: op.numArguments - 1)
                case .callMethodWithSpread(let op):
                    if op.numArguments == 1 {
                        newOp = CallMethod(methodName: op.methodName, numArguments: 0)
                    } else {
                        newOp = CallMethodWithSpread(methodName: op.methodName, numArguments: op.numArguments - 1, spreads: op.spreads.dropLast())
                    }
                case .callComputedMethod(let op):
                    newOp = CallComputedMethod(numArguments: op.numArguments - 1)
                case .callComputedMethodWithSpread(let op):
                    if op.numArguments == 1 {
                        newOp = CallComputedMethod(numArguments: 0)
                    } else {
                        newOp = CallComputedMethodWithSpread(numArguments: op.numArguments - 1, spreads: op.spreads.dropLast())
                    }
                case .callSuperConstructor(let op):
                    newOp = CallSuperConstructor(numArguments: op.numArguments - 1)
                case .callSuperMethod(let op):
                    newOp = CallSuperMethod(methodName: op.methodName, numArguments: op.numArguments - 1)
                case .createTemplateString(let op):
                    newOp = CreateTemplateString(parts: op.parts.dropLast())
                default:
                    fatalError("Unknown variadic operation \(instr.op)")
                }

                let inouts = instr.inputs.dropLast() + instr.outputs + instr.innerOutputs
                instr = Instruction(newOp, inouts: inouts)
            } while helper.tryReplacing2(instructionAt: index, with: instr, in: &code)
        }
    }
}
