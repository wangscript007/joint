#if defined SWIGPYTHON
%module(directors="1") swig_benchmarks_wrappers_py
#elif defined SWIGJAVA
%module(directors="1") swig_benchmarks_wrappers_java
#endif

%include <stdint.i>
%include <exception.i>
%include <std_string.i>

#ifdef SWIGPYTHON
%exception {
    try { $action }
    catch (const std::exception& e) { SWIG_exception(SWIG_RuntimeError, e.what()); }
}

%feature("director:except") {
    if ($error != NULL) {
        struct PyObjectHolder
        {
            PyObject* Obj;

            PyObjectHolder(PyObject* obj) : Obj(obj) { }
            ~PyObjectHolder() { Py_DECREF(Obj); }
        };

        std::string msg(Swig::DirectorMethodException().getMessage());
        PyObject *type = NULL, *value = NULL, *traceback = NULL;
        PyErr_Fetch(&type, &value, &traceback);
        if (value)
        {
            PyObjectHolder value_str(PyObject_Str(value));
            const char* err_str = PyString_AsString(value_str.Obj);
            if (err_str)
                msg += std::string(" (") + err_str + ")";
        }
        PyErr_Restore(type, value, traceback);
        throw std::runtime_error(msg);
    }
}
#endif

%pragma(java) jniclasscode=%{
    static {
        try {
            System.loadLibrary("swig_benchmarks_wrappers_java");
        } catch (UnsatisfiedLinkError e) {
            System.err.println("Native code library failed to load. \n" + e);
            System.exit(1);
        }
    }
%}

%feature("director") IBasicBenchmarks;
%{
    #include <ISwigBenchmarks.hpp>
%}
%include "ISwigBenchmarks.hpp"
