# add the executable
add_executable(i8085 src/main.cpp)

target_include_directories(i8085 PRIVATE inc)
target_link_libraries(i8085 PRIVATE project_options ${CONAN_LIBS})
