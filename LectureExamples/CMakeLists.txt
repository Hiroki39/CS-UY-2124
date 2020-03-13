cmake_minimum_required (VERSION 3.10)

project (LectureExamples)

add_compile_options(-Wall -std=c++14 -g)


# Find all cpp files and store in list mains
file(GLOB mains RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
foreach(mainfile IN LISTS mains)
    if(testPrincess.cpp STREQUAL ${mainfile})
      add_executable(testPrincess testPrincess.cpp Princess.cpp FrogPrince.cpp)
    else()
      # Get file name without directory
      get_filename_component(mainname ${mainfile} NAME_WE)
      add_executable(${mainname} ${mainfile})
    endif()
endforeach()
