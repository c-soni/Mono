cmake_minimum_required(VERSION 3.19)
project(Interpreter8085 CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
include(cmake/SetCompilerWarnings.cmake)

add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_20)
set_project_warnings(project_options)

add_subdirectory(projects)
