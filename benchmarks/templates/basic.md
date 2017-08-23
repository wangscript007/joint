# C++
|               | void(), ns | void(i32), ns | i32(), ns | void(string-3), ns | string-3(), ns | void(string-100), ns | string-100(), ns |
| ------------- | ---------: | ------------: | --------: | -----------------: | -------------: | -------------------: | ---------------: |
| Native call   | ${basic.invokeNative_void_void.joint(module:build/bin/cpp/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeNative_void_i32.joint(module:build/bin/cpp/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeNative_i32_void.joint(module:build/bin/cpp/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeNative_void_string3.joint(module:build/bin/cpp/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeNative_string3_void.joint(module:build/bin/cpp/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeNative_void_string100.joint(module:build/bin/cpp/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeNative_string100_void.joint(module:build/bin/cpp/Benchmarks/Benchmarks.jm)[main]} |
| Incoming call | ${basic.invoke_void_void.joint(module:build/bin/cpp/Benchmarks/Benchmarks.jm)[main]} | ${basic.invoke_void_i32.joint(module:build/bin/cpp/Benchmarks/Benchmarks.jm)[main]} | ${basic.invoke_i32_void.joint(module:build/bin/cpp/Benchmarks/Benchmarks.jm)[main]} | ${basic.invoke_void_string3.joint(module:build/bin/cpp/Benchmarks/Benchmarks.jm)[main]} | ${basic.invoke_string3_void.joint(module:build/bin/cpp/Benchmarks/Benchmarks.jm)[main]} | ${basic.invoke_void_string100.joint(module:build/bin/cpp/Benchmarks/Benchmarks.jm)[main]} | ${basic.invoke_string100_void.joint(module:build/bin/cpp/Benchmarks/Benchmarks.jm)[main]} |
| Outgoing call | ${basic.invokeOutgoing_void_void.joint(module:build/bin/cpp/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeOutgoing_void_i32.joint(module:build/bin/cpp/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeOutgoing_i32_void.joint(module:build/bin/cpp/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeOutgoing_void_string3.joint(module:build/bin/cpp/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeOutgoing_string3_void.joint(module:build/bin/cpp/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeOutgoing_void_string100.joint(module:build/bin/cpp/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeOutgoing_string100_void.joint(module:build/bin/cpp/Benchmarks/Benchmarks.jm)[main]} |

# C
|               | void(), ns | void(i32), ns | i32(), ns | void(string-3), ns | string-3(), ns | void(string-100), ns | string-100(), ns |
| ------------- | ---------: | ------------: | --------: | -----------------: | -------------: | -------------------: | ---------------: |
| Native call   | ${basic.invokeNative_void_void.joint(module:build/bin/c/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeNative_void_i32.joint(module:build/bin/c/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeNative_i32_void.joint(module:build/bin/c/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeNative_void_string3.joint(module:build/bin/c/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeNative_string3_void.joint(module:build/bin/c/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeNative_void_string100.joint(module:build/bin/c/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeNative_string100_void.joint(module:build/bin/c/Benchmarks/Benchmarks.jm)[main]} |
| Incoming call | ${basic.invoke_void_void.joint(module:build/bin/c/Benchmarks/Benchmarks.jm)[main]} | ${basic.invoke_void_i32.joint(module:build/bin/c/Benchmarks/Benchmarks.jm)[main]} | ${basic.invoke_i32_void.joint(module:build/bin/c/Benchmarks/Benchmarks.jm)[main]} | ${basic.invoke_void_string3.joint(module:build/bin/c/Benchmarks/Benchmarks.jm)[main]} | ${basic.invoke_string3_void.joint(module:build/bin/c/Benchmarks/Benchmarks.jm)[main]} | ${basic.invoke_void_string100.joint(module:build/bin/c/Benchmarks/Benchmarks.jm)[main]} | ${basic.invoke_string100_void.joint(module:build/bin/c/Benchmarks/Benchmarks.jm)[main]} |
| Outgoing call | ${basic.invokeOutgoing_void_void.joint(module:build/bin/c/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeOutgoing_void_i32.joint(module:build/bin/c/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeOutgoing_i32_void.joint(module:build/bin/c/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeOutgoing_void_string3.joint(module:build/bin/c/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeOutgoing_string3_void.joint(module:build/bin/c/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeOutgoing_void_string100.joint(module:build/bin/c/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeOutgoing_string100_void.joint(module:build/bin/c/Benchmarks/Benchmarks.jm)[main]} |

# Python
## joint
|               | void(), ns | void(i32), ns | i32(), ns | void(string-3), ns | string-3(), ns | void(string-100), ns | string-100(), ns |
| ------------- | ---------: | ------------: | --------: | -----------------: | -------------: | -------------------: | ---------------: |
| Native call   | ${basic.invokeNative_void_void.joint(module:build/bin/python/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeNative_void_i32.joint(module:build/bin/python/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeNative_i32_void.joint(module:build/bin/python/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeNative_void_string3.joint(module:build/bin/python/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeNative_string3_void.joint(module:build/bin/python/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeNative_void_string100.joint(module:build/bin/python/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeNative_string100_void.joint(module:build/bin/python/Benchmarks/Benchmarks.jm)[main]} |
| Incoming call | ${basic.invoke_void_void.joint(module:build/bin/python/Benchmarks/Benchmarks.jm)[main]} | ${basic.invoke_void_i32.joint(module:build/bin/python/Benchmarks/Benchmarks.jm)[main]} | ${basic.invoke_i32_void.joint(module:build/bin/python/Benchmarks/Benchmarks.jm)[main]} | ${basic.invoke_void_string3.joint(module:build/bin/python/Benchmarks/Benchmarks.jm)[main]} | ${basic.invoke_string3_void.joint(module:build/bin/python/Benchmarks/Benchmarks.jm)[main]} | ${basic.invoke_void_string100.joint(module:build/bin/python/Benchmarks/Benchmarks.jm)[main]} | ${basic.invoke_string100_void.joint(module:build/bin/python/Benchmarks/Benchmarks.jm)[main]} |
| Outgoing call | ${basic.invokeOutgoing_void_void.joint(module:build/bin/python/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeOutgoing_void_i32.joint(module:build/bin/python/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeOutgoing_i32_void.joint(module:build/bin/python/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeOutgoing_void_string3.joint(module:build/bin/python/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeOutgoing_string3_void.joint(module:build/bin/python/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeOutgoing_void_string100.joint(module:build/bin/python/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeOutgoing_string100_void.joint(module:build/bin/python/Benchmarks/Benchmarks.jm)[main]} |

## swig
|               | void(), ns | void(i32), ns | i32(), ns | void(string-3), ns | string-3(), ns | void(string-100), ns | string-100(), ns |
| ------------- | ---------: | ------------: | --------: | -----------------: | -------------: | -------------------: | ---------------: |
| Native call   | ${basic.invokeNative_void_void.swig(module:benchmarks/swig/python.manifest)[main]} | ${basic.invokeNative_void_i32.swig(module:benchmarks/swig/python.manifest)[main]} | ${basic.invokeNative_i32_void.swig(module:benchmarks/swig/python.manifest)[main]} | ${basic.invokeNative_void_string3.swig(module:benchmarks/swig/python.manifest)[main]} | ${basic.invokeNative_string3_void.swig(module:benchmarks/swig/python.manifest)[main]} | ${basic.invokeNative_void_string100.swig(module:benchmarks/swig/python.manifest)[main]} | ${basic.invokeNative_string100_void.swig(module:benchmarks/swig/python.manifest)[main]} |
| Incoming call | ${basic.invoke_void_void.swig(module:benchmarks/swig/python.manifest)[main]} | ${basic.invoke_void_i32.swig(module:benchmarks/swig/python.manifest)[main]} | ${basic.invoke_i32_void.swig(module:benchmarks/swig/python.manifest)[main]} | ${basic.invoke_void_string3.swig(module:benchmarks/swig/python.manifest)[main]} | ${basic.invoke_string3_void.swig(module:benchmarks/swig/python.manifest)[main]} | ${basic.invoke_void_string100.swig(module:benchmarks/swig/python.manifest)[main]} | ${basic.invoke_string100_void.swig(module:benchmarks/swig/python.manifest)[main]} |
| Outgoing call | ${basic.invokeOutgoing_void_void.swig(module:benchmarks/swig/python.manifest)[main]} | ${basic.invokeOutgoing_void_i32.swig(module:benchmarks/swig/python.manifest)[main]} | ${basic.invokeOutgoing_i32_void.swig(module:benchmarks/swig/python.manifest)[main]} | ${basic.invokeOutgoing_void_string3.swig(module:benchmarks/swig/python.manifest)[main]} | ${basic.invokeOutgoing_string3_void.swig(module:benchmarks/swig/python.manifest)[main]} | ${basic.invokeOutgoing_void_string100.swig(module:benchmarks/swig/python.manifest)[main]} | ${basic.invokeOutgoing_string100_void.swig(module:benchmarks/swig/python.manifest)[main]} |

# Java
## joint
|               | void(), ns | void(i32), ns | i32(), ns | void(string-3), ns | string-3(), ns | void(string-100), ns | string-100(), ns |
| ------------- | ---------: | ------------: | --------: | -----------------: | -------------: | -------------------: | ---------------: |
| Native call   | ${basic.invokeNative_void_void.joint(module:build/bin/java/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeNative_void_i32.joint(module:build/bin/java/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeNative_i32_void.joint(module:build/bin/java/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeNative_void_string3.joint(module:build/bin/java/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeNative_string3_void.joint(module:build/bin/java/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeNative_void_string100.joint(module:build/bin/java/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeNative_string100_void.joint(module:build/bin/java/Benchmarks/Benchmarks.jm)[main]} |
| Incoming call | ${basic.invoke_void_void.joint(module:build/bin/java/Benchmarks/Benchmarks.jm)[main]} | ${basic.invoke_void_i32.joint(module:build/bin/java/Benchmarks/Benchmarks.jm)[main]} | ${basic.invoke_i32_void.joint(module:build/bin/java/Benchmarks/Benchmarks.jm)[main]} | ${basic.invoke_void_string3.joint(module:build/bin/java/Benchmarks/Benchmarks.jm)[main]} | ${basic.invoke_string3_void.joint(module:build/bin/java/Benchmarks/Benchmarks.jm)[main]} | ${basic.invoke_void_string100.joint(module:build/bin/java/Benchmarks/Benchmarks.jm)[main]} | ${basic.invoke_string100_void.joint(module:build/bin/java/Benchmarks/Benchmarks.jm)[main]} |
| Outgoing call | ${basic.invokeOutgoing_void_void.joint(module:build/bin/java/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeOutgoing_void_i32.joint(module:build/bin/java/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeOutgoing_i32_void.joint(module:build/bin/java/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeOutgoing_void_string3.joint(module:build/bin/java/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeOutgoing_string3_void.joint(module:build/bin/java/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeOutgoing_void_string100.joint(module:build/bin/java/Benchmarks/Benchmarks.jm)[main]} | ${basic.invokeOutgoing_string100_void.joint(module:build/bin/java/Benchmarks/Benchmarks.jm)[main]} |

## swig
|               | void(), ns | void(i32), ns | i32(), ns | void(string-3), ns | string-3(), ns | void(string-100), ns | string-100(), ns |
| ------------- | ---------: | ------------: | --------: | -----------------: | -------------: | -------------------: | ---------------: |
| Native call   | ${basic.invokeNative_void_void.swig(module:benchmarks/swig/java.manifest)[main]} | ${basic.invokeNative_void_i32.swig(module:benchmarks/swig/java.manifest)[main]} | ${basic.invokeNative_i32_void.swig(module:benchmarks/swig/java.manifest)[main]} | ${basic.invokeNative_void_string3.swig(module:benchmarks/swig/java.manifest)[main]} | ${basic.invokeNative_string3_void.swig(module:benchmarks/swig/java.manifest)[main]} | ${basic.invokeNative_void_string100.swig(module:benchmarks/swig/java.manifest)[main]} | ${basic.invokeNative_string100_void.swig(module:benchmarks/swig/java.manifest)[main]} |
| Incoming call | ${basic.invoke_void_void.swig(module:benchmarks/swig/java.manifest)[main]} | ${basic.invoke_void_i32.swig(module:benchmarks/swig/java.manifest)[main]} | ${basic.invoke_i32_void.swig(module:benchmarks/swig/java.manifest)[main]} | ${basic.invoke_void_string3.swig(module:benchmarks/swig/java.manifest)[main]} | ${basic.invoke_string3_void.swig(module:benchmarks/swig/java.manifest)[main]} | ${basic.invoke_void_string100.swig(module:benchmarks/swig/java.manifest)[main]} | ${basic.invoke_string100_void.swig(module:benchmarks/swig/java.manifest)[main]} |
| Outgoing call | ${basic.invokeOutgoing_void_void.swig(module:benchmarks/swig/java.manifest)[main]} | ${basic.invokeOutgoing_void_i32.swig(module:benchmarks/swig/java.manifest)[main]} | ${basic.invokeOutgoing_i32_void.swig(module:benchmarks/swig/java.manifest)[main]} | ${basic.invokeOutgoing_void_string3.swig(module:benchmarks/swig/java.manifest)[main]} | ${basic.invokeOutgoing_string3_void.swig(module:benchmarks/swig/java.manifest)[main]} | ${basic.invokeOutgoing_void_string100.swig(module:benchmarks/swig/java.manifest)[main]} | ${basic.invokeOutgoing_string100_void.swig(module:benchmarks/swig/java.manifest)[main]} |