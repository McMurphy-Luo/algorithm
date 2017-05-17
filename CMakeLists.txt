cmake_minimum_required(VERSION 3.5)
project(algorithm C CXX)
set(CMAKE_CXX_STANDARD 11)
set(lib_output_dir ${PROJECT_BINARY_DIR}/lib)
set(bin_output_dir ${PROJECT_BINARY_DIR}/bin)
set(source_dir ${PROJECT_SOURCE_DIR}/src)
set(test_source_dir ${PROJECT_SOURCE_DIR}/test)
include_directories(${source_dir})

list(APPEND data_structure_source
        ${source_dir}/data_structure/linked_list.h)
add_executable(list_test ${test_source_dir}/list.cpp)

set_property(TARGET list_test PROPERTY RUNTIME_OUTPUT_DIRECTORY ${bin_output_dir})