/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "config.h"
#include "JSTestActiveDOMObject.h"

#include "ActiveDOMObject.h"
#include "CustomElementReactionQueue.h"
#include "JSDOMAttribute.h"
#include "JSDOMBinding.h"
#include "JSDOMBindingSecurity.h"
#include "JSDOMConstructorNotConstructable.h"
#include "JSDOMConvertInterface.h"
#include "JSDOMConvertNumbers.h"
#include "JSDOMConvertStrings.h"
#include "JSDOMExceptionHandling.h"
#include "JSDOMOperation.h"
#include "JSDOMWrapperCache.h"
#include "JSNode.h"
#include "ScriptExecutionContext.h"
#include <JavaScriptCore/FunctionPrototype.h>
#include <JavaScriptCore/HeapAnalyzer.h>
#include <JavaScriptCore/JSCInlines.h>
#include <wtf/GetPtr.h>
#include <wtf/PointerPreparations.h>
#include <wtf/URL.h>


namespace WebCore {
using namespace JSC;

// Functions

JSC::EncodedJSValue JSC_HOST_CALL jsTestActiveDOMObjectPrototypeFunctionExcitingFunction(JSC::JSGlobalObject*, JSC::CallFrame*);
JSC::EncodedJSValue JSC_HOST_CALL jsTestActiveDOMObjectPrototypeFunctionPostMessage(JSC::JSGlobalObject*, JSC::CallFrame*);
JSC::EncodedJSValue JSC_HOST_CALL jsTestActiveDOMObjectPrototypeFunctionOverloadedMethod(JSC::JSGlobalObject*, JSC::CallFrame*);

// Attributes

JSC::EncodedJSValue jsTestActiveDOMObjectConstructor(JSC::JSGlobalObject*, JSC::EncodedJSValue, JSC::PropertyName);
bool setJSTestActiveDOMObjectConstructor(JSC::JSGlobalObject*, JSC::EncodedJSValue, JSC::EncodedJSValue);
JSC::EncodedJSValue jsTestActiveDOMObjectExcitingAttr(JSC::JSGlobalObject*, JSC::EncodedJSValue, JSC::PropertyName);

class JSTestActiveDOMObjectPrototype : public JSC::JSNonFinalObject {
public:
    using Base = JSC::JSNonFinalObject;
    static JSTestActiveDOMObjectPrototype* create(JSC::VM& vm, JSDOMGlobalObject* globalObject, JSC::Structure* structure)
    {
        JSTestActiveDOMObjectPrototype* ptr = new (NotNull, JSC::allocateCell<JSTestActiveDOMObjectPrototype>(vm.heap)) JSTestActiveDOMObjectPrototype(vm, globalObject, structure);
        ptr->finishCreation(vm);
        return ptr;
    }

    DECLARE_INFO;
    static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype)
    {
        return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), info());
    }

private:
    JSTestActiveDOMObjectPrototype(JSC::VM& vm, JSC::JSGlobalObject*, JSC::Structure* structure)
        : JSC::JSNonFinalObject(vm, structure)
    {
    }

    void finishCreation(JSC::VM&);
};
STATIC_ASSERT_ISO_SUBSPACE_SHARABLE(JSTestActiveDOMObjectPrototype, JSTestActiveDOMObjectPrototype::Base);

using JSTestActiveDOMObjectConstructor = JSDOMConstructorNotConstructable<JSTestActiveDOMObject>;

/* Hash table */

static const struct CompactHashIndex JSTestActiveDOMObjectTableIndex[2] = {
    { 0, -1 },
    { -1, -1 },
};


static const HashTableValue JSTestActiveDOMObjectTableValues[] =
{
    { "excitingAttr", static_cast<unsigned>(JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::CustomAccessor | JSC::PropertyAttribute::DOMAttribute), NoIntrinsic, { (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestActiveDOMObjectExcitingAttr), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(0) } },
};

static const HashTable JSTestActiveDOMObjectTable = { 1, 1, true, JSTestActiveDOMObject::info(), JSTestActiveDOMObjectTableValues, JSTestActiveDOMObjectTableIndex };
template<> JSValue JSTestActiveDOMObjectConstructor::prototypeForStructure(JSC::VM& vm, const JSDOMGlobalObject& globalObject)
{
    UNUSED_PARAM(vm);
    return globalObject.functionPrototype();
}

template<> void JSTestActiveDOMObjectConstructor::initializeProperties(VM& vm, JSDOMGlobalObject& globalObject)
{
    putDirect(vm, vm.propertyNames->prototype, JSTestActiveDOMObject::prototype(vm, globalObject), JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    putDirect(vm, vm.propertyNames->name, jsNontrivialString(vm, String("TestActiveDOMObject"_s)), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    putDirect(vm, vm.propertyNames->length, jsNumber(0), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
}

template<> const ClassInfo JSTestActiveDOMObjectConstructor::s_info = { "TestActiveDOMObject", &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestActiveDOMObjectConstructor) };

/* Hash table for prototype */

static const HashTableValue JSTestActiveDOMObjectPrototypeTableValues[] =
{
    { "constructor", static_cast<unsigned>(JSC::PropertyAttribute::DontEnum), NoIntrinsic, { (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestActiveDOMObjectConstructor), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(setJSTestActiveDOMObjectConstructor) } },
    { "excitingFunction", static_cast<unsigned>(JSC::PropertyAttribute::Function), NoIntrinsic, { (intptr_t)static_cast<RawNativeFunction>(jsTestActiveDOMObjectPrototypeFunctionExcitingFunction), (intptr_t) (1) } },
    { "postMessage", static_cast<unsigned>(JSC::PropertyAttribute::Function), NoIntrinsic, { (intptr_t)static_cast<RawNativeFunction>(jsTestActiveDOMObjectPrototypeFunctionPostMessage), (intptr_t) (1) } },
    { "overloadedMethod", static_cast<unsigned>(JSC::PropertyAttribute::Function), NoIntrinsic, { (intptr_t)static_cast<RawNativeFunction>(jsTestActiveDOMObjectPrototypeFunctionOverloadedMethod), (intptr_t) (1) } },
};

const ClassInfo JSTestActiveDOMObjectPrototype::s_info = { "TestActiveDOMObjectPrototype", &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestActiveDOMObjectPrototype) };

void JSTestActiveDOMObjectPrototype::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    reifyStaticProperties(vm, JSTestActiveDOMObject::info(), JSTestActiveDOMObjectPrototypeTableValues, *this);
}

const ClassInfo JSTestActiveDOMObject::s_info = { "TestActiveDOMObject", &Base::s_info, &JSTestActiveDOMObjectTable, nullptr, CREATE_METHOD_TABLE(JSTestActiveDOMObject) };

JSTestActiveDOMObject::JSTestActiveDOMObject(Structure* structure, JSDOMGlobalObject& globalObject, Ref<TestActiveDOMObject>&& impl)
    : JSDOMWrapper<TestActiveDOMObject>(structure, globalObject, WTFMove(impl))
{
}

void JSTestActiveDOMObject::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    ASSERT(inherits(vm, info()));

    static_assert(!std::is_base_of<ActiveDOMObject, TestActiveDOMObject>::value, "Interface is not marked as [ActiveDOMObject] even though implementation class subclasses ActiveDOMObject.");

}

JSObject* JSTestActiveDOMObject::createPrototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    return JSTestActiveDOMObjectPrototype::create(vm, &globalObject, JSTestActiveDOMObjectPrototype::createStructure(vm, &globalObject, globalObject.objectPrototype()));
}

JSObject* JSTestActiveDOMObject::prototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    return getDOMPrototype<JSTestActiveDOMObject>(vm, globalObject);
}

JSValue JSTestActiveDOMObject::getConstructor(VM& vm, const JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSTestActiveDOMObjectConstructor>(vm, *jsCast<const JSDOMGlobalObject*>(globalObject));
}

void JSTestActiveDOMObject::destroy(JSC::JSCell* cell)
{
    JSTestActiveDOMObject* thisObject = static_cast<JSTestActiveDOMObject*>(cell);
    thisObject->JSTestActiveDOMObject::~JSTestActiveDOMObject();
}

template<> inline JSTestActiveDOMObject* IDLAttribute<JSTestActiveDOMObject>::cast(JSGlobalObject& lexicalGlobalObject, EncodedJSValue thisValue)
{
    return jsDynamicCast<JSTestActiveDOMObject*>(JSC::getVM(&lexicalGlobalObject), JSValue::decode(thisValue));
}

template<> inline JSTestActiveDOMObject* IDLOperation<JSTestActiveDOMObject>::cast(JSGlobalObject& lexicalGlobalObject, CallFrame& callFrame)
{
    return jsDynamicCast<JSTestActiveDOMObject*>(JSC::getVM(&lexicalGlobalObject), callFrame.thisValue());
}

EncodedJSValue jsTestActiveDOMObjectConstructor(JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName)
{
    VM& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto* prototype = jsDynamicCast<JSTestActiveDOMObjectPrototype*>(vm, JSValue::decode(thisValue));
    if (UNLIKELY(!prototype))
        return throwVMTypeError(lexicalGlobalObject, throwScope);
    return JSValue::encode(JSTestActiveDOMObject::getConstructor(JSC::getVM(lexicalGlobalObject), prototype->globalObject()));
}

bool setJSTestActiveDOMObjectConstructor(JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, EncodedJSValue encodedValue)
{
    VM& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto* prototype = jsDynamicCast<JSTestActiveDOMObjectPrototype*>(vm, JSValue::decode(thisValue));
    if (UNLIKELY(!prototype)) {
        throwVMTypeError(lexicalGlobalObject, throwScope);
        return false;
    }
    // Shadowing a built-in constructor
    return prototype->putDirect(vm, vm.propertyNames->constructor, JSValue::decode(encodedValue));
}

static inline JSValue jsTestActiveDOMObjectExcitingAttrGetter(JSGlobalObject& lexicalGlobalObject, JSTestActiveDOMObject& thisObject, ThrowScope& throwScope)
{
    UNUSED_PARAM(throwScope);
    UNUSED_PARAM(lexicalGlobalObject);
    if (!BindingSecurity::shouldAllowAccessToDOMWindow(&lexicalGlobalObject, thisObject.wrapped().window(), ThrowSecurityError))
        return jsUndefined();
    auto& impl = thisObject.wrapped();
    JSValue result = toJS<IDLLong>(lexicalGlobalObject, throwScope, impl.excitingAttr());
    return result;
}

EncodedJSValue jsTestActiveDOMObjectExcitingAttr(JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName)
{
    return IDLAttribute<JSTestActiveDOMObject>::get<jsTestActiveDOMObjectExcitingAttrGetter, CastedThisErrorBehavior::Assert>(*lexicalGlobalObject, thisValue, "excitingAttr");
}

static inline JSC::EncodedJSValue jsTestActiveDOMObjectPrototypeFunctionExcitingFunctionBody(JSC::JSGlobalObject* lexicalGlobalObject, JSC::CallFrame* callFrame, typename IDLOperation<JSTestActiveDOMObject>::ClassParameter castedThis, JSC::ThrowScope& throwScope)
{
    UNUSED_PARAM(lexicalGlobalObject);
    UNUSED_PARAM(callFrame);
    UNUSED_PARAM(throwScope);
    if (!BindingSecurity::shouldAllowAccessToDOMWindow(lexicalGlobalObject, castedThis->wrapped().window(), ThrowSecurityError))
        return JSValue::encode(jsUndefined());
    auto& impl = castedThis->wrapped();
    if (UNLIKELY(callFrame->argumentCount() < 1))
        return throwVMError(lexicalGlobalObject, throwScope, createNotEnoughArgumentsError(lexicalGlobalObject));
    auto nextChild = convert<IDLInterface<Node>>(*lexicalGlobalObject, callFrame->uncheckedArgument(0), [](JSC::JSGlobalObject& lexicalGlobalObject, JSC::ThrowScope& scope) { throwArgumentTypeError(lexicalGlobalObject, scope, 0, "nextChild", "TestActiveDOMObject", "excitingFunction", "Node"); });
    RETURN_IF_EXCEPTION(throwScope, encodedJSValue());
    impl.excitingFunction(*nextChild);
    return JSValue::encode(jsUndefined());
}

EncodedJSValue JSC_HOST_CALL jsTestActiveDOMObjectPrototypeFunctionExcitingFunction(JSGlobalObject* lexicalGlobalObject, CallFrame* callFrame)
{
    return IDLOperation<JSTestActiveDOMObject>::call<jsTestActiveDOMObjectPrototypeFunctionExcitingFunctionBody>(*lexicalGlobalObject, *callFrame, "excitingFunction");
}

static inline JSC::EncodedJSValue jsTestActiveDOMObjectPrototypeFunctionPostMessageBody(JSC::JSGlobalObject* lexicalGlobalObject, JSC::CallFrame* callFrame, typename IDLOperation<JSTestActiveDOMObject>::ClassParameter castedThis, JSC::ThrowScope& throwScope)
{
    UNUSED_PARAM(lexicalGlobalObject);
    UNUSED_PARAM(callFrame);
    UNUSED_PARAM(throwScope);
    auto& impl = castedThis->wrapped();
    if (UNLIKELY(callFrame->argumentCount() < 1))
        return throwVMError(lexicalGlobalObject, throwScope, createNotEnoughArgumentsError(lexicalGlobalObject));
    auto message = convert<IDLDOMString>(*lexicalGlobalObject, callFrame->uncheckedArgument(0));
    RETURN_IF_EXCEPTION(throwScope, encodedJSValue());
    impl.postMessage(WTFMove(message));
    return JSValue::encode(jsUndefined());
}

EncodedJSValue JSC_HOST_CALL jsTestActiveDOMObjectPrototypeFunctionPostMessage(JSGlobalObject* lexicalGlobalObject, CallFrame* callFrame)
{
    return IDLOperation<JSTestActiveDOMObject>::call<jsTestActiveDOMObjectPrototypeFunctionPostMessageBody>(*lexicalGlobalObject, *callFrame, "postMessage");
}

static inline JSC::EncodedJSValue jsTestActiveDOMObjectPrototypeFunctionOverloadedMethod1Body(JSC::JSGlobalObject* lexicalGlobalObject, JSC::CallFrame* callFrame, typename IDLOperation<JSTestActiveDOMObject>::ClassParameter castedThis, JSC::ThrowScope& throwScope)
{
    UNUSED_PARAM(lexicalGlobalObject);
    UNUSED_PARAM(callFrame);
    UNUSED_PARAM(throwScope);
    CustomElementReactionStack customElementReactionStack(*lexicalGlobalObject);
    auto& impl = castedThis->wrapped();
    auto param = convert<IDLDOMString>(*lexicalGlobalObject, callFrame->uncheckedArgument(0));
    RETURN_IF_EXCEPTION(throwScope, encodedJSValue());
    impl.overloadedMethod(WTFMove(param));
    return JSValue::encode(jsUndefined());
}

static inline JSC::EncodedJSValue jsTestActiveDOMObjectPrototypeFunctionOverloadedMethod2Body(JSC::JSGlobalObject* lexicalGlobalObject, JSC::CallFrame* callFrame, typename IDLOperation<JSTestActiveDOMObject>::ClassParameter castedThis, JSC::ThrowScope& throwScope)
{
    UNUSED_PARAM(lexicalGlobalObject);
    UNUSED_PARAM(callFrame);
    UNUSED_PARAM(throwScope);
    auto& impl = castedThis->wrapped();
    auto param1 = convert<IDLInterface<Node>>(*lexicalGlobalObject, callFrame->uncheckedArgument(0), [](JSC::JSGlobalObject& lexicalGlobalObject, JSC::ThrowScope& scope) { throwArgumentTypeError(lexicalGlobalObject, scope, 0, "param1", "TestActiveDOMObject", "overloadedMethod", "Node"); });
    RETURN_IF_EXCEPTION(throwScope, encodedJSValue());
    auto param2 = convert<IDLInterface<Node>>(*lexicalGlobalObject, callFrame->uncheckedArgument(1), [](JSC::JSGlobalObject& lexicalGlobalObject, JSC::ThrowScope& scope) { throwArgumentTypeError(lexicalGlobalObject, scope, 1, "param2", "TestActiveDOMObject", "overloadedMethod", "Node"); });
    RETURN_IF_EXCEPTION(throwScope, encodedJSValue());
    impl.overloadedMethod(*param1, *param2);
    return JSValue::encode(jsUndefined());
}

static inline JSC::EncodedJSValue jsTestActiveDOMObjectPrototypeFunctionOverloadedMethodOverloadDispatcher(JSC::JSGlobalObject* lexicalGlobalObject, JSC::CallFrame* callFrame, typename IDLOperation<JSTestActiveDOMObject>::ClassParameter castedThis, JSC::ThrowScope& throwScope)
{
    UNUSED_PARAM(lexicalGlobalObject);
    UNUSED_PARAM(callFrame);
    UNUSED_PARAM(throwScope);
    if (!BindingSecurity::shouldAllowAccessToDOMWindow(lexicalGlobalObject, castedThis->wrapped().window(), ThrowSecurityError))
        return JSValue::encode(jsUndefined());
    VM& vm = JSC::getVM(lexicalGlobalObject);
    UNUSED_PARAM(vm);
    size_t argsCount = std::min<size_t>(2, callFrame->argumentCount());
    if (argsCount == 1) {
        return jsTestActiveDOMObjectPrototypeFunctionOverloadedMethod1Body(lexicalGlobalObject, callFrame, castedThis, throwScope);
    }
    if (argsCount == 2) {
        return jsTestActiveDOMObjectPrototypeFunctionOverloadedMethod2Body(lexicalGlobalObject, callFrame, castedThis, throwScope);
    }
    return argsCount < 1 ? throwVMError(lexicalGlobalObject, throwScope, createNotEnoughArgumentsError(lexicalGlobalObject)) : throwVMTypeError(lexicalGlobalObject, throwScope);
}

EncodedJSValue JSC_HOST_CALL jsTestActiveDOMObjectPrototypeFunctionOverloadedMethod(JSGlobalObject* lexicalGlobalObject, CallFrame* callFrame)
{
    return IDLOperation<JSTestActiveDOMObject>::call<jsTestActiveDOMObjectPrototypeFunctionOverloadedMethodOverloadDispatcher>(*lexicalGlobalObject, *callFrame, "overloadedMethod");
}

void JSTestActiveDOMObject::analyzeHeap(JSCell* cell, HeapAnalyzer& analyzer)
{
    auto* thisObject = jsCast<JSTestActiveDOMObject*>(cell);
    analyzer.setWrappedObjectForCell(cell, &thisObject->wrapped());
    if (thisObject->scriptExecutionContext())
        analyzer.setLabelForCell(cell, "url " + thisObject->scriptExecutionContext()->url().string());
    Base::analyzeHeap(cell, analyzer);
}

bool JSTestActiveDOMObjectOwner::isReachableFromOpaqueRoots(JSC::Handle<JSC::Unknown> handle, void*, SlotVisitor& visitor, const char** reason)
{
    UNUSED_PARAM(handle);
    UNUSED_PARAM(visitor);
    UNUSED_PARAM(reason);
    return false;
}

void JSTestActiveDOMObjectOwner::finalize(JSC::Handle<JSC::Unknown> handle, void* context)
{
    auto* jsTestActiveDOMObject = static_cast<JSTestActiveDOMObject*>(handle.slot()->asCell());
    auto& world = *static_cast<DOMWrapperWorld*>(context);
    uncacheWrapper(world, &jsTestActiveDOMObject->wrapped(), jsTestActiveDOMObject);
}

#if ENABLE(BINDING_INTEGRITY)
#if PLATFORM(WIN)
#pragma warning(disable: 4483)
extern "C" { extern void (*const __identifier("??_7TestActiveDOMObject@WebCore@@6B@")[])(); }
#else
extern "C" { extern void* _ZTVN7WebCore19TestActiveDOMObjectE[]; }
#endif
#endif

JSC::JSValue toJSNewlyCreated(JSC::JSGlobalObject*, JSDOMGlobalObject* globalObject, Ref<TestActiveDOMObject>&& impl)
{

#if ENABLE(BINDING_INTEGRITY)
    void* actualVTablePointer = getVTablePointer(impl.ptr());
#if PLATFORM(WIN)
    void* expectedVTablePointer = __identifier("??_7TestActiveDOMObject@WebCore@@6B@");
#else
    void* expectedVTablePointer = &_ZTVN7WebCore19TestActiveDOMObjectE[2];
#endif

    // If this fails TestActiveDOMObject does not have a vtable, so you need to add the
    // ImplementationLacksVTable attribute to the interface definition
    static_assert(std::is_polymorphic<TestActiveDOMObject>::value, "TestActiveDOMObject is not polymorphic");

    // If you hit this assertion you either have a use after free bug, or
    // TestActiveDOMObject has subclasses. If TestActiveDOMObject has subclasses that get passed
    // to toJS() we currently require TestActiveDOMObject you to opt out of binding hardening
    // by adding the SkipVTableValidation attribute to the interface IDL definition
    RELEASE_ASSERT(actualVTablePointer == expectedVTablePointer);
#endif
    return createWrapper<TestActiveDOMObject>(globalObject, WTFMove(impl));
}

JSC::JSValue toJS(JSC::JSGlobalObject* lexicalGlobalObject, JSDOMGlobalObject* globalObject, TestActiveDOMObject& impl)
{
    return wrap(lexicalGlobalObject, globalObject, impl);
}

TestActiveDOMObject* JSTestActiveDOMObject::toWrapped(JSC::VM& vm, JSC::JSValue value)
{
    if (auto* wrapper = jsDynamicCast<JSTestActiveDOMObject*>(vm, value))
        return &wrapper->wrapped();
    return nullptr;
}

}
