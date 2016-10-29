#ifndef BINDING_JAVABINDINGINFO_HPP
#define BINDING_JAVABINDINGINFO_HPP


#include <joint/Joint.h>
#include <joint/devkit/InterfaceDescriptor.hpp>
#include <joint/devkit/Logger.hpp>

#include <vector>

#include <utils/JPtr.hpp>
#include <utils/Utils.hpp>


namespace joint {
namespace java
{

	class JavaBindingInfo
	{
		JOINT_DEVKIT_LOGGER("Joint.Java.JavaBindingInfo")

	public:
		struct MemberId
		{
			jfieldID           Id;
		};

		struct ArrayUserData
		{
		};

		struct ObjectUserData
		{
			JGlobalClassPtr    Cls;
			jmethodID          CtorId;
		};

		struct EnumUserData
		{
			JGlobalClassPtr    Cls;
			jmethodID          FromIntId;
		};

		struct StructUserData
		{
			JGlobalClassPtr    Cls;
			jmethodID          CtorId;
		};

		struct MethodUserData
		{
			jmethodID          Id;
		};

	public:
		Joint_TypeId GetJointTypeId(const JLocalObjPtr& typeNode) const;
		Joint_InterfaceChecksum GetInterfaceChecksum(const JLocalObjPtr& typeNode) const;

		ArrayUserData GetArrayUserData(const JLocalObjPtr& typeNode) const;
		ObjectUserData GetObjectUserData(const JLocalObjPtr& typeNode) const;
		EnumUserData GetEnumUserData(const JLocalObjPtr& typeNode) const;
		StructUserData GetStructUserData(const JLocalObjPtr& typeNode) const;

		MethodUserData GetMethodUserData(const JLocalObjPtr& methodNode) const;

		JLocalObjPtr GetRetTypeNode(const JLocalObjPtr& methodNode) const;
		JLocalObjPtr GetArrayElementTypeNode(const JLocalObjPtr& typeNode) const;


		class Sequence
		{
		private:
			JLocalObjArrayPtr    _array;

		public:
			Sequence(const JLocalObjArrayPtr& array) : _array(array) { }

			size_t GetCount() const
			{
				auto env = _array.GetEnv();
				return JAVA_CALL(_array.GetEnv()->GetArrayLength(_array.Get()));
			}

			JLocalObjPtr Get(size_t index) const
			{
				auto env = _array.GetEnv();
				return JLocalObjPtr(env, JAVA_CALL(env->GetObjectArrayElement(_array.Get(), index)));
			}
		};

		Sequence GetParamsNodes(const JLocalObjPtr& methodNode) const;
		Sequence GetMethodsNodes(const JLocalObjPtr& ifcNode) const;
		Sequence GetMembersNodes(const JLocalObjPtr& typeNode) const;
		MemberId GetMemberId(const StructUserData& structUserData, const JLocalObjPtr& memberNode) const;
		JLocalObjPtr GetMemberType(const StructUserData& structUserData, const JLocalObjPtr& memberNode) const;
	};


	using JavaInterfaceDescriptor = devkit::InterfaceDescriptor<JavaBindingInfo>;

}}

#endif
