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
#include "JSTestEnabledBySetting.h"

#include "ActiveDOMObject.h"
#include "Document.h"
#include "JSDOMAttribute.h"
#include "JSDOMBinding.h"
#include "JSDOMConstructorNotConstructable.h"
#include "JSDOMExceptionHandling.h"
#include "JSDOMOperation.h"
#include "JSDOMWrapperCache.h"
#include "JSTestSubObj.h"
#include "ScriptExecutionContext.h"
#include "Settings.h"
#include "WebCoreJSClientData.h"
#include <JavaScriptCore/FunctionPrototype.h>
#include <JavaScriptCore/HeapAnalyzer.h>
#include <JavaScriptCore/JSCInlines.h>
#include <wtf/GetPtr.h>
#include <wtf/PointerPreparations.h>
#include <wtf/URL.h>

#if ENABLE(TEST_FEATURE)
#include "JSDOMConvertStrings.h"
#endif


namespace WebCore {
using namespace JSC;

// Functions

#if ENABLE(TEST_FEATURE)
JSC::EncodedJSValue JSC_HOST_CALL jsTestEnabledBySettingPrototypeFunctionEnabledBySettingOperation(JSC::JSGlobalObject*, JSC::CallFrame*);
#endif

// Attributes

JSC::EncodedJSValue jsTestEnabledBySettingConstructor(JSC::JSGlobalObject*, JSC::EncodedJSValue, JSC::PropertyName);
bool setJSTestEnabledBySettingConstructor(JSC::JSGlobalObject*, JSC::EncodedJSValue, JSC::EncodedJSValue);
JSC::EncodedJSValue jsTestEnabledBySettingTestSubObjEnabledBySettingConstructor(JSC::JSGlobalObject*, JSC::EncodedJSValue, JSC::PropertyName);
bool setJSTestEnabledBySettingTestSubObjEnabledBySettingConstructor(JSC::JSGlobalObject*, JSC::EncodedJSValue, JSC::EncodedJSValue);
#if ENABLE(TEST_FEATURE)
JSC::EncodedJSValue jsTestEnabledBySettingEnabledBySettingAttribute(JSC::JSGlobalObject*, JSC::EncodedJSValue, JSC::PropertyName);
bool setJSTestEnabledBySettingEnabledBySettingAttribute(JSC::JSGlobalObject*, JSC::EncodedJSValue, JSC::EncodedJSValue);
#endif

class JSTestEnabledBySettingPrototype : public JSC::JSNonFinalObject {
public:
    using Base = JSC::JSNonFinalObject;
    static JSTestEnabledBySettingPrototype* create(JSC::VM& vm, JSDOMGlobalObject* globalObject, JSC::Structure* structure)
    {
        JSTestEnabledBySettingPrototype* ptr = new (NotNull, JSC::allocateCell<JSTestEnabledBySettingPrototype>(vm.heap)) JSTestEnabledBySettingPrototype(vm, globalObject, structure);
        ptr->finishCreation(vm);
        return ptr;
    }

    DECLARE_INFO;
    static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype)
    {
        return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), info());
    }

private:
    JSTestEnabledBySettingPrototype(JSC::VM& vm, JSC::JSGlobalObject*, JSC::Structure* structure)
        : JSC::JSNonFinalObject(vm, structure)
    {
    }

    void finishCreation(JSC::VM&);
};
STATIC_ASSERT_ISO_SUBSPACE_SHARABLE(JSTestEnabledBySettingPrototype, JSTestEnabledBySettingPrototype::Base);

using JSTestEnabledBySettingConstructor = JSDOMConstructorNotConstructable<JSTestEnabledBySetting>;

template<> JSValue JSTestEnabledBySettingConstructor::prototypeForStructure(JSC::VM& vm, const JSDOMGlobalObject& globalObject)
{
    UNUSED_PARAM(vm);
    return globalObject.functionPrototype();
}

template<> void JSTestEnabledBySettingConstructor::initializeProperties(VM& vm, JSDOMGlobalObject& globalObject)
{
    putDirect(vm, vm.propertyNames->prototype, JSTestEnabledBySetting::prototype(vm, globalObject), JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    putDirect(vm, vm.propertyNames->name, jsNontrivialString(vm, String("TestEnabledBySetting"_s)), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    putDirect(vm, vm.propertyNames->length, jsNumber(0), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
}

template<> const ClassInfo JSTestEnabledBySettingConstructor::s_info = { "TestEnabledBySetting", &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestEnabledBySettingConstructor) };

/* Hash table for prototype */

static const HashTableValue JSTestEnabledBySettingPrototypeTableValues[] =
{
    { "constructor", static_cast<unsigned>(JSC::PropertyAttribute::DontEnum), NoIntrinsic, { (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestEnabledBySettingConstructor), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(setJSTestEnabledBySettingConstructor) } },
#if ENABLE(TEST_FEATURE)
    { "enabledBySettingAttribute", static_cast<unsigned>(JSC::PropertyAttribute::CustomAccessor | JSC::PropertyAttribute::DOMAttribute), NoIntrinsic, { (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestEnabledBySettingEnabledBySettingAttribute), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(setJSTestEnabledBySettingEnabledBySettingAttribute) } },
#else
    { 0, 0, NoIntrinsic, { 0, 0 } },
#endif
#if ENABLE(TEST_FEATURE)
    { "enabledBySettingOperation", static_cast<unsigned>(JSC::PropertyAttribute::Function), NoIntrinsic, { (intptr_t)static_cast<RawNativeFunction>(jsTestEnabledBySettingPrototypeFunctionEnabledBySettingOperation), (intptr_t) (1) } },
#else
    { 0, 0, NoIntrinsic, { 0, 0 } },
#endif
};

const ClassInfo JSTestEnabledBySettingPrototype::s_info = { "TestEnabledBySettingPrototype", &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestEnabledBySettingPrototype) };

void JSTestEnabledBySettingPrototype::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    reifyStaticProperties(vm, JSTestEnabledBySetting::info(), JSTestEnabledBySettingPrototypeTableValues, *this);
    bool hasDisabledRuntimeProperties = false;
#if ENABLE(TEST_FEATURE)
    if (!downcast<Document>(jsCast<JSDOMGlobalObject*>(globalObject())->scriptExecutionContext())->settings().testSettingEnabled()) {
        hasDisabledRuntimeProperties = true;
        auto propertyName = Identifier::fromString(vm, reinterpret_cast<const LChar*>("enabledBySettingOperation"), strlen("enabledBySettingOperation"));
        VM::DeletePropertyModeScope scope(vm, VM::DeletePropertyMode::IgnoreConfigurable);
        JSObject::deleteProperty(this, globalObject(), propertyName);
    }
#endif
#if ENABLE(TEST_FEATURE)
    if (!downcast<Document>(jsCast<JSDOMGlobalObject*>(globalObject())->scriptExecutionContext())->settings().testSettingEnabled()) {
        hasDisabledRuntimeProperties = true;
        auto propertyName = Identifier::fromString(vm, reinterpret_cast<const LChar*>("enabledBySettingAttribute"), strlen("enabledBySettingAttribute"));
        VM::DeletePropertyModeScope scope(vm, VM::DeletePropertyMode::IgnoreConfigurable);
        JSObject::deleteProperty(this, globalObject(), propertyName);
    }
#endif
    if (hasDisabledRuntimeProperties && structure()->isDictionary())
        flattenDictionaryObject(vm);
}

const ClassInfo JSTestEnabledBySetting::s_info = { "TestEnabledBySetting", &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestEnabledBySetting) };

JSTestEnabledBySetting::JSTestEnabledBySetting(Structure* structure, JSDOMGlobalObject& globalObject, Ref<TestEnabledBySetting>&& impl)
    : JSDOMWrapper<TestEnabledBySetting>(structure, globalObject, WTFMove(impl))
{
}

void JSTestEnabledBySetting::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    ASSERT(inherits(vm, info()));

    static_assert(!std::is_base_of<ActiveDOMObject, TestEnabledBySetting>::value, "Interface is not marked as [ActiveDOMObject] even though implementation class subclasses ActiveDOMObject.");

    if (downcast<Document>(jsCast<JSDOMGlobalObject*>(globalObject())->scriptExecutionContext())->settings().testSettingEnabled())
        putDirectCustomAccessor(vm, static_cast<JSVMClientData*>(vm.clientData)->builtinNames().TestSubObjEnabledBySettingPublicName(), CustomGetterSetter::create(vm, jsTestEnabledBySettingTestSubObjEnabledBySettingConstructor, setJSTestEnabledBySettingTestSubObjEnabledBySettingConstructor), attributesForStructure(static_cast<unsigned>(JSC::PropertyAttribute::DontEnum)));
}

JSObject* JSTestEnabledBySetting::createPrototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    return JSTestEnabledBySettingPrototype::create(vm, &globalObject, JSTestEnabledBySettingPrototype::createStructure(vm, &globalObject, globalObject.objectPrototype()));
}

JSObject* JSTestEnabledBySetting::prototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    return getDOMPrototype<JSTestEnabledBySetting>(vm, globalObject);
}

JSValue JSTestEnabledBySetting::getConstructor(VM& vm, const JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSTestEnabledBySettingConstructor>(vm, *jsCast<const JSDOMGlobalObject*>(globalObject));
}

void JSTestEnabledBySetting::destroy(JSC::JSCell* cell)
{
    JSTestEnabledBySetting* thisObject = static_cast<JSTestEnabledBySetting*>(cell);
    thisObject->JSTestEnabledBySetting::~JSTestEnabledBySetting();
}

template<> inline JSTestEnabledBySetting* IDLAttribute<JSTestEnabledBySetting>::cast(JSGlobalObject& lexicalGlobalObject, EncodedJSValue thisValue)
{
    return jsDynamicCast<JSTestEnabledBySetting*>(JSC::getVM(&lexicalGlobalObject), JSValue::decode(thisValue));
}

template<> inline JSTestEnabledBySetting* IDLOperation<JSTestEnabledBySetting>::cast(JSGlobalObject& lexicalGlobalObject, CallFrame& callFrame)
{
    return jsDynamicCast<JSTestEnabledBySetting*>(JSC::getVM(&lexicalGlobalObject), callFrame.thisValue());
}

EncodedJSValue jsTestEnabledBySettingConstructor(JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName)
{
    VM& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto* prototype = jsDynamicCast<JSTestEnabledBySettingPrototype*>(vm, JSValue::decode(thisValue));
    if (UNLIKELY(!prototype))
        return throwVMTypeError(lexicalGlobalObject, throwScope);
    return JSValue::encode(JSTestEnabledBySetting::getConstructor(JSC::getVM(lexicalGlobalObject), prototype->globalObject()));
}

bool setJSTestEnabledBySettingConstructor(JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, EncodedJSValue encodedValue)
{
    VM& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto* prototype = jsDynamicCast<JSTestEnabledBySettingPrototype*>(vm, JSValue::decode(thisValue));
    if (UNLIKELY(!prototype)) {
        throwVMTypeError(lexicalGlobalObject, throwScope);
        return false;
    }
    // Shadowing a built-in constructor
    return prototype->putDirect(vm, vm.propertyNames->constructor, JSValue::decode(encodedValue));
}

static inline JSValue jsTestEnabledBySettingTestSubObjEnabledBySettingConstructorGetter(JSGlobalObject& lexicalGlobalObject, JSTestEnabledBySetting& thisObject, ThrowScope& throwScope)
{
    UNUSED_PARAM(throwScope);
    UNUSED_PARAM(lexicalGlobalObject);
    return JSTestSubObj::getConstructor(JSC::getVM(&lexicalGlobalObject), thisObject.globalObject());
}

EncodedJSValue jsTestEnabledBySettingTestSubObjEnabledBySettingConstructor(JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName)
{
    return IDLAttribute<JSTestEnabledBySetting>::get<jsTestEnabledBySettingTestSubObjEnabledBySettingConstructorGetter>(*lexicalGlobalObject, thisValue, "TestSubObjEnabledBySetting");
}

static inline bool setJSTestEnabledBySettingTestSubObjEnabledBySettingConstructorSetter(JSGlobalObject& lexicalGlobalObject, JSTestEnabledBySetting& thisObject, JSValue value, ThrowScope& throwScope)
{
    UNUSED_PARAM(lexicalGlobalObject);
    VM& vm = throwScope.vm();
    // Shadowing a built-in constructor.
    return thisObject.putDirect(vm, Identifier::fromString(vm, reinterpret_cast<const LChar*>("TestSubObjEnabledBySetting"), strlen("TestSubObjEnabledBySetting")), value);
}

bool setJSTestEnabledBySettingTestSubObjEnabledBySettingConstructor(JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, EncodedJSValue encodedValue)
{
    return IDLAttribute<JSTestEnabledBySetting>::set<setJSTestEnabledBySettingTestSubObjEnabledBySettingConstructorSetter>(*lexicalGlobalObject, thisValue, encodedValue, "TestSubObjEnabledBySetting");
}

#if ENABLE(TEST_FEATURE)
static inline JSValue jsTestEnabledBySettingEnabledBySettingAttributeGetter(JSGlobalObject& lexicalGlobalObject, JSTestEnabledBySetting& thisObject, ThrowScope& throwScope)
{
    UNUSED_PARAM(throwScope);
    UNUSED_PARAM(lexicalGlobalObject);
    auto& impl = thisObject.wrapped();
    JSValue result = toJS<IDLDOMString>(lexicalGlobalObject, throwScope, impl.enabledBySettingAttribute());
    return result;
}

EncodedJSValue jsTestEnabledBySettingEnabledBySettingAttribute(JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName)
{
    return IDLAttribute<JSTestEnabledBySetting>::get<jsTestEnabledBySettingEnabledBySettingAttributeGetter, CastedThisErrorBehavior::Assert>(*lexicalGlobalObject, thisValue, "enabledBySettingAttribute");
}

#endif

#if ENABLE(TEST_FEATURE)
static inline bool setJSTestEnabledBySettingEnabledBySettingAttributeSetter(JSGlobalObject& lexicalGlobalObject, JSTestEnabledBySetting& thisObject, JSValue value, ThrowScope& throwScope)
{
    UNUSED_PARAM(lexicalGlobalObject);
    UNUSED_PARAM(throwScope);
    auto& impl = thisObject.wrapped();
    auto nativeValue = convert<IDLDOMString>(lexicalGlobalObject, value);
    RETURN_IF_EXCEPTION(throwScope, false);
    AttributeSetter::call(lexicalGlobalObject, throwScope, [&] {
        return impl.setEnabledBySettingAttribute(WTFMove(nativeValue));
    });
    return true;
}

bool setJSTestEnabledBySettingEnabledBySettingAttribute(JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, EncodedJSValue encodedValue)
{
    return IDLAttribute<JSTestEnabledBySetting>::set<setJSTestEnabledBySettingEnabledBySettingAttributeSetter>(*lexicalGlobalObject, thisValue, encodedValue, "enabledBySettingAttribute");
}

#endif

#if ENABLE(TEST_FEATURE)
static inline JSC::EncodedJSValue jsTestEnabledBySettingPrototypeFunctionEnabledBySettingOperationBody(JSC::JSGlobalObject* lexicalGlobalObject, JSC::CallFrame* callFrame, typename IDLOperation<JSTestEnabledBySetting>::ClassParameter castedThis, JSC::ThrowScope& throwScope)
{
    UNUSED_PARAM(lexicalGlobalObject);
    UNUSED_PARAM(callFrame);
    UNUSED_PARAM(throwScope);
    auto& impl = castedThis->wrapped();
    if (UNLIKELY(callFrame->argumentCount() < 1))
        return throwVMError(lexicalGlobalObject, throwScope, createNotEnoughArgumentsError(lexicalGlobalObject));
    auto testParam = convert<IDLDOMString>(*lexicalGlobalObject, callFrame->uncheckedArgument(0));
    RETURN_IF_EXCEPTION(throwScope, encodedJSValue());
    impl.enabledBySettingOperation(WTFMove(testParam));
    return JSValue::encode(jsUndefined());
}

EncodedJSValue JSC_HOST_CALL jsTestEnabledBySettingPrototypeFunctionEnabledBySettingOperation(JSGlobalObject* lexicalGlobalObject, CallFrame* callFrame)
{
    return IDLOperation<JSTestEnabledBySetting>::call<jsTestEnabledBySettingPrototypeFunctionEnabledBySettingOperationBody>(*lexicalGlobalObject, *callFrame, "enabledBySettingOperation");
}

#endif

void JSTestEnabledBySetting::analyzeHeap(JSCell* cell, HeapAnalyzer& analyzer)
{
    auto* thisObject = jsCast<JSTestEnabledBySetting*>(cell);
    analyzer.setWrappedObjectForCell(cell, &thisObject->wrapped());
    if (thisObject->scriptExecutionContext())
        analyzer.setLabelForCell(cell, "url " + thisObject->scriptExecutionContext()->url().string());
    Base::analyzeHeap(cell, analyzer);
}

bool JSTestEnabledBySettingOwner::isReachableFromOpaqueRoots(JSC::Handle<JSC::Unknown> handle, void*, SlotVisitor& visitor, const char** reason)
{
    UNUSED_PARAM(handle);
    UNUSED_PARAM(visitor);
    UNUSED_PARAM(reason);
    return false;
}

void JSTestEnabledBySettingOwner::finalize(JSC::Handle<JSC::Unknown> handle, void* context)
{
    auto* jsTestEnabledBySetting = static_cast<JSTestEnabledBySetting*>(handle.slot()->asCell());
    auto& world = *static_cast<DOMWrapperWorld*>(context);
    uncacheWrapper(world, &jsTestEnabledBySetting->wrapped(), jsTestEnabledBySetting);
}

#if ENABLE(BINDING_INTEGRITY)
#if PLATFORM(WIN)
#pragma warning(disable: 4483)
extern "C" { extern void (*const __identifier("??_7TestEnabledBySetting@WebCore@@6B@")[])(); }
#else
extern "C" { extern void* _ZTVN7WebCore20TestEnabledBySettingE[]; }
#endif
#endif

JSC::JSValue toJSNewlyCreated(JSC::JSGlobalObject*, JSDOMGlobalObject* globalObject, Ref<TestEnabledBySetting>&& impl)
{

#if ENABLE(BINDING_INTEGRITY)
    void* actualVTablePointer = getVTablePointer(impl.ptr());
#if PLATFORM(WIN)
    void* expectedVTablePointer = __identifier("??_7TestEnabledBySetting@WebCore@@6B@");
#else
    void* expectedVTablePointer = &_ZTVN7WebCore20TestEnabledBySettingE[2];
#endif

    // If this fails TestEnabledBySetting does not have a vtable, so you need to add the
    // ImplementationLacksVTable attribute to the interface definition
    static_assert(std::is_polymorphic<TestEnabledBySetting>::value, "TestEnabledBySetting is not polymorphic");

    // If you hit this assertion you either have a use after free bug, or
    // TestEnabledBySetting has subclasses. If TestEnabledBySetting has subclasses that get passed
    // to toJS() we currently require TestEnabledBySetting you to opt out of binding hardening
    // by adding the SkipVTableValidation attribute to the interface IDL definition
    RELEASE_ASSERT(actualVTablePointer == expectedVTablePointer);
#endif
    return createWrapper<TestEnabledBySetting>(globalObject, WTFMove(impl));
}

JSC::JSValue toJS(JSC::JSGlobalObject* lexicalGlobalObject, JSDOMGlobalObject* globalObject, TestEnabledBySetting& impl)
{
    return wrap(lexicalGlobalObject, globalObject, impl);
}

TestEnabledBySetting* JSTestEnabledBySetting::toWrapped(JSC::VM& vm, JSC::JSValue value)
{
    if (auto* wrapper = jsDynamicCast<JSTestEnabledBySetting*>(vm, value))
        return &wrapper->wrapped();
    return nullptr;
}

}
