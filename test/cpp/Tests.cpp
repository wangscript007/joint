#include <Tests_adapters.hpp>


using namespace test;
using namespace joint;

class SomeObject
{
private:
	int	_counter;

public:
	typedef TypeList<ISomeObject>	JointInterfaces;

	SomeObject() : _counter(0) { }

	void Method() { ++_counter; }
	int32_t GetInvokationsCount() { return _counter; }
};


class LifetimeListenable
{
private:
	ILifetimeListener_Ptr	_listener;

public:
	typedef TypeList<ILifetimeListenable>	JointInterfaces;

	~LifetimeListenable()
	{
		if (_listener)
			_listener->OnDestroyed();
	}

	void SetListener(const ILifetimeListener_Ptr& l)
	{ _listener = l; }
};


class Tests
{
public:
	typedef TypeList<IBasicTests, IObjectTests, ILifetimeTests>	JointInterfaces;

private:
	Joint_ModuleHandle   _module;

public:
	Tests(Joint_ModuleHandle module)
		: _module(module)
	{ }

	~Tests()
	{ }

	void Throw() { }

	uint8_t   AddU8(uint8_t l, uint8_t r)     { return l + r; }
	int8_t    AddI8(int8_t l, int8_t r)       { return l + r; }
	uint16_t  AddU16(uint16_t l, uint16_t r)  { return l + r; }
	int16_t   AddI16(int16_t l, int16_t r)    { return l + r; }
	uint32_t  AddU32(uint32_t l, uint32_t r)  { return l + r; }
	int32_t   AddI32(int32_t l, int32_t r)    { return l + r; }
	uint64_t  AddU64(uint64_t l, uint64_t r)  { return l + r; }
	int64_t   AddI64(int64_t l, int64_t r)    { return l + r; }

	float     AddF32(float l, float r)        { return l + r; }
	double    AddF64(double l, double r)      { return l + r; }

	bool And(bool l, bool r) { return l && r; }

	std::string Concat(const std::string& l, const std::string& r)
	{ return l + r; }

	uint8_t CallbackU8(const IBasicTestsCallbackU8_Ptr& cb, uint8_t l, uint8_t r) { return cb->AddU8(l, r); }
	int8_t CallbackI8(const IBasicTestsCallbackI8_Ptr& cb, int8_t l, int8_t r) { return cb->AddI8(l, r); }
	uint16_t CallbackU16(const IBasicTestsCallbackU16_Ptr& cb, uint16_t l, uint16_t r) { return cb->AddU16(l, r); }
	int16_t CallbackI16(const IBasicTestsCallbackI16_Ptr& cb, int16_t l, int16_t r) { return cb->AddI16(l, r); }
	uint32_t CallbackU32(const IBasicTestsCallbackU32_Ptr& cb, uint32_t l, uint32_t r) { return cb->AddU32(l, r); }
	int32_t CallbackI32(const IBasicTestsCallbackI32_Ptr& cb, int32_t l, int32_t r) { return cb->AddI32(l, r); }
	uint64_t CallbackU64(const IBasicTestsCallbackU64_Ptr& cb, uint64_t l, uint64_t r) { return cb->AddU64(l, r); }
	int64_t CallbackI64(const IBasicTestsCallbackI64_Ptr& cb, int64_t l, int64_t r) { return cb->AddI64(l, r); }
	float CallbackF32(const IBasicTestsCallbackF32_Ptr& cb, float l, float r) { return cb->AddF32(l, r); }
	double CallbackF64(const IBasicTestsCallbackF64_Ptr& cb, double l, double r) { return cb->AddF64(l, r); }
	bool CallbackBool(const IBasicTestsCallbackBool_Ptr& cb, bool l, bool r) { return cb->And(l, r); }
	std::string CallbackString(const IBasicTestsCallbackString_Ptr& cb, const std::string& l, const std::string& r) { return cb->Concat(l, r); }


	ISomeObject_Ptr ReturnNull()
	{ return ISomeObject_Ptr(); }

	bool CheckNotNull(const ISomeObject_Ptr& o)
	{ return (bool)o; }

	bool ReverseNullChecks(const INullChecksCallback_Ptr& cb)
	{
		ISomeObject_Ptr o = cb->ReturnNotNull();
		return
			(bool)cb->ReturnNull() == false &&
			(bool)o == true &&
			cb->ValidateNotNull(ISomeObject_Ptr(), false) &&
			cb->ValidateNotNull(o, true);
	}

	void InvokeObjectMethod(const ISomeObject_Ptr& o)
	{ o->Method(); }

	ISomeObject_Ptr ReturnSameObject(const ISomeObject_Ptr& o)
	{ return o; }

	ISomeObject_Ptr ReturnNewObject()
	{ return MakeComponent<ISomeObject, SomeObject>(_module); }


	ILifetimeListenable_Ptr CreateListenable()
	{ return MakeComponent<ILifetimeListenable, LifetimeListenable>(_module); }

	void CollectGarbage()
	{ }
};

extern "C"
{

#ifdef _MSC_VER
	__declspec(dllexport)
#endif
	Joint_ObjectHandle GetTests(Joint_ModuleHandle module)
	{ return Export(MakeComponent<IObject, Tests>(module, module)); }

}
