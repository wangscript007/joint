#include <utils/DynamicLibrary.hpp>

#include <joint/devkit/Holder.hpp>
#include <joint/devkit/JointException.hpp>
#include <joint/devkit/StringBuilder.hpp>


#ifdef _WIN32
#	include <windows.h>
#else
#	include <dlfcn.h>
#endif

namespace joint {
namespace cpp
{

#ifdef _WIN32

	class DynamicLibrary::Impl
	{
	private:
		HMODULE    _handle;

	public:
		Impl(const std::string& name)
		{
			// TODO: add unicode support
			_handle = LoadLibraryA((name + ".dll").c_str());
			JOINT_CHECK(_handle != nullptr, joint::devkit::StringBuilder() % "dlopen failed: " % GetWinErrorMessage(GetLastError()));
		}

		~Impl()
		{
			if (!FreeLibrary(_handle))
				GetLogger().Warning() << "FreeLibrary failed: " << GetWinErrorMessage(GetLastError());
		}

		FuncPtr GetFunction(const std::string& name)
		{ return reinterpret_cast<FuncPtr>(GetProcAddress(_handle, name.c_str())); }

	private:
		static std::string GetWinErrorMessage(DWORD err)
		{
			char* buf = NULL;
			// TODO: add unicode support
			if (!FormatMessageA(
					FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
					NULL,
					err,
					0,
					(LPSTR)&buf,
					0,
					NULL))
			{ return "Windows error " + std::to_string(err); }

			joint::devkit::Holder<char*> h(buf, [](char* b){ LocalFree(b); });
			return buf;
		}
	};

#else

	class DynamicLibrary::Impl
	{
	private:
		void*    _handle;

	public:
		Impl(const std::string& name)
		{
			_handle = dlopen(("lib" + name + ".so").c_str(), RTLD_NOW | RTLD_DEEPBIND);
			JOINT_CHECK(_handle != nullptr, joint::devkit::StringBuilder() % "dlopen failed: " % dlerror());
		}

		~Impl()
		{
			if (dlclose(_handle) != 0)
				GetLogger().Warning() << "dlclose failed: " << dlerror();
		}

		FuncPtr GetFunction(const std::string& name)
		{ return reinterpret_cast<FuncPtr>(dlsym(_handle, name.c_str())); }
	};

#endif


	DynamicLibrary::DynamicLibrary(const std::string& name)
		: _impl(new Impl(name))
	{ }


	DynamicLibrary::~DynamicLibrary()
	{ }


	DynamicLibrary::FuncPtr DynamicLibrary::GetFunctionImpl(const std::string& name)
	{ return _impl->GetFunction(name); }

}}
