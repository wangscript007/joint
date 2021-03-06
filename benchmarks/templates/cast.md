# C++
| Cast                | Time, ns |
| ------------------- | -------: |
| Native cast         | ${cast.native.joint(lang:cpp)[main]} |
| Component-side cast | ${cast.component.joint(lang:cpp)[main]} |
| Proxy-side cast     | ${cast.proxy.joint(lang:cpp)[main]} |

# C++ (no exceptions)
| Cast                | Time, ns |
| ------------------- | -------: |
| Native cast         | - |
| Component-side cast | ${cast.component.joint(lang:cpp_ne)[main]} |
| Proxy-side cast     | ${cast.proxy.joint(lang:cpp_ne)[main]} |

# C
| Cast                | Time, ns |
| ------------------- | -------: |
| Native cast         | - |
| Component-side cast | ${cast.component.joint(lang:c)[main]} |
| Proxy-side cast     | ${cast.proxy.joint(lang:c)[main]} |

# Python
| Cast                | Time, ns |
| ------------------- | -------: |
| Native cast         | - |
| Component-side cast | ${cast.component.joint(lang:python)[main]} |
| Proxy-side cast     | ${cast.proxy.joint(lang:python)[main]} |

# Java
| Cast                | Time, ns |
| ------------------- | -------: |
| Native cast         | - |
| Component-side cast | ${cast.component.joint(lang:java)[main]} |
| Proxy-side cast     | ${cast.proxy.joint(lang:java)[main]} |
