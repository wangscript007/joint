#ifndef BINDINGS_PYTHON_PYJOINT_COMMON_H
#define BINDINGS_PYTHON_PYJOINT_COMMON_H


#include <stdexcept>
#include <type_traits>

#include <Python.h>


static PyObject* g_error = nullptr;


#define PYJOINT_THROW(Message_) do { throw std::runtime_error(Message_); } while (false)
#define PYJOINT_CHECK(Expr_, Message_) do { if (!(Expr_)) PYJOINT_THROW(Message_); } while (false)


#define PYJOINT_CPP_WRAP_BEGIN \
			try { \

#define PYJOINT_CPP_WRAP_END(RetSuccess_, RetError_, ...) \
				return RetSuccess_; \
			} \
			catch (const std::exception& ex) { \
				Joint_Log(JOINT_LOGLEVEL_ERROR, "Joint.Python", "%s failed: %s", __func__, ex.what()); \
				__VA_ARGS__ \
				return RetError_; \
			}

#define PYJOINT_CPP_WRAP_END_VOID(...) \
			} \
			catch (const std::exception& ex) { \
				Joint_Log(JOINT_LOGLEVEL_ERROR, "Joint.Python", "%s failed: %s", __func__, ex.what()); \
				__VA_ARGS__ \
			}

template < typename T_ >
T_ TerminateOnInvoke()
{
	Joint_Log(JOINT_LOGLEVEL_ERROR, "Joint.Python", "TerminateOnInvoke invoked");
	std::terminate();
}

template < typename T_ >
T_ FromPyLong(PyObject* pyLong)
{
	int overflow = 0;
	long long_result = PyLong_AsLongAndOverflow(pyLong, &overflow);
	PYJOINT_CHECK(!overflow, "long value overflow");
	T_ result = static_cast<T_>(long_result);
	PYJOINT_CHECK(static_cast<long>(result) == long_result, "T_ value overflow");
	return result;
}


#endif
