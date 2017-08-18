#ifndef BINDING_MODULE_HPP
#define BINDING_MODULE_HPP


#include <joint/Joint.h>
#include <joint/devkit/Logger.hpp>
#include <joint/devkit/accessors/Module.hpp>

#include <memory>

#include <utils/DynamicLibrary.hpp>


namespace joint {
namespace cpp {
namespace binding
{

	class Module : public joint::devkit::accessors::Module<Module>
	{
		JOINT_DEVKIT_LOGGER("Joint.C++.Module")

	private:
		std::unique_ptr<DynamicLibrary> _dl;

	public:
		Module(JointCore_ManifestHandle moduleManifest);
		~Module();

		JointCore_Error GetRootObject(const char* getterName, JointCore_ObjectAccessor* outObject) JOINT_DEVKIT_NOEXCEPT;
	};

}}}

#endif