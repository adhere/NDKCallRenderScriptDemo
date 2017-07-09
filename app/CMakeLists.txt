# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# set some var
set(DEBUG_MODEL 1)
set(CPP_SOURCE_FILES "")
set(CPP_HEADER_FILES "")
set(RS_FILES "")
set(RS_OBJ_FILES "")
set(RENDER_SCRIPT_HEADERS_PATH ${ANDROID_NDK}/toolchains/renderscript/prebuilt/${ANDROID_HOST_TAG}/platform/rs)

# create the jniLibs
add_custom_target(
    make_jniLibs
    "${CMAKE_COMMAND}" -E make_directory "${PROJECT_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}"
    COMMENT "Create 'jniLibs'"
)

include_directories(src/main/cpp/include)
include_directories(${RENDER_SCRIPT_HEADERS_PATH}/cpp
                    ${RENDER_SCRIPT_HEADERS_PATH}/scriptc
                    ${RENDER_SCRIPT_HEADERS_PATH})
link_directories(${ANDROID_NDK}/toolchains/renderscript/prebuilt/${ANDROID_HOST_TAG}/platform/${ANDROID_SYSROOT_ABI})

file(GLOB_RECURSE CPP_SOURCE_FILES src/main/cpp/src/*)
file(GLOB_RECURSE CPP_HEADER_FILES src/main/cpp/include/*)
file(GLOB_RECURSE RS_FILES src/main/rs/*)

if(DEBUG_MODEL)
    include_directories(build/generated/source/rs/debug)
    file(GLOB_RECURSE RS_CPP_FILES build/generated/source/rs/debug/*)
else()
    include_directories(build/generated/source/rs/release)
    file(GLOB_RECURSE RS_CPP_FILES build/generated/source/rs/release/*)
endif()

foreach(rs_file ${RS_FILES})
    get_filename_component(name ${rs_file} NAME_WE)
    list(APPEND RS_OBJ_FILES ${PROJECT_SOURCE_DIR}/src/main/obj/local/${ANDROID_ABI}/objs/hellocomputendk/${name}.o)
    configure_file(${PROJECT_SOURCE_DIR}/src/main/obj/local/${ANDROID_ABI}/librs.${name}.so ${PROJECT_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI} COPYONLY)
endforeach()

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED
             ${CPP_SOURCE_FILES}
             ${RS_OBJ_FILES}
             ${RS_FILES}
  )

add_dependencies(native-lib make_jniLibs)


# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       native-lib
                       RScpp_static
                       jnigraphics
                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )