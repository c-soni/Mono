cmake_minimum_required(VERSION 3.19)
project(Interpreter8085 CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
include(cmake/SetCompilerWarnings.cmake)

# add the executable
add_executable(app src/main.cpp)
add_library(project_options INTERFACE)

target_compile_features(project_options INTERFACE cxx_std_20)
set_project_warnings(project_options)

target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR}/inc)
target_link_libraries(app project_options ${CONAN_LIBS})
