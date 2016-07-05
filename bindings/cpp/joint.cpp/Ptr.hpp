#ifndef BINDINGS_CPP_JOINT_CPP_PTR_HPP
#define BINDINGS_CPP_JOINT_CPP_PTR_HPP


#include <joint.cpp/detail/JointCall.hpp>


namespace joint
{

	template < typename T_ >
	class Ptr
	{
	private:
		T_*		_raw;

	public:
		explicit Ptr(T_* raw = nullptr)
			: _raw(raw)
		{ }

		Ptr(Ptr&& other)
			: _raw(other._raw)
		{ other._raw = nullptr; }

		Ptr(const Ptr& other)
			: _raw(other._raw)
		{
			if (_raw)
				_raw->_AddRef();
		}

		~Ptr()
		{
			if (_raw)
				_raw->_Release();
		}


		void swap(Ptr& other)
		{ std::swap(_raw, other._raw); }


		Ptr& operator = (const Ptr& other)
		{
			Ptr tmp(other);
			swap(tmp);
			return *this;
		}

		explicit operator bool() const
		{ return _raw != nullptr; }

		T_* get() const
		{ return _raw; }

		T_* operator -> () const
		{ return _raw; }

		T_& operator * () const
		{ return &_raw; }
	};


	template < typename Dst_, typename Src_ >
	Ptr<Dst_> Cast(Ptr<Src_> src)
	{
		if (!src)
			return Ptr<Dst_>();

		detail::ProxyBase *proxy_base = src.get();
		Joint_ObjectHandle result_handle;
		JOINT_CALL(Joint_CastObject(proxy_base->_GetObjectHandle(), Dst_::_GetInterfaceId(), &result_handle));
		return Ptr<Dst_>(new Dst_(result_handle));
	}

}

#endif