#!/usr/bin/python3

import timeit
from SomeInterface import *

import sys
sys.path.append('build/bin')

import pyjoint

m = pyjoint.Module('python', 'test_module')
obj = SomeInterface(m.GetRootObject('CreateSomeInterface'))

obj.Method1()
obj.Method2()

s = obj.ToString()
print('obj.ToString: {}'.format(s))

obj.PrintInt(42)
obj.PrintString('ohohoho')

other = obj.ReturnOther()
other.Func()

obj.AcceptOther(other)

del other
del obj
