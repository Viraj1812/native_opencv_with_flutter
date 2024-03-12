# The Flutter tooling requires that developers have CMake 3.10 or later
# installed. You should not increase this version, as doing so will cause
# the plugin to fail to compile for some customers of the plugin.
cmake_minimum_required(VERSION 3.4.1)

project(native_add_library VERSION 0.0.1 LANGUAGES CXX)

find_library(log-lib log)

set(pathToProject /Users/mac-mini-006/native_add/example/android/app)

include_directories(../opencv_include)

add_library(lib_opencv SHARED IMPORTED)

add_library(native_add SHARED native_add.cpp)

set_target_properties(native_add PROPERTIES
  PUBLIC_HEADER native_add.h
  OUTPUT_NAME "native_add"
)

set_target_properties(lib_opencv PROPERTIES IMPORTED_LOCATION ${pathToProject}/src/main/jniLibs/${ANDROID_ABI}/libopencv_java4.so)

target_link_libraries(native_add lib_opencv ${log-lib})