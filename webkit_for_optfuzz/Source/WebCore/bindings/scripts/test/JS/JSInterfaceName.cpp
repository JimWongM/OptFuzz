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
#include "JSInterfaceName.h"

#include "ActiveDOMObject.h"
#include "JSDOMBinding.h"
#include "JSDOMConstructorNotConstructable.h"
#include "JSDOMExceptionHandling.h"
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

// Attributes

JSC::EncodedJSValue jsInterfaceNameConstructor(JSC::JSGlobalObject*, JSC::EncodedJSValue, JSC::PropertyName);
bool setJSInterfaceNameConstructor(JSC::JSGlobalObject*, JSC::EncodedJSValue, JSC::EncodedJSValue);

class JSInterfaceNamePrototype : public JSC::JSNonFinalObject {
public:
    using Base = JSC::JSNonFinalObject;
    static JSInterfaceNamePrototype* create(JSC::VM& vm, JSDOMGlobalObject* globalObject, JSC::Structure* structure)
    {
        JSInterfaceNamePrototype* ptr = new (NotNull, JSC::allocateCell<JSInterfaceNamePrototype>(vm.heap)) JSInterfaceNamePrototype(vm, globalObject, structure);
        ptr->finishCreation(vm);
        return ptr;
    }

    DECLARE_INFO;
    static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype)
    {
        return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), info());
    }

private:
    JSInterfaceNamePrototype(JSC::VM& vm, JSC::JSGlobalObject*, JSC::Structure* structure)
        : JSC::JSNonFinalObject(vm, structure)
    {
    }

    void finishCreation(JSC::VM&);
};
STATIC_ASSERT_ISO_SUBSPACE_SHARABLE(JSInterfaceNamePrototype, JSInterfaceNamePrototype::Base);

using JSInterfaceNameConstructor = JSDOMConstructorNotConstructable<JSInterfaceName>;

template<> JSValue JSInterfaceNameConstructor::prototypeForStructure(JSC::VM& vm, const JSDOMGlobalObject& globalObject)
{
    UNUSED_PARAM(vm);
    return globalObject.functionPrototype();
}

template<> void JSInterfaceNameConstructor::initializeProperties(VM& vm, JSDOMGlobalObject& globalObject)
{
    putDirect(vm, vm.propertyNames->prototype, JSInterfaceName::prototype(vm, globalObject), JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    putDirect(vm, vm.propertyNames->name, jsNontrivialString(vm, String("InterfaceName"_s)), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    putDirect(vm, vm.propertyNames->length, jsNumber(0), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
}

template<> const ClassInfo JSInterfaceNameConstructor::s_info = { "InterfaceName", &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSInterfaceNameConstructor) };

/* Hash table for prototype */

static const HashTableValue JSInterfaceNamePrototypeTableValues[] =
{
    { "constructor", static_cast<unsigned>(JSC::PropertyAttribute::DontEnum), NoIntrinsic, { (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsInterfaceNameConstructor), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(setJSInterfaceNameConstructor) } },
};

const ClassInfo JSInterfaceNamePrototype::s_info = { "InterfaceNamePrototype", &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSInterfaceNamePrototype) };

void JSInterfaceNamePrototype::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    reifyStaticProperties(vm, JSInterfaceName::info(), JSInterfaceNamePrototypeTableValues, *this);
}

const ClassInfo JSInterfaceName::s_info = { "InterfaceName", &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSInterfaceName) };

JSInterfaceName::JSInterfaceName(Structure* structure, JSDOMGlobalObject& globalObject, Ref<InterfaceName>&& impl)
    : JSDOMWrapper<InterfaceName>(structure, globalObject, WTFMove(impl))
{
}

void JSInterfaceName::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    ASSERT(inherits(vm, info()));

    static_assert(!std::is_base_of<ActiveDOMObject, InterfaceName>::value, "Interface is not marked as [ActiveDOMObject] even though implementation class subclasses ActiveDOMObject.");

}

JSObject* JSInterfaceName::createPrototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    return JSInterfaceNamePrototype::create(vm, &globalObject, JSInterfaceNamePrototype::createStructure(vm, &globalObject, globalObject.objectPrototype()));
}

JSObject* JSInterfaceName::prototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    return getDOMPrototype<JSInterfaceName>(vm, globalObject);
}

JSValue JSInterfaceName::getConstructor(VM& vm, const JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSInterfaceNameConstructor>(vm, *jsCast<const JSDOMGlobalObject*>(globalObject));
}

void JSInterfaceName::destroy(JSC::JSCell* cell)
{
    JSInterfaceName* thisObject = static_cast<JSInterfaceName*>(cell);
    thisObject->JSInterfaceName::~JSInterfaceName();
}

EncodedJSValue jsInterfaceNameConstructor(JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName)
{
    VM& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto* prototype = jsDynamicCast<JSInterfaceNamePrototype*>(vm, JSValue::decode(thisValue));
    if (UNLIKELY(!prototype))
        return throwVMTypeError(lexicalGlobalObject, throwScope);
    return JSValue::encode(JSInterfaceName::getConstructor(JSC::getVM(lexicalGlobalObject), prototype->globalObject()));
}

bool setJSInterfaceNameConstructor(JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, EncodedJSValue encodedValue)
{
    VM& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto* prototype = jsDynamicCast<JSInterfaceNamePrototype*>(vm, JSValue::decode(thisValue));
    if (UNLIKELY(!prototype)) {
        throwVMTypeError(lexicalGlobalObject, throwScope);
        return false;
    }
    // Shadowing a built-in constructor
    return prototype->putDirect(vm, vm.propertyNames->constructor, JSValue::decode(encodedValue));
}

void JSInterfaceName::visitChildren(JSCell* cell, SlotVisitor& visitor)
{
    auto* thisObject = jsCast<JSInterfaceName*>(cell);
    ASSERT_GC_OBJECT_INHERITS(thisObject, info());
    Base::visitChildren(thisObject, visitor);
    visitor.reportExtraMemoryVisited(thisObject->wrapped().memoryCost());
}

size_t JSInterfaceName::estimatedSize(JSCell* cell, VM& vm)
{
    auto* thisObject = jsCast<JSInterfaceName*>(cell);
    return Base::estimatedSize(thisObject, vm) + thisObject->wrapped().memoryCost();
}

void JSInterfaceName::analyzeHeap(JSCell* cell, HeapAnalyzer& analyzer)
{
    auto* thisObject = jsCast<JSInterfaceName*>(cell);
    analyzer.setWrappedObjectForCell(cell, &thisObject->wrapped());
    if (thisObject->scriptExecutionContext())
        analyzer.setLabelForCell(cell, "url " + thisObject->scriptExecutionContext()->url().string());
    Base::analyzeHeap(cell, analyzer);
}

bool JSInterfaceNameOwner::isReachableFromOpaqueRoots(JSC::Handle<JSC::Unknown> handle, void*, SlotVisitor& visitor, const char** reason)
{
    UNUSED_PARAM(handle);
    UNUSED_PARAM(visitor);
    UNUSED_PARAM(reason);
    return false;
}

void JSInterfaceNameOwner::finalize(JSC::Handle<JSC::Unknown> handle, void* context)
{
    auto* jsInterfaceName = static_cast<JSInterfaceName*>(handle.slot()->asCell());
    auto& world = *static_cast<DOMWrapperWorld*>(context);
    uncacheWrapper(world, &jsInterfaceName->wrapped(), jsInterfaceName);
}

#if ENABLE(BINDING_INTEGRITY)
#if PLATFORM(WIN)
#pragma warning(disable: 4483)
extern "C" { extern void (*const __identifier("??_7InterfaceName@WebCore@@6B@")[])(); }
#else
extern "C" { extern void* _ZTVN7WebCore13InterfaceNameE[]; }
#endif
#endif

JSC::JSValue toJSNewlyCreated(JSC::JSGlobalObject*, JSDOMGlobalObject* globalObject, Ref<InterfaceName>&& impl)
{

#if ENABLE(BINDING_INTEGRITY)
    void* actualVTablePointer = getVTablePointer(impl.ptr());
#if PLATFORM(WIN)
    void* expectedVTablePointer = __identifier("??_7InterfaceName@WebCore@@6B@");
#else
    void* expectedVTablePointer = &_ZTVN7WebCore13InterfaceNameE[2];
#endif

    // If this fails InterfaceName does not have a vtable, so you need to add the
    // ImplementationLacksVTable attribute to the interface definition
    static_assert(std::is_polymorphic<InterfaceName>::value, "InterfaceName is not polymorphic");

    // If you hit this assertion you either have a use after free bug, or
    // InterfaceName has subclasses. If InterfaceName has subclasses that get passed
    // to toJS() we currently require InterfaceName you to opt out of binding hardening
    // by adding the SkipVTableValidation attribute to the interface IDL definition
    RELEASE_ASSERT(actualVTablePointer == expectedVTablePointer);
#endif
    globalObject->vm().heap.reportExtraMemoryAllocated(impl->memoryCost());
    return createWrapper<InterfaceName>(globalObject, WTFMove(impl));
}

JSC::JSValue toJS(JSC::JSGlobalObject* lexicalGlobalObject, JSDOMGlobalObject* globalObject, InterfaceName& impl)
{
    return wrap(lexicalGlobalObject, globalObject, impl);
}

InterfaceName* JSInterfaceName::toWrapped(JSC::VM& vm, JSC::JSValue value)
{
    if (auto* wrapper = jsDynamicCast<JSInterfaceName*>(vm, value))
        return &wrapper->wrapped();
    return nullptr;
}

}
