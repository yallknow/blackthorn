# blackthorn
Easy to use client-server library with C++ and Boost

<br/>

How to start:
- **python -m pip install -U pip**
- **pip install --force-reinstall -v "conan==1.59.0"**

- **mkdir build**
- **cd build**

*For latest MSVC compiler:
- Debug:
    - **conan install .. -s compiler.version=17 -s compiler.toolset=v143 --build=missing -s build_type=Debug**
- Release:
    - **conan install .. -s compiler.version=17 -s compiler.toolset=v143 --build=missing -s build_type=Release**
*For default installation:
- Debug:
    - **conan install .. --build=missing -s build_type=Debug**
- Release:
    - **conan install .. --build=missing -s build_type=Release**

- **cmake build -S ..**
