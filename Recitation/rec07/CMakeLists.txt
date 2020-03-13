cmake_minimum_required (VERSION 3.10)

project (rec07)

add_compile_options(-Wall -std=c++14 -g)

add_executable(rec07 rec07.cpp)
add_executable(rec07_separatecompilation rec07_separatecompilation.cpp Student.cpp Course.cpp Registar.cpp)
