#include <binding/Binding.hpp>

#include <joint/Joint.h>
#include <joint/devkit/Holder.hpp>
#include <joint/utils/CppWrappers.hpp>

#include <memory>
#include <string.h>

#include <stdio.h>

#include <joint.cpp/IJointObject.hpp>
#include <joint.cpp/Ptr.hpp>
#include <utils/DynamicLibrary.hpp>


namespace joint_cpp {
namespace binding
{

	Binding::Binding()
	{ GetLogger().Debug() << "Created"; }


	Binding::~Binding()
	{ GetLogger().Debug() << "Destroying"; }


	Joint_Error Binding::Deinit(void* bindingUserData)
	{
		JOINT_CPP_WRAP_BEGIN
		delete reinterpret_cast<Binding*>(bindingUserData);
		JOINT_CPP_WRAP_END
	}


	Joint_Error Binding::LoadModule(void* bindingUserData, const char* moduleName, Joint_ModuleHandleInternal* outModule)
	{
		JOINT_CPP_WRAP_BEGIN
		*outModule = new DynamicLibrary(moduleName);
		JOINT_CPP_WRAP_END
	}


	Joint_Error Binding::UnloadModule(void* bindingUserData, Joint_ModuleHandleInternal module)
	{
		JOINT_CPP_WRAP_BEGIN
		delete reinterpret_cast<DynamicLibrary*>(module);
		JOINT_CPP_WRAP_END
	}

	namespace {
		class IObject : public virtual ::joint::detail::ProxyBase
		{ };
	}

	Joint_Error Binding::GetRootObject(Joint_ModuleHandle module, void* bindingUserData, Joint_ModuleHandleInternal moduleInt, const char* getterName, Joint_ObjectHandle* outObject)
	{
		JOINT_CPP_WRAP_BEGIN

		auto dl = reinterpret_cast<DynamicLibrary*>(moduleInt);
		auto getter = dl->GetFunction<IObject*(Joint_ModuleHandle)>(getterName);
		JOINT_CHECK(getter, JOINT_ERROR_NO_SUCH_MODULE);
		IObject* obj = getter(module);
		printf("??? %p\n", obj);
		printf("+++ %p\n", obj->_GetObjectHandle());
		obj->_AddRef();
		*outObject = obj->_GetObjectHandle();

		JOINT_CPP_WRAP_END
	}


	Joint_Error Binding::InvokeMethod(Joint_ModuleHandle module, void* bindingUserData, Joint_ModuleHandleInternal moduleInt, Joint_ObjectHandleInternal obj, Joint_SizeT methodId, const Joint_Variant* params, Joint_SizeT paramsCount, Joint_Type retType, Joint_RetValue* outRetValue)
	{
		JOINT_CPP_WRAP_BEGIN

		auto o = reinterpret_cast<joint::IJointObject*>(obj);
		return o->_InvokeMethod(methodId, params, paramsCount, retType, outRetValue);

		JOINT_CPP_WRAP_END
	}


	Joint_Error Binding::ReleaseObject(void* bindingUserData, Joint_ModuleHandleInternal module, Joint_ObjectHandleInternal obj)
	{
		JOINT_CPP_WRAP_BEGIN

		auto o = reinterpret_cast<joint::IJointObject*>(obj);
		o->_Release();

		JOINT_CPP_WRAP_END
	}


	Joint_Error Binding::CastObject(void* bindingUserData, Joint_ModuleHandleInternal module, Joint_ObjectHandleInternal obj, Joint_InterfaceId interfaceId, Joint_ObjectHandleInternal* outRetValue)
	{
		JOINT_CPP_WRAP_BEGIN

		auto o = reinterpret_cast<joint::IJointObject*>(obj);
		joint::IJointObject* result = nullptr;
		Joint_Error ret = o->_CastObject(interfaceId, &result);
		*outRetValue = result;
		return ret;

		JOINT_CPP_WRAP_END
	}


	Joint_Error Binding::ReleaseRetValue(Joint_Variant value)
	{
		JOINT_CPP_WRAP_BEGIN
		switch(value.type)
		{
		case JOINT_TYPE_VOID:
		case JOINT_TYPE_BOOL:
		case JOINT_TYPE_I8:
		case JOINT_TYPE_U8:
		case JOINT_TYPE_I16:
		case JOINT_TYPE_U16:
		case JOINT_TYPE_I32:
		case JOINT_TYPE_U32:
		case JOINT_TYPE_I64:
		case JOINT_TYPE_U64:
		case JOINT_TYPE_F32:
		case JOINT_TYPE_F64:
			break;
		case JOINT_TYPE_UTF8:
			delete[] value.value.utf8;
			break;
		case JOINT_TYPE_OBJ:
			break;
		case JOINT_TYPE_EXCEPTION:
			{
				Joint_Error ret = Joint_ReleaseException(value.value.ex);
				if (ret != JOINT_ERROR_NONE)
					GetLogger().Error() << "Joint_ReleaseException failed: " << ret;
			}
			break;
		default:
			JOINT_THROW(JOINT_ERROR_GENERIC);
			break;
		}
		JOINT_CPP_WRAP_END
	}

}}
