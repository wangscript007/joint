#include <pyjoint/Object.hpp>

#include <joint/devkit/Logger.hpp>

#include <vector>

#include <utils/PythonUtils.hpp>


namespace joint_python {
namespace pyjoint
{

	JOINT_DEVKIT_LOGGER("Joint.Python.PyJoint.Object")

	static PyObject* Object_new(PyTypeObject* type, PyObject* args, PyObject* kwds);
	static void Object_del(PyObject* self);
	static PyObject* Object_InvokeMethod(PyObject* self, PyObject* args, PyObject* kwds);

	static PyMethodDef Object_methods[] = {
		{"InvokeMethod", (PyCFunction)Object_InvokeMethod, METH_VARARGS, "InvokeMethod" },
		{NULL}  /* Sentinel */
	};

	PyTypeObject Object_type = {
		PyVarObject_HEAD_INIT(NULL, 0)
		"pyjoint.Object",          // tp_name
		sizeof(Object),            // tp_basicsize
		0,                         // tp_itemsize
		(destructor)Object_del,    // tp_dealloc
		0,                         // tp_print
		0,                         // tp_getattr
		0,                         // tp_setattr
		0,                         // tp_reserved
		0,                         // tp_repr
		0,                         // tp_as_number
		0,                         // tp_as_sequence
		0,                         // tp_as_mapping
		0,                         // tp_hash
		0,                         // tp_call
		0,                         // tp_str
		0,                         // tp_getattro
		0,                         // tp_setattro
		0,                         // tp_as_buffer
		Py_TPFLAGS_DEFAULT,        // tp_flags
		"joint module object",     // tp_doc
		0,                         // tp_traverse
		0,                         // tp_clear
		0,                         // tp_richcompare
		0,                         // tp_weaklistoffset
		0,                         // tp_iter
		0,                         // tp_iternext
		Object_methods,            // tp_methods
		NULL,                      // tp_members
		0,                         // tp_getset
		0,                         // tp_base
		0,                         // tp_dict
		0,                         // tp_descr_get
		0,                         // tp_descr_set
		0,                         // tp_dictoffset
		0,                         // tp_init
		0,                         // tp_alloc
		Object_new                 // tp_new
	};


	static PyObject* Object_new(PyTypeObject* type, PyObject* args, PyObject* kwds)
	{
		PYJOINT_CPP_WRAP_BEGIN

		Object* self = PY_OBJ_CHECK((Object*)type->tp_alloc(type, 0));

		self->handle = JOINT_NULL_HANDLE;

		PYJOINT_CPP_WRAP_END((PyObject*)self, NULL)
	}


	static void Object_del(PyObject* self)
	{
		PYJOINT_CPP_WRAP_BEGIN

		auto m = reinterpret_cast<Object*>(self);
		if (m && m->handle)
		{
			Joint_Error ret = Joint_DecRefObject(m->handle);
			if (ret != JOINT_ERROR_NONE)
				GetLogger().Error() << "Joint_DecRefObject failed: " << ret;
			m->handle = JOINT_NULL_HANDLE;
		}

		PYJOINT_CPP_WRAP_END_VOID()
	}


	static PyObject* Object_InvokeMethod(PyObject* self, PyObject* args, PyObject* kwds)
	{
		PYJOINT_CPP_WRAP_BEGIN

		auto o = reinterpret_cast<Object*>(self);
		NATIVE_CHECK(o && o->handle, "Uninitialized object");

		auto tuple_size = PyTuple_Size(args);
		NATIVE_CHECK(tuple_size >= 2, "Could not parse arguments");

		auto method_id = FromPyLong<int>(PyTuple_GetItem(args, 0));
		Joint_Type ret_type = FromPyLong<Joint_Type>(PyTuple_GetItem(args, 1));

		// TODO: use stack allocations for smaller tuples
		std::vector<Joint_Variant> params;
		params.reserve(tuple_size - 2);

		std::vector<PyBytesHolder> str_params;

		for (int i = 2; i < tuple_size; ++i)
		{
			PyObject* py_param_tuple = PY_OBJ_CHECK(PyTuple_GetItem(args, i));

			Joint_Variant v = { };
			v.type = FromPyLong<Joint_Type>(PyTuple_GetItem(py_param_tuple, 0));

			PyObject* py_param = PyTuple_GetItem(py_param_tuple, 1);
			switch (v.type)
			{
			case JOINT_TYPE_BOOL: v.value.b = PyObject_IsTrue(py_param); break;
			case JOINT_TYPE_I8: v.value.i8 = FromPyLong<int8_t>(py_param); break;
			case JOINT_TYPE_U8: v.value.u8 = FromPyLong<uint8_t>(py_param); break;
			case JOINT_TYPE_I16: v.value.i16 = FromPyLong<int16_t>(py_param); break;
			case JOINT_TYPE_U16: v.value.u16 = FromPyLong<uint16_t>(py_param); break;
			case JOINT_TYPE_I32: v.value.i32 = FromPyLong<int32_t>(py_param); break;
			case JOINT_TYPE_U32: v.value.u32 = FromPyLong<uint32_t>(py_param); break;
			case JOINT_TYPE_I64: v.value.i64 = FromPyLong<int64_t>(py_param); break;
			case JOINT_TYPE_U64: v.value.u64 = FromPyLong<uint64_t>(py_param); break;
			case JOINT_TYPE_F32: v.value.f32 = FromPyFloat<float>(py_param); break;
			case JOINT_TYPE_F64: v.value.f64 = FromPyFloat<double>(py_param); break;
			case JOINT_TYPE_UTF8:
				str_params.push_back(Utf8FromPyUnicode(py_param));
				v.value.utf8 = str_params.back().GetContent();
				break;
			case JOINT_TYPE_OBJ:
				v.value.obj = (py_param != Py_None) ? CastPyObject<Object>(py_param, &Object_type)->handle : JOINT_NULL_HANDLE;
				break;
			default:
				NATIVE_THROW("Unknown parameter type: " + std::to_string(v.type));
			}

			params.push_back(v);
		}

		Joint_RetValue ret_value;
		Joint_Error ret = Joint_InvokeMethod(o->handle, method_id, params.data(), params.size(), ret_type, &ret_value);
		NATIVE_CHECK(ret == JOINT_ERROR_NONE, (std::string("Joint_InvokeMethod failed: ") + Joint_ErrorToString(ret)).c_str());

		auto sg(ScopeExit([&]{
			Joint_Error ret = Joint_ReleaseRetValue(ret_value);
			if (ret != JOINT_ERROR_NONE)
				GetLogger().Error() << "Joint_ReleaseRetValue failed: " << ret;
		}));

		PyObjectHolder result;
		switch (ret_value.variant.type)
		{
		case JOINT_TYPE_VOID: Py_RETURN_NONE; break;
		case JOINT_TYPE_BOOL: result.Reset(PyBool_FromLong(ret_value.variant.value.b)); break;
		case JOINT_TYPE_I8: result.Reset(PyLong_FromLong(ret_value.variant.value.i8)); break;
		case JOINT_TYPE_U8: result.Reset(PyLong_FromLong(ret_value.variant.value.u8)); break;
		case JOINT_TYPE_I16: result.Reset(PyLong_FromLong(ret_value.variant.value.i16)); break;
		case JOINT_TYPE_U16: result.Reset(PyLong_FromLong(ret_value.variant.value.u16)); break;
		case JOINT_TYPE_I32: result.Reset(PyLong_FromLong(ret_value.variant.value.i32)); break;
		case JOINT_TYPE_U32: result.Reset(PyLong_FromLong(ret_value.variant.value.u32)); break;
		case JOINT_TYPE_I64: result.Reset(PyLong_FromLong(ret_value.variant.value.i64)); break;
		case JOINT_TYPE_U64: result.Reset(PyLong_FromLong(ret_value.variant.value.u64)); break;
		case JOINT_TYPE_F32: result.Reset(PyFloat_FromDouble(ret_value.variant.value.f32)); break;
		case JOINT_TYPE_F64: result.Reset(PyFloat_FromDouble(ret_value.variant.value.f64)); break;
		case JOINT_TYPE_UTF8: result.Reset(PyUnicode_FromString(ret_value.variant.value.utf8)); break;
		case JOINT_TYPE_OBJ:
			if (ret_value.variant.value.obj != JOINT_NULL_HANDLE)
			{
				result.Reset(PY_OBJ_CHECK(PyObject_CallObject((PyObject*)&Object_type, NULL)));
				reinterpret_cast<Object*>(result.Get())->handle = ret_value.variant.value.obj;
			}
			else
			{
				Py_INCREF(Py_None);
				result.Reset(Py_None);
			}
			break;
		case JOINT_TYPE_EXCEPTION:
			{
				Joint_SizeT buf_size = 0;
				std::vector<char> buf;

				Joint_Error ret = Joint_GetExceptionMessageSize(ret_value.variant.value.ex, &buf_size);
				if (ret != JOINT_ERROR_NONE)
				{
					Joint_Log(JOINT_LOGLEVEL_ERROR, "Joint.C++", "Joint_GetExceptionMessageSize failed: ", Joint_ErrorToString(ret));
					throw std::runtime_error("Could not obtain joint exception message!");
				}

				buf.resize(buf_size);

				ret = Joint_GetExceptionMessage(ret_value.variant.value.ex, buf.data(), buf.size());
				if (ret != JOINT_ERROR_NONE)
				{
					Joint_Log(JOINT_LOGLEVEL_ERROR, "Joint.C++", "Joint_GetExceptionMessage failed: %s", Joint_ErrorToString(ret));
					throw std::runtime_error("Could not obtain joint exception message!");
				}
				throw std::runtime_error(buf.data());
			}
			break;
		default:
			NATIVE_THROW("Unknown return type: " + std::to_string(ret_value.variant.type));
		}

		PYJOINT_CPP_WRAP_END(result.Release(), NULL)
	}

}}
