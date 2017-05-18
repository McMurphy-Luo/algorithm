cmake_minimum_required(VERSION 3.5)
project(algorithm C CXX)
set(CMAKE_CXX_STANDARD 11)
set(lib_output_dir ${PROJECT_BINARY_DIR}/lib)
set(bin_output_dir ${PROJECT_BINARY_DIR}/bin)
set(source_dir ${PROJECT_SOURCE_DIR}/src)
set(test_source_dir ${PROJECT_SOURCE_DIR}/test)
include_directories(${source_dir})

list(APPEND data_structure_source
        ${source_dir}/data_structure/linked_list.h
        ${source_dir}/data_structure/array_list.h)
add_library(data_structure ${data_structure_source})
add_executable(list_test ${test_source_dir}/list.cpp)
add_executable(test ${test_source_dir}/test.cpp)

list(APPEND all_target
        )

set_target_properties(data_structure list_test PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(data_structure PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${lib_output_dir})
set_target_properties(list_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${bin_output_dir})