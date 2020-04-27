cmake_minimum_required (VERSION 3.10)

project (hw08)

add_compile_options(-Wall -std=c++14 -g)

aux_source_directory(. DIR_SRCS)
add_executable(hw08 ${DIR_SRCS})
