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
#include "JSTestStringifierOperationImplementedAs.h"

#include "ActiveDOMObject.h"
#include "JSDOMBinding.h"
#include "JSDOMConstructorNotConstructable.h"
#include "JSDOMConvertStrings.h"
#include "JSDOMExceptionHandling.h"
#include "JSDOMOperation.h"
#include "JSDOMWrapperCache.h"
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

JSC::EncodedJSValue JSC_HOST_CALL jsTestStringifierOperationImplementedAsPrototypeFunctionIdentifier(JSC::JSGlobalObject*, JSC::CallFrame*);
JSC::EncodedJSValue JSC_HOST_CALL jsTestStringifierOperationImplementedAsPrototypeFunctionToString(JSC::JSGlobalObject*, JSC::CallFrame*);

// Attributes

JSC::EncodedJSValue jsTestStringifierOperationImplementedAsConstructor(JSC::JSGlobalObject*, JSC::EncodedJSValue, JSC::PropertyName);
bool setJSTestStringifierOperationImplementedAsConstructor(JSC::JSGlobalObject*, JSC::EncodedJSValue, JSC::EncodedJSValue);

class JSTestStringifierOperationImplementedAsPrototype : public JSC::JSNonFinalObject {
public:
    using Base = JSC::JSNonFinalObject;
    static JSTestStringifierOperationImplementedAsPrototype* create(JSC::VM& vm, JSDOMGlobalObject* globalObject, JSC::Structure* structure)
    {
        JSTestStringifierOperationImplementedAsPrototype* ptr = new (NotNull, JSC::allocateCell<JSTestStringifierOperationImplementedAsPrototype>(vm.heap)) JSTestStringifierOperationImplementedAsPrototype(vm, globalObject, structure);
        ptr->finishCreation(vm);
        return ptr;
    }

    DECLARE_INFO;
    static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype)
    {
        return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), info());
    }

private:
    JSTestStringifierOperationImplementedAsPrototype(JSC::VM& vm, JSC::JSGlobalObject*, JSC::Structure* structure)
        : JSC::JSNonFinalObject(vm, structure)
    {
    }

    void finishCreation(JSC::VM&);
};
STATIC_ASSERT_ISO_SUBSPACE_SHARABLE(JSTestStringifierOperationImplementedAsPrototype, JSTestStringifierOperationImplementedAsPrototype::Base);

using JSTestStringifierOperationImplementedAsConstructor = JSDOMConstructorNotConstructable<JSTestStringifierOperationImplementedAs>;

template<> JSValue JSTestStringifierOperationImplementedAsConstructor::prototypeForStructure(JSC::VM& vm, const JSDOMGlobalObject& globalObject)
{
    UNUSED_PARAM(vm);
    return globalObject.functionPrototype();
}

template<> void JSTestStringifierOperationImplementedAsConstructor::initializeProperties(VM& vm, JSDOMGlobalObject& globalObject)
{
    putDirect(vm, vm.propertyNames->prototype, JSTestStringifierOperationImplementedAs::prototype(vm, globalObject), JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    putDirect(vm, vm.propertyNames->name, jsNontrivialString(vm, String("TestStringifierOperationImplementedAs"_s)), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    putDirect(vm, vm.propertyNames->length, jsNumber(0), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
}

template<> const ClassInfo JSTestStringifierOperationImplementedAsConstructor::s_info = { "TestStringifierOperationImplementedAs", &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestStringifierOperationImplementedAsConstructor) };

/* Hash table for prototype */

static const HashTableValue JSTestStringifierOperationImplementedAsPrototypeTableValues[] =
{
    { "constructor", static_cast<unsigned>(JSC::PropertyAttribute::DontEnum), NoIntrinsic, { (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestStringifierOperationImplementedAsConstructor), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(setJSTestStringifierOperationImplementedAsConstructor) } },
    { "identifier", static_cast<unsigned>(JSC::PropertyAttribute::Function), NoIntrinsic, { (intptr_t)static_cast<RawNativeFunction>(jsTestStringifierOperationImplementedAsPrototypeFunctionIdentifier), (intptr_t) (0) } },
    { "toString", static_cast<unsigned>(JSC::PropertyAttribute::Function), NoIntrinsic, { (intptr_t)static_cast<RawNativeFunction>(jsTestStringifierOperationImplementedAsPrototypeFunctionToString), (intptr_t) (0) } },
};

const ClassInfo JSTestStringifierOperationImplementedAsPrototype::s_info = { "TestStringifierOperationImplementedAsPrototype", &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestStringifierOperationImplementedAsPrototype) };

void JSTestStringifierOperationImplementedAsPrototype::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    reifyStaticProperties(vm, JSTestStringifierOperationImplementedAs::info(), JSTestStringifierOperationImplementedAsPrototypeTableValues, *this);
}

const ClassInfo JSTestStringifierOperationImplementedAs::s_info = { "TestStringifierOperationImplementedAs", &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestStringifierOperationImplementedAs) };

JSTestStringifierOperationImplementedAs::JSTestStringifierOperationImplementedAs(Structure* structure, JSDOMGlobalObject& globalObject, Ref<TestStringifierOperationImplementedAs>&& impl)
    : JSDOMWrapper<TestStringifierOperationImplementedAs>(structure, globalObject, WTFMove(impl))
{
}

void JSTestStringifierOperationImplementedAs::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    ASSERT(inherits(vm, info()));

    static_assert(!std::is_base_of<ActiveDOMObject, TestStringifierOperationImplementedAs>::value, "Interface is not marked as [ActiveDOMObject] even though implementation class subclasses ActiveDOMObject.");

}

JSObject* JSTestStringifierOperationImplementedAs::createPrototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    return JSTestStringifierOperationImplementedAsPrototype::create(vm, &globalObject, JSTestStringifierOperationImplementedAsPrototype::createStructure(vm, &globalObject, globalObject.objectPrototype()));
}

JSObject* JSTestStringifierOperationImplementedAs::prototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    return getDOMPrototype<JSTestStringifierOperationImplementedAs>(vm, globalObject);
}

JSValue JSTestStringifierOperationImplementedAs::getConstructor(VM& vm, const JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSTestStringifierOperationImplementedAsConstructor>(vm, *jsCast<const JSDOMGlobalObject*>(globalObject));
}

void JSTestStringifierOperationImplementedAs::destroy(JSC::JSCell* cell)
{
    JSTestStringifierOperationImplementedAs* thisObject = static_cast<JSTestStringifierOperationImplementedAs*>(cell);
    thisObject->JSTestStringifierOperationImplementedAs::~JSTestStringifierOperationImplementedAs();
}

template<> inline JSTestStringifierOperationImplementedAs* IDLOperation<JSTestStringifierOperationImplementedAs>::cast(JSGlobalObject& lexicalGlobalObject, CallFrame& callFrame)
{
    return jsDynamicCast<JSTestStringifierOperationImplementedAs*>(JSC::getVM(&lexicalGlobalObject), callFrame.thisValue());
}

EncodedJSValue jsTestStringifierOperationImplementedAsConstructor(JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName)
{
    VM& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto* prototype = jsDynamicCast<JSTestStringifierOperationImplementedAsPrototype*>(vm, JSValue::decode(thisValue));
    if (UNLIKELY(!prototype))
        return throwVMTypeError(lexicalGlobalObject, throwScope);
    return JSValue::encode(JSTestStringifierOperationImplementedAs::getConstructor(JSC::getVM(lexicalGlobalObject), prototype->globalObject()));
}

bool setJSTestStringifierOperationImplementedAsConstructor(JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, EncodedJSValue encodedValue)
{
    VM& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto* prototype = jsDynamicCast<JSTestStringifierOperationImplementedAsPrototype*>(vm, JSValue::decode(thisValue));
    if (UNLIKELY(!prototype)) {
        throwVMTypeError(lexicalGlobalObject, throwScope);
        return false;
    }
    // Shadowing a built-in constructor
    return prototype->putDirect(vm, vm.propertyNames->constructor, JSValue::decode(encodedValue));
}

static inline JSC::EncodedJSValue jsTestStringifierOperationImplementedAsPrototypeFunctionIdentifierBody(JSC::JSGlobalObject* lexicalGlobalObject, JSC::CallFrame* callFrame, typename IDLOperation<JSTestStringifierOperationImplementedAs>::ClassParameter castedThis, JSC::ThrowScope& throwScope)
{
    UNUSED_PARAM(lexicalGlobalObject);
    UNUSED_PARAM(callFrame);
    UNUSED_PARAM(throwScope);
    auto& impl = castedThis->wrapped();
    return JSValue::encode(toJS<IDLDOMString>(*lexicalGlobalObject, impl.alternateIdentifier()));
}

EncodedJSValue JSC_HOST_CALL jsTestStringifierOperationImplementedAsPrototypeFunctionIdentifier(JSGlobalObject* lexicalGlobalObject, CallFrame* callFrame)
{
    return IDLOperation<JSTestStringifierOperationImplementedAs>::call<jsTestStringifierOperationImplementedAsPrototypeFunctionIdentifierBody>(*lexicalGlobalObject, *callFrame, "identifier");
}

static inline JSC::EncodedJSValue jsTestStringifierOperationImplementedAsPrototypeFunctionToStringBody(JSC::JSGlobalObject* lexicalGlobalObject, JSC::CallFrame* callFrame, typename IDLOperation<JSTestStringifierOperationImplementedAs>::ClassParameter castedThis, JSC::ThrowScope& throwScope)
{
    UNUSED_PARAM(lexicalGlobalObject);
    UNUSED_PARAM(callFrame);
    UNUSED_PARAM(throwScope);
    auto& impl = castedThis->wrapped();
    return JSValue::encode(toJS<IDLDOMString>(*lexicalGlobalObject, impl.alternateIdentifier()));
}

EncodedJSValue JSC_HOST_CALL jsTestStringifierOperationImplementedAsPrototypeFunctionToString(JSGlobalObject* lexicalGlobalObject, CallFrame* callFrame)
{
    return IDLOperation<JSTestStringifierOperationImplementedAs>::call<jsTestStringifierOperationImplementedAsPrototypeFunctionToStringBody>(*lexicalGlobalObject, *callFrame, "toString");
}

void JSTestStringifierOperationImplementedAs::analyzeHeap(JSCell* cell, HeapAnalyzer& analyzer)
{
    auto* thisObject = jsCast<JSTestStringifierOperationImplementedAs*>(cell);
    analyzer.setWrappedObjectForCell(cell, &thisObject->wrapped());
    if (thisObject->scriptExecutionContext())
        analyzer.setLabelForCell(cell, "url " + thisObject->scriptExecutionContext()->url().string());
    Base::analyzeHeap(cell, analyzer);
}

bool JSTestStringifierOperationImplementedAsOwner::isReachableFromOpaqueRoots(JSC::Handle<JSC::Unknown> handle, void*, SlotVisitor& visitor, const char** reason)
{
    UNUSED_PARAM(handle);
    UNUSED_PARAM(visitor);
    UNUSED_PARAM(reason);
    return false;
}

void JSTestStringifierOperationImplementedAsOwner::finalize(JSC::Handle<JSC::Unknown> handle, void* context)
{
    auto* jsTestStringifierOperationImplementedAs = static_cast<JSTestStringifierOperationImplementedAs*>(handle.slot()->asCell());
    auto& world = *static_cast<DOMWrapperWorld*>(context);
    uncacheWrapper(world, &jsTestStringifierOperationImplementedAs->wrapped(), jsTestStringifierOperationImplementedAs);
}

#if ENABLE(BINDING_INTEGRITY)
#if PLATFORM(WIN)
#pragma warning(disable: 4483)
extern "C" { extern void (*const __identifier("??_7TestStringifierOperationImplementedAs@WebCore@@6B@")[])(); }
#else
extern "C" { extern void* _ZTVN7WebCore37TestStringifierOperationImplementedAsE[]; }
#endif
#endif

JSC::JSValue toJSNewlyCreated(JSC::JSGlobalObject*, JSDOMGlobalObject* globalObject, Ref<TestStringifierOperationImplementedAs>&& impl)
{

#if ENABLE(BINDING_INTEGRITY)
    void* actualVTablePointer = getVTablePointer(impl.ptr());
#if PLATFORM(WIN)
    void* expectedVTablePointer = __identifier("??_7TestStringifierOperationImplementedAs@WebCore@@6B@");
#else
    void* expectedVTablePointer = &_ZTVN7WebCore37TestStringifierOperationImplementedAsE[2];
#endif

    // If this fails TestStringifierOperationImplementedAs does not have a vtable, so you need to add the
    // ImplementationLacksVTable attribute to the interface definition
    static_assert(std::is_polymorphic<TestStringifierOperationImplementedAs>::value, "TestStringifierOperationImplementedAs is not polymorphic");

    // If you hit this assertion you either have a use after free bug, or
    // TestStringifierOperationImplementedAs has subclasses. If TestStringifierOperationImplementedAs has subclasses that get passed
    // to toJS() we currently require TestStringifierOperationImplementedAs you to opt out of binding hardening
    // by adding the SkipVTableValidation attribute to the interface IDL definition
    RELEASE_ASSERT(actualVTablePointer == expectedVTablePointer);
#endif
    return createWrapper<TestStringifierOperationImplementedAs>(globalObject, WTFMove(impl));
}

JSC::JSValue toJS(JSC::JSGlobalObject* lexicalGlobalObject, JSDOMGlobalObject* globalObject, TestStringifierOperationImplementedAs& impl)
{
    return wrap(lexicalGlobalObject, globalObject, impl);
}

TestStringifierOperationImplementedAs* JSTestStringifierOperationImplementedAs::toWrapped(JSC::VM& vm, JSC::JSValue value)
{
    if (auto* wrapper = jsDynamicCast<JSTestStringifierOperationImplementedAs*>(vm, value))
        return &wrapper->wrapped();
    return nullptr;
}

}
