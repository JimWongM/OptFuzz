

/// A temp mutator template for development


public class XXXInputMutator: BaseInstructionMutator {
    /// Whether this instance is type aware or not.
    /// A type aware InputMutator will attempt to find "compatible" replacement
    /// variables, which have roughly the same type as the replaced variable.
    public let isTypeAware: Bool

    /// The name of this mutator.
    public override var name: String {
        return isTypeAware ? "InputMutator (type aware)" : "InputMutator"
    }

    public init(isTypeAware: Bool) {
        self.isTypeAware = isTypeAware
        var maxSimultaneousMutations = defaultMaxSimultaneousMutations
        // A type aware instance can be more aggressive. Based on simple experiments and
        // the mutator correctness rates, it can very roughly be twice as aggressive.
        if isTypeAware {
            maxSimultaneousMutations *= 2
        }
        super.init(maxSimultaneousMutations: maxSimultaneousMutations)
    }

    public override func canMutate(_ instr: Instruction) -> Bool {
        var isOK =  false
        switch instr.op.opcode {
        case .nop,
             .loadInteger,
             .loadBigInt,
             .loadFloat,
             .loadString,
             .loadBoolean,
             .loadUndefined,
             .loadThis,
             .loadArguments,
             .loadRegExp,
             .createObject,
             .createArray,
             .createIntArray,
             .createFloatArray,
             .createObjectWithSpread,
             .createArrayWithSpread,
             .createTemplateString,
             .loadBuiltin,
             .loadProperty,
             .storeProperty,
             .storePropertyWithBinop,
             .deleteProperty,
             .configureProperty,
             .loadElement,
             .storeElement,
             .storeElementWithBinop,
             .deleteElement,
             .configureElement,
             .loadComputedProperty,
             .storeComputedProperty,
             .storeComputedPropertyWithBinop,
             .deleteComputedProperty,
             .configureComputedProperty,
             .typeOf,
             .testInstanceOf,
             .testIn,
             .beginPlainFunction,
             .endPlainFunction,
             .beginArrowFunction,
             .endArrowFunction,
             .beginGeneratorFunction,
             .endGeneratorFunction,
             .beginAsyncFunction,
             .endAsyncFunction,
             .beginAsyncArrowFunction,
             .endAsyncArrowFunction,
             .beginAsyncGeneratorFunction,
             .endAsyncGeneratorFunction,
             .beginConstructor,
             .endConstructor,
             .`return`,
             .yield,
             .yieldEach,
             .await,
             .callFunction,
             .callFunctionWithSpread,
             .construct,
             .constructWithSpread,
             .callMethod,
             .callMethodWithSpread,
             .callComputedMethod,
             .callComputedMethodWithSpread,
             .unaryOperation,
             .binaryOperation,
             .ternaryOperation,
             .reassignWithBinop,
             .dup,
             .reassign,
             .destructArray,
             .destructArrayAndReassign,
             .destructObject,
             .destructObjectAndReassign,
             .compare,
             .eval,
             .beginWith,
             .endWith,
             .loadFromScope,
             .storeToScope,
             .beginClass,
             .beginMethod,
             .endClass,
             .callSuperConstructor,
             .callSuperMethod,
             .loadSuperProperty,
             .storeSuperProperty,
             .storeSuperPropertyWithBinop,
             .beginIf,
             .beginElse,
             .endIf,
             .beginWhileLoop,
             .endWhileLoop,
             .beginDoWhileLoop,
             .endDoWhileLoop,
             .beginForLoop,
             .endForLoop,
             .beginForInLoop,
             .endForInLoop,
             .beginForOfLoop,
             .beginForOfWithDestructLoop,
             .endForOfLoop,
             .beginRepeatLoop,
             .endRepeatLoop,
             .loopBreak,
             .loopContinue,
             .beginTry,
             .beginCatch,
             .beginFinally,
             .endTryCatchFinally,
             .throwException,
             .beginCodeString,
             .endCodeString,
             .beginBlockStatement,
             .endBlockStatement,
             .beginSwitch,
             .beginSwitchCase,
             .beginSwitchDefaultCase,
             .endSwitchCase,
             .endSwitch,
             .switchBreak:
            isOK = true
        default:
            isOK = false
        }
        
        return instr.numInputs > 0 && isOK
        //return (instr.isJump || instr.isLoopBegin || instr.isLoopEnd || instr.isBlock) && instr.numInputs > 0
    }

    public override func mutate(_ instr: Instruction, _ b: ProgramBuilder) {
        var inouts = b.adopt(instr.inouts)

        // Replace one input
        let selectedInput = Int.random(in: 0..<instr.numInputs)
        // Inputs to block end instructions must be taken from the outer scope since the scope
        // closed by the instruction is currently still active.
        let replacement: Variable
        if (isTypeAware) {
            let type = b.type(of: inouts[selectedInput]).generalize()
            // We are guaranteed to find at least the current input.
            replacement = b.randVar(ofType: type, excludeInnermostScope: instr.isBlockEnd)!
        } else {
            replacement = b.randVar(excludeInnermostScope: instr.isBlockEnd)
        }
        b.trace("Replacing input \(selectedInput) (\(inouts[selectedInput])) with \(replacement)")
        inouts[selectedInput] = replacement

        b.append(Instruction(instr.op, inouts: inouts))
    }
}

public class XXXOperationMutator: BaseInstructionMutator {
    public init() {
        super.init(maxSimultaneousMutations: defaultMaxSimultaneousMutations)
    }

    public override func canMutate(_ instr: Instruction) -> Bool {
        // The OperationMutator handles both mutable and variadic operations since both require
        // modifying the operation and both types of mutations are approximately equally "useful",
        // so there's no need for a dedicated "VariadicOperationMutator".
        var isOK = false
        return (instr.isOperationMutable || instr.isVariadic) && isOK
    }

    public override func mutate(_ instr: Instruction, _ b: ProgramBuilder) {
        b.trace("Mutating next operation")

        let newInstr: Instruction
        if instr.isOperationMutable && instr.isVariadic {
            newInstr = probability(0.5) ? mutateOperation(instr, b) : extendVariadicOperation(instr, b)
        } else if instr.isOperationMutable {
            newInstr = mutateOperation(instr, b)
        } else {
            assert(instr.isVariadic)
            newInstr = extendVariadicOperation(instr, b)
        }

        b.adopt(newInstr)
    }

    private func mutateOperation(_ instr: Instruction, _ b: ProgramBuilder) -> Instruction {
        let newOp: Operation
        switch instr.op.opcode {
        case .loadInteger(_):
            newOp = LoadInteger(value: b.genInt())
        case .loadBigInt(_):
            newOp = LoadBigInt(value: b.genInt())
        case .loadFloat(_):
            newOp = LoadFloat(value: b.genFloat())
        case .loadString(_):
            newOp = LoadString(value: b.genString())
        case .loadRegExp(let op):
            if probability(0.5) {
                newOp = LoadRegExp(value: b.genRegExp(), flags: op.flags)
            } else {
                newOp = LoadRegExp(value: op.value, flags: b.genRegExpFlags())
            }
        case .loadBoolean(let op):
            newOp = LoadBoolean(value: !op.value)
        case .createObject(let op):
            var propertyNames = op.propertyNames
            assert(!propertyNames.isEmpty)
            propertyNames[Int.random(in: 0..<propertyNames.count)] = b.genPropertyNameForWrite()
            newOp = CreateObject(propertyNames: propertyNames)
        case .createIntArray:
            var values = [Int64]()
            for _ in 0..<Int.random(in: 1...10) {
                values.append(b.genInt())
            }
            newOp = CreateIntArray(values: values)
        case .createFloatArray:
            var values = [Double]()
            for _ in 0..<Int.random(in: 1...10) {
                values.append(b.genFloat())
            }
            newOp = CreateFloatArray(values: values)
        case .createObjectWithSpread(let op):
            var propertyNames = op.propertyNames
            assert(!propertyNames.isEmpty)
            propertyNames[Int.random(in: 0..<propertyNames.count)] = b.genPropertyNameForWrite()
            newOp = CreateObjectWithSpread(propertyNames: propertyNames, numSpreads: op.numSpreads)
        case .createArrayWithSpread(let op):
            var spreads = op.spreads
            assert(!spreads.isEmpty)
            let idx = Int.random(in: 0..<spreads.count)
            spreads[idx] = !spreads[idx]
            newOp = CreateArrayWithSpread(spreads: spreads)
        case .loadBuiltin(_):
            newOp = LoadBuiltin(builtinName: b.genBuiltinName())
        case .loadProperty(_):
            newOp = LoadProperty(propertyName: b.genPropertyNameForRead())
        case .storeProperty(_):
            newOp = StoreProperty(propertyName: b.genPropertyNameForWrite())
        case .storePropertyWithBinop(_):
            newOp = StorePropertyWithBinop(propertyName: b.genPropertyNameForWrite(), operator: chooseUniform(from: BinaryOperator.allCases))
        case .deleteProperty(_):
            newOp = DeleteProperty(propertyName: b.genPropertyNameForWrite())
        case .configureProperty(let op):
            // Change the flags or the property name, but don't change the type as that would require changing the inputs as well.
            if probability(0.5) {
                newOp = ConfigureProperty(propertyName: b.genPropertyNameForWrite(), flags: op.flags, type: op.type)
            } else {
                newOp = ConfigureProperty(propertyName: op.propertyName, flags: PropertyFlags.random(), type: op.type)
            }
        case .loadElement(_):
            newOp = LoadElement(index: b.genIndex())
        case .storeElement(_):
            newOp = StoreElement(index: b.genIndex())
        case .storeElementWithBinop(_):
            newOp = StoreElementWithBinop(index: b.genIndex(), operator: chooseUniform(from: BinaryOperator.allCases))
        case .storeComputedPropertyWithBinop(_):
            newOp = StoreComputedPropertyWithBinop(operator: chooseUniform(from: BinaryOperator.allCases))
        case .deleteElement(_):
            newOp = DeleteElement(index: b.genIndex())
        case .configureElement(let op):
            // Change the flags or the element index, but don't change the type as that would require changing the inputs as well.
            if probability(0.5) {
                newOp = ConfigureElement(index: b.genIndex(), flags: op.flags, type: op.type)
            } else {
                newOp = ConfigureElement(index: op.index, flags: PropertyFlags.random(), type: op.type)
            }
        case .configureComputedProperty(let op):
            newOp = ConfigureComputedProperty(flags: PropertyFlags.random(), type: op.type)
        case .callFunctionWithSpread(let op):
            var spreads = op.spreads
            assert(!spreads.isEmpty)
            let idx = Int.random(in: 0..<spreads.count)
            spreads[idx] = !spreads[idx]
            newOp = CallFunctionWithSpread(numArguments: op.numArguments, spreads: spreads)
        case .constructWithSpread(let op):
            var spreads = op.spreads
            assert(!spreads.isEmpty)
            let idx = Int.random(in: 0..<spreads.count)
            spreads[idx] = !spreads[idx]
            newOp = ConstructWithSpread(numArguments: op.numArguments, spreads: spreads)
        case .callMethod(let op):
            newOp = CallMethod(methodName: b.genMethodName(), numArguments: op.numArguments)
        case .callMethodWithSpread(let op):
            var spreads = op.spreads
            assert(!spreads.isEmpty)
            let idx = Int.random(in: 0..<spreads.count)
            spreads[idx] = !spreads[idx]
            newOp = CallMethodWithSpread(methodName: b.genMethodName(), numArguments: op.numArguments, spreads: spreads)
        case .callComputedMethodWithSpread(let op):
            var spreads = op.spreads
            assert(!spreads.isEmpty)
            let idx = Int.random(in: 0..<spreads.count)
            spreads[idx] = !spreads[idx]
            newOp = CallComputedMethodWithSpread(numArguments: op.numArguments, spreads: spreads)
        case .unaryOperation(_):
            newOp = UnaryOperation(chooseUniform(from: UnaryOperator.allCases))
        case .binaryOperation(_):
            newOp = BinaryOperation(chooseUniform(from: BinaryOperator.allCases))
        case .reassignWithBinop(_):
            newOp = ReassignWithBinop(chooseUniform(from: BinaryOperator.allCases))
        case .destructArray(let op):
            var newIndices = Set(op.indices)
            replaceRandomElement(in: &newIndices, generatingRandomValuesWith: { return Int64.random(in: 0..<10) })
            newOp = DestructArray(indices: newIndices.sorted(), hasRestElement: !op.hasRestElement)
        case .destructArrayAndReassign(let op):
            var newIndices = Set(op.indices)
            replaceRandomElement(in: &newIndices, generatingRandomValuesWith: { return Int64.random(in: 0..<10) })
            newOp = DestructArrayAndReassign(indices: newIndices.sorted(), hasRestElement: !op.hasRestElement)
        case .destructObject(let op):
            var newProperties = Set(op.properties)
            replaceRandomElement(in: &newProperties, generatingRandomValuesWith: { return b.genPropertyNameForRead() })
            newOp = DestructObject(properties: newProperties.sorted(), hasRestElement: !op.hasRestElement)
        case .destructObjectAndReassign(let op):
            var newProperties = Set(op.properties)
            replaceRandomElement(in: &newProperties, generatingRandomValuesWith: { return b.genPropertyNameForRead() })
            newOp = DestructObjectAndReassign(properties: newProperties.sorted(), hasRestElement: !op.hasRestElement)
        case .compare(_):
            newOp = Compare(chooseUniform(from: Comparator.allCases))
        case .loadFromScope(_):
            newOp = LoadFromScope(id: b.genPropertyNameForRead())
        case .storeToScope(_):
            newOp = StoreToScope(id: b.genPropertyNameForWrite())
        case .callSuperMethod(let op):
            newOp = CallSuperMethod(methodName: b.genMethodName(), numArguments: op.numArguments)
        case .loadSuperProperty(_):
            newOp = LoadSuperProperty(propertyName: b.genPropertyNameForRead())
        case .storeSuperProperty(_):
            newOp = StoreSuperProperty(propertyName: b.genPropertyNameForWrite())
        case .storeSuperPropertyWithBinop(_):
            newOp = StoreSuperPropertyWithBinop(propertyName: b.genPropertyNameForWrite(), operator: chooseUniform(from: BinaryOperator.allCases))
        case .beginIf(let op):
            newOp = BeginIf(inverted: !op.inverted)
        case .beginWhileLoop(_):
            newOp = BeginWhileLoop(comparator: chooseUniform(from: Comparator.allCases))
        case .beginDoWhileLoop(_):
            newOp = BeginDoWhileLoop(comparator: chooseUniform(from: Comparator.allCases))
        case .beginForLoop(let op):
            if probability(0.5) {
                newOp = BeginForLoop(comparator: chooseUniform(from: Comparator.allCases), op: op.op)
            } else {
                newOp = BeginForLoop(comparator: op.comparator, op: chooseUniform(from: BinaryOperator.allCases))
            }
        default:
            fatalError("Unhandled Operation: \(type(of: instr.op))")
        }

        return Instruction(newOp, inouts: instr.inouts)
    }

    private func extendVariadicOperation(_ instr: Instruction, _ b: ProgramBuilder) -> Instruction {
        var instr = instr
        let numInputsToAdd = Int.random(in: 1...3)
        for _ in 0..<numInputsToAdd {
            instr = extendVariadicOperationByOneInput(instr, b)
        }
        return instr
    }

    private func extendVariadicOperationByOneInput(_ instr: Instruction, _ b: ProgramBuilder) -> Instruction {
        // Without visible variables, we can't add a new input to this instruction.
        // This should happen rarely, so just skip this mutation.
        guard b.hasVisibleVariables else { return instr }

        let newOp: Operation
        var inputs = instr.inputs

        switch instr.op.opcode {
        case .createObject(let op):
            var propertyNames = op.propertyNames
            propertyNames.append(b.genPropertyNameForWrite())
            inputs.append(b.randVar())
            newOp = CreateObject(propertyNames: propertyNames)
        case .createArray(let op):
            newOp = CreateArray(numInitialValues: op.numInitialValues + 1)
            inputs.append(b.randVar())
        case .createObjectWithSpread(let op):
            var propertyNames = op.propertyNames
            var numSpreads = op.numSpreads
            if probability(0.5) {
                // Add a new property
                propertyNames.append(b.genPropertyNameForWrite())
                inputs.insert(b.randVar(), at: propertyNames.count - 1)
            } else {
                // Add spread input
                numSpreads += 1
                inputs.append(b.randVar())
            }
            newOp = CreateObjectWithSpread(propertyNames: propertyNames, numSpreads: numSpreads)
        case .createArrayWithSpread(let op):
            let spreads = op.spreads + [Bool.random()]
            inputs.append(b.randVar())
            newOp = CreateArrayWithSpread(spreads: spreads)
        case .callFunction(let op):
            inputs.append(b.randVar())
            newOp = CallFunction(numArguments: op.numArguments + 1)
        case .callFunctionWithSpread(let op):
            let spreads = op.spreads + [Bool.random()]
            inputs.append(b.randVar())
            newOp = CallFunctionWithSpread(numArguments: op.numArguments + 1, spreads: spreads)
        case .construct(let op):
            inputs.append(b.randVar())
            newOp = Construct(numArguments: op.numArguments + 1)
        case .constructWithSpread(let op):
            let spreads = op.spreads + [Bool.random()]
            inputs.append(b.randVar())
            newOp = ConstructWithSpread(numArguments: op.numArguments + 1, spreads: spreads)
        case .callMethod(let op):
            inputs.append(b.randVar())
            newOp = CallMethod(methodName: op.methodName, numArguments: op.numArguments + 1)
        case .callMethodWithSpread(let op):
            let spreads = op.spreads + [Bool.random()]
            inputs.append(b.randVar())
            newOp = CallMethodWithSpread(methodName: op.methodName, numArguments: op.numArguments + 1, spreads: spreads)
        case .callComputedMethod(let op):
            inputs.append(b.randVar())
            newOp = CallComputedMethod(numArguments: op.numArguments + 1)
        case .callComputedMethodWithSpread(let op):
            let spreads = op.spreads + [Bool.random()]
            inputs.append(b.randVar())
            newOp = CallComputedMethodWithSpread(numArguments: op.numArguments + 1, spreads: spreads)
        case .callSuperConstructor(let op):
            inputs.append(b.randVar())
            newOp = CallSuperConstructor(numArguments: op.numArguments + 1)
        case .callSuperMethod(let op):
            inputs.append(b.randVar())
            newOp = CallSuperMethod(methodName: op.methodName, numArguments: op.numArguments + 1)
        case .createTemplateString(let op):
            var parts = op.parts
            parts.append(b.genString())
            inputs.append(b.randVar())
            newOp = CreateTemplateString(parts: parts)
        default:
            fatalError("Unhandled Operation: \(type(of: instr.op))")
        }

        assert(inputs.count != instr.inputs.count)
        let inouts = inputs + instr.outputs + instr.innerOutputs
        return Instruction(newOp, inouts: inouts)
    }

    private func replaceRandomElement<T>(in set: inout Set<T>, generatingRandomValuesWith generator: () -> T) {
        guard let removedElem = set.randomElement() else { return }
        set.remove(removedElem)

        for _ in 0...5 {
            let newElem = generator()
            // Ensure that we neither add an element that already exists nor add one that we just removed
            if !set.contains(newElem) && newElem != removedElem {
                set.insert(newElem)
                return
            }
        }

        // Failed to insert a new element, so just insert the removed element again as we must not change the size of the set
        set.insert(removedElem)
    }
}

public class XXXCodeGenMutator: BaseInstructionMutator {
    var analyzer = DeadCodeAnalyzer()

    public init() {
        super.init(maxSimultaneousMutations: defaultMaxSimultaneousCodeGenerations)
        assert(defaultCodeGenerationAmount >= ProgramBuilder.minBudgetForRecursiveCodeGeneration)
    }

    public override func beginMutation(of program: Program) {
        analyzer = DeadCodeAnalyzer()
    }

    public override func canMutate(_ instr: Instruction) -> Bool {
        analyzer.analyze(instr)
        return !analyzer.currentlyInDeadCode
    }

    public override func mutate(_ instr: Instruction, _ b: ProgramBuilder) {
        b.adopt(instr)
        b.build(n: defaultCodeGenerationAmount, by: .runningGenerators)
    }
}

public class XXXMutatorInternal: Mutator {
    public override init() {}
    
    override func mutate(_ program: Program, using b: ProgramBuilder, for fuzzer: Fuzzer) -> Program? {
        //let pos = Int.random(in: 0..<100)
        return b.finalize()
    }
}


public class XXXMutator: Mutator {
    public override init() {}
    override func mutate(_ program: Program, using b: ProgramBuilder, for fuzzer: Fuzzer) -> Program? {
        //TODO: set mutateID
        //TODO: adjust weight at runtime
        let mymutators = WeightedList([
        (XXXCodeGenMutator(),                  1),
        (XXXInputMutator(isTypeAware: false),  1),
        (XXXInputMutator(isTypeAware: true),   1),
        (XXXOperationMutator(),                1),
        (XXXMutatorInternal(),                 1),
        (CombineMutator(),                     1),
        (JITStressMutator(),                   1),
        (SpliceMutator(),                      1),
        (ExplorationMutator(),                 1),
        (ProbingMutator(),                     1),
        ])
        let mutator = mymutators.randomElement()
        let result = mutator.mutate(program, using: b, for: fuzzer)
        return result
    }
}
