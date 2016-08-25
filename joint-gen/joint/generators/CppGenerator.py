from ..SemanticGraph import BuiltinType, BuiltinTypeCategory, Interface, Enum

class CppGenerator:
    def __init__(self, semanticGraph):
        self.semanticGraph = semanticGraph

    def generate(self):
        yield '#pragma once'
        yield ''

        yield '#include <joint.cpp/detail/GeneratedCodePrologue.hpp>'
        yield ''

        for p in self.semanticGraph.packages:
            for l in self._generatePackageContent(p, p.enums, self._generateEnum):
                yield l

        for p in self.semanticGraph.packages:
            for l in self._generatePackageContent(p, p.interfaces, self._generatePredeclarations):
                yield l

        for p in self.semanticGraph.packages:
            for l in self._generatePackageContent(p, p.interfaces, self._generateClasses):
                yield l

        for p in self.semanticGraph.packages:
            for l in self._generatePackageContent(p, p.enums, self._generateEnumMethods):
                yield l

        for p in self.semanticGraph.packages:
            for l in self._generatePackageContent(p, p.interfaces, self._generateMethods):
                yield l

        yield ''
        yield '#include <joint.cpp/detail/GeneratedCodeEpilogue.hpp>'
        yield ''

    def _generatePackageContent(self, p, types, generator):
        namespaces_count = 0
        for n in p.nameList:
            namespaces_count += 1
            yield 'namespace {} {{'.format(n)
            for t in types:
                for l in generator(t):
                    yield '\t{}'.format(l)
        yield '}' * namespaces_count
        yield ''

    def _generateEnum(self, e):
        yield 'class {}'.format(e.name)
        yield '{'
        yield 'public:'
        yield '\tenum _Value'
        yield '\t{'
        for i,v in enumerate(e.values):
            yield '\t\t{} = {}{}'.format(v.name, v.value, ', ' if i < len(e.values) - 1 else '')
        yield '\t};'
        yield ''
        yield '\tDETAIL_JOINT_CPP_ENUM_CLASS_INTERNALS({}, {})'.format(e.name, '_Value::{}'.format(e.values[0].name) if e.values else '_Value()')
        yield '};'
        yield ''

    def _generateEnumMethods(self, e):
        yield 'std::string {}::ToString() const'.format(e.name)
        yield '{'
        yield '\tswitch (_value)'
        yield '\t{'
        for v in e.values:
            yield '\tcase {v}: return "{v}";'.format(v=v.name)
        yield '\tdefault: return "<Unknown {} value>";'.format(e.name)
        yield '\t}'
        yield '}'
        yield ''

    def _generatePredeclarations(self, ifc):
        yield 'class {};'.format(ifc.name)
        yield 'typedef ::joint::Ptr<{name}> {name}_Ptr;'.format(name=ifc.name)
        yield 'template <typename ComponentImpl_> class {}_accessor;'.format(ifc.name)
        yield ''

    def _generateClasses(self, ifc):
        yield 'class {}'.format(ifc.name)
        yield '{'
        yield 'private:'
        yield '\tJoint_ObjectHandle _obj;'
        yield ''
        yield 'public:'
        yield '\ttypedef ::joint::TypeList<{}> BaseInterfaces;'.format(', '.join(self._mangleType(b) for b in ifc.bases))
        yield '\ttemplate <typename ComponentImpl_> using Accessor = {}_accessor<ComponentImpl_>;'.format(ifc.name)
        yield ''
        yield '\t{}() : _obj(JOINT_NULL_HANDLE) {{ }}'.format(ifc.name);
        yield '\t{}(Joint_ObjectHandle obj) : _obj(obj) {{ }}'.format(ifc.name);
        yield ''
        yield '\tJoint_ObjectHandle _GetObjectHandle() const { return _obj; }'
        yield '\tstatic Joint_InterfaceChecksum _GetInterfaceChecksum() {{ return {}UL; }}'.format(hex(ifc.checksum))
        yield '\tstatic const char* _GetInterfaceId() {{ return "{}"; }}'.format(ifc.fullname)
        yield ''
        for m in ifc.methods:
            for l in self._generateMethodDeclaration(m):
                yield '\t{}'.format(l)
        yield '};'
        yield ''
        yield 'template <typename ComponentImpl_>'
        yield 'class {}_accessor'.format(ifc.name)
        yield '{'
        yield 'public:'
        yield '\tstatic Joint_Error InheritsInterface(Joint_InterfaceId interfaceId, Joint_InterfaceChecksum checksum)'
        yield '\t{'
        b = ifc
        while b:
            yield '\t\tif (strcmp(interfaceId, "{}") == 0)'.format(b.fullname)
            yield '\t\t\treturn (checksum == {}::_GetInterfaceChecksum()) ? JOINT_ERROR_NONE : JOINT_ERROR_INVALID_INTERFACE_CHECKSUM;'.format(self._mangleType(b))
            if not b.bases:
                break
            b = b.bases[0]
        yield '\t\treturn JOINT_ERROR_CAST_FAILED;'
        yield '\t}'
        yield ''
        yield '\tstatic Joint_Error InvokeMethodImpl(ComponentImpl_* componentImpl, Joint_SizeT methodId, const Joint_Parameter* params, Joint_SizeT paramsCount, Joint_Type retType, Joint_RetValue* outRetValue);'
        yield '};'
        yield ''
        yield ''

    def _generateMethods(self, ifc):
        for m in ifc.methods:
            for l in self._generateMethodDefinition(ifc, m):
                yield '{}'.format(l)

        for l in self._generateAccessorInvokeMethod(ifc):
            yield '{}'.format(l)

    def _generateMethodDeclaration(self, m):
        yield '{} {}({});'.format(self._toCppType(m.retType), m.name, ', '.join('{} {}'.format(self._toCppType(p.type), p.name) for p in m.params))

    def _generateMethodDefinition(self, ifc, m):
        yield '{} {}::{}({})'.format(self._toCppType(m.retType), ifc.name, m.name, ', '.join('{} {}'.format(self._toCppType(p.type), p.name) for p in m.params))
        yield '{'
        yield '\tJoint_RetValue _ret_val;'
        yield '\tJoint_Type _ret_val_type;'
        yield '\t_ret_val_type.id = (Joint_TypeId){};'.format(m.retType.index)
        if isinstance(m.retType, Interface):
            yield '\t_ret_val_type.payload.interfaceChecksum = {}::_GetInterfaceChecksum();'.format(self._mangleType(m.retType))
        if m.params:
            yield '\tJoint_Parameter params[{}];'.format(len(m.params))
            for p in m.params:
                yield '\tparams[{}].value.{} = {};'.format(p.index, p.type.variantName, self._toCppParamGetter(p))
                yield '\tparams[{}].type.id = (Joint_TypeId){};'.format(p.index, p.type.index)
                if isinstance(p.type, Interface):
                    yield '\tparams[{}].type.payload.interfaceChecksum = {}::_GetInterfaceChecksum();'.format(p.index, self._mangleType(p.type))
        yield '\tJOINT_METHOD_CALL("{}.{}", Joint_InvokeMethod(_obj, {}, {}, {}, _ret_val_type, &_ret_val));'.format(ifc.fullname, m.name, m.index, 'params' if m.params else 'nullptr', len(m.params), m.retType.index)
        if m.retType.needRelease:
            yield '\t::joint::detail::RetValueGuard _rvg(_ret_val_type, _ret_val);'.format(m.retType.index)
        if m.retType.name != 'void':
            yield self._wrapRetValue(m.retType)
        yield '}'
        yield ''

    def _toCppParamInitializer(self, p):
        if isinstance(p.type, BuiltinType) or isinstance(p.type, Interface):
            return 'params[{i}].value.{v}'.format(i=p.index, v=p.type.variantName)
        elif isinstance(p.type, Enum):
            return '{e}(params[{i}].value.{v})'.format(e='{}::_Value'.format(self._mangleType(p.type)), i=p.index, v=p.type.variantName)
        else:
            raise RuntimeError('Not implemented (type: {})!'.format(p.type))

    def _generateAccessorInvokeMethodCase(self, ifc, m):
        yield 'case {}:'.format(m.index)
        yield '\t{'
        if isinstance(m.retType, Interface):
            yield '\t\tif (retType.payload.interfaceChecksum != {}::_GetInterfaceChecksum())'.format(self._mangleType(m.retType))
            yield '\t\t\treturn JOINT_ERROR_INVALID_INTERFACE_CHECKSUM;'
        for p in m.params:
            if isinstance(p.type, Interface):
                yield '\t\tJOINT_CALL(Joint_IncRefObject(params[{i}].value.{v}));'.format(i=p.index, v=p.type.variantName)
                yield '\t\t{t} p{i}({w}(params[{i}].value.{v}));'.format(t=self._toCppType(p.type), w=self._mangleType(p.type), i=p.index, v=p.type.variantName)
            else:
                yield '\t\t{t} p{i}({v});'.format(t=self._toCppType(p.type), i=p.index, v=self._toCppParamInitializer(p))
        method_call = 'componentImpl->{}({})'.format(m.name, ', '.join('p{}'.format(p.index) for p in m.params))
        if m.retType.name != 'void':
            yield '\t\t{} result({});'.format(self._toCppType(m.retType), method_call)
            if isinstance(m.retType, Interface):
                yield '\t\tJoint_Error ret = Joint_IncRefObject(result->_GetObjectHandle());'
                yield '\t\tif (ret != JOINT_ERROR_NONE)'
                yield '\t\t\treturn ret;'
            if m.retType.name != 'string':
                yield '\t\toutRetValue->result.value.{} = {};'.format(m.retType.variantName, self._toCppValue('result', m.retType))
            else:
                yield '\t\tchar* result_c_str = new char[result.size() + 1];'
                yield '\t\tstrcpy(result_c_str, result.c_str());'
                yield '\t\toutRetValue->result.value.{} = result_c_str;'.format(m.retType.variantName)
        else:
            yield '\t\t{};'.format(method_call)
        yield '\t}'
        yield '\tbreak;'

    def _generateAccessorInvokeMethod(self, ifc):
        yield 'template <typename ComponentImpl_>'
        yield 'Joint_Error {}_accessor<ComponentImpl_>::InvokeMethodImpl(ComponentImpl_* componentImpl, Joint_SizeT methodId, const Joint_Parameter* params, Joint_SizeT paramsCount, Joint_Type retType, Joint_RetValue* outRetValue)'.format(ifc.name)
        yield '{'
        yield '\ttry'
        yield '\t{'
        yield '\t\tswitch(methodId)'
        yield '\t\t{'
        for m in ifc.methods:
            for l in self._generateAccessorInvokeMethodCase(ifc, m):
                yield '\t\t{}'.format(l)
        yield '\t\tdefault:'
        yield '\t\t\treturn JOINT_ERROR_GENERIC;'
        yield '\t\t}'
        yield '\t}'
        yield '\tcatch (const ::joint::detail::JointCppException& ex)'
        yield '\t{'
        yield '\t\tconst char* method_names[] = {{ {} }};'.format(', '.join('"{}.{}"'.format(ifc.fullname, m.name) for m in ifc.methods))
        yield '\t\treturn ::joint::detail::WrapCppException<ComponentImpl_>(ex, outRetValue, method_names[methodId]);'
        yield '\t}'
        yield '\tcatch (const std::exception& ex)'
        yield '\t{'
        yield '\t\tconst char* method_names[] = {{ {} }};'.format(', '.join('"{}.{}"'.format(ifc.fullname, m.name) for m in ifc.methods))
        yield '\t\treturn ::joint::detail::WrapCppException<ComponentImpl_>(ex, outRetValue, method_names[methodId]);'
        yield '\t}'
        yield '\toutRetValue->releaseValue = &::joint::detail::_ReleaseRetValue;'
        yield '\treturn JOINT_ERROR_NONE;'
        yield '}'

    def _toCppValue(self, varName, type):
        if isinstance(type, BuiltinType):
            if type.category == BuiltinTypeCategory.string:
                return '{}.c_str()'.format(varName)
            else:
                return varName
        elif isinstance(type, Interface):
            return '{}->_GetObjectHandle()'.format(varName)
        elif isinstance(type, Enum):
            return '{}._RawValue()'.format(varName)
        else:
            raise RuntimeError('Not implemented (type: {})!'.format(type))

    def _toCppParamGetter(self, p):
        return self._toCppValue(p.name, p.type)

    def _wrapRetValue(self, type):
        if isinstance(type, BuiltinType):
            if type.name != 'bool':
                return '\treturn {}(_ret_val.result.value.{});'.format(self._toCppType(type), type.variantName)
            else:
                return '\treturn _ret_val.result.value.{} != 0;'.format(type.variantName)
        elif isinstance(type, Interface):
            return '\treturn {}({}(_ret_val.result.value.{}));'.format(self._toCppType(type), self._mangleType(type), type.variantName)
        elif isinstance(type, Enum):
            return '\treturn {}::_Value(_ret_val.result.value.{});'.format(self._toCppType(type), type.variantName)
        else:
            raise RuntimeError('Not implemented (type: {})!'.format(type))

    def _toCppType(self, type):
        if isinstance(type, BuiltinType):
            if type.category == BuiltinTypeCategory.void:
                return 'void'
            if type.category == BuiltinTypeCategory.int:
                return '{}int{}_t'.format('' if type.signed else 'u', type.bits)
            if type.category == BuiltinTypeCategory.bool:
                return 'bool'
            if type.category == BuiltinTypeCategory.float:
                if type.bits == 32:
                    return 'float'
                if type.bits == 64:
                    return 'double'
                raise RuntimeError('Unsupported floatint point type (bits: {})'.format(type.bits))
            if type.category == BuiltinTypeCategory.string:
                return 'std::string'
            raise RuntimeError('Unknown type: {}'.format(type))
        elif isinstance(type, Interface):
            return '{}_Ptr'.format(self._mangleType(type));
        elif isinstance(type, Enum):
            return '{}'.format(self._mangleType(type));
        else:
            raise RuntimeError('Not implemented (type: {})!'.format(type))

    def _mangleType(self, ifc):
        return '::{}::{}'.format('::'.join(ifc.packageNameList), ifc.name)
