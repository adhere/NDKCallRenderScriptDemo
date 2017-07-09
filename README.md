## A CMake NDK Demo Using RenderScript With rtti Flag

- It is for this issue [Is it possible to call RenderScript in NDK WITH "-frtti" ](https://github.com/android-ndk/ndk/issues/444).
- Mixing ndk-build and CMake, you can call RenderScript from NDK and DEBUG step by step. 
## TAKE CARE
- Maybe in the next Android Studio version or other update, it is out of date. Before using this project template, you should check the newest Android Studio whether fix the bug.
### Development Environment
- OS: Ubuntu 14.04
- Android Studio: 2.3.3
- NDK Version: 15.1.4119039
- cmake: the AS bundle one

### Project Structure
- Put RenderScript file at app/src/main/rs and pp/src/main/jni (Or should make a soft link)
- Put C++ sources  file at app/src/main/cpp/src
- Put C++ headers file at app/src/main/cpp/include

### Compile
1. First, Using ndk-build to build the RenderScript sources
```
Add an external tools to call ndk(Linux):
    Click File/Settings/Tools/External Tools, and add a new one
    The Program should be ${ANDROID_NDK}/ndk-build, such as "/home/pan/Android/Sdk/ndk-bundle/ndk-build"
    The Working directory should be $ModuleFileDir$/src/main/
Now, you can right click to External Tools to call the ndk.
    
```
2. Do the normal things as other cmake ndk projects.
