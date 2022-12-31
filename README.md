# blackthorn
Easy to use client-server library with C++ and Boost

<br/>

How to run:
- **mkdir build**
- **cd build**
- **pip install -U pip**
- **pip install -U conan**
- **conan install .. [-s build_type={Debug | Release}]**
- **cmake build -S ..**

*For latest MSVC compiler:
- **conan install .. [-s build_type={Debug | Release}] -s compiler.version=17 -s compiler.toolset=v143 --build=missing**
