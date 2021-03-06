#ifndef BINDINGS_PYTHON_PYJOINT_JOINTEXCEPTION_H
#define BINDINGS_PYTHON_PYJOINT_JOINTEXCEPTION_H


#include <joint/devkit/marshalling/StackFrameData.hpp>

#include <string>
#include <vector>

#include <pyjoint/Common.hpp>


namespace joint {
namespace python {
namespace pyjoint
{

    struct JointException
    {
#if PY_VERSION_HEX >= 0x03000000
        PyException_HEAD
#else
        PyObject_HEAD
        PyObject* dict;
        PyObject* args;
        PyObject* message;
#endif

        JointCore_Exception_Handle ex;
    };


    extern PyTypeObject JointException_type;

}}}


#endif
