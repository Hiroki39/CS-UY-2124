cmake_minimum_required (VERSION 3.10)

project (testPrincess)

add_compile_options(-Wall -std=c++14 -g)

aux_source_directory(. DIR_SRCS)
add_executable(testPrincess ${DIR_SRCS})
