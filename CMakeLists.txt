cmake_minimum_required(VERSION 3.5)
project(algorithm C CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Werror -Wall -Wextra -Wold-style-cast -Woverloaded-virtual -g")

set(lib_output_dir ${PROJECT_BINARY_DIR}/lib)
set(bin_output_dir ${PROJECT_BINARY_DIR}/bin)
set(source_dir ${PROJECT_SOURCE_DIR}/src)
set(test_source_dir ${PROJECT_SOURCE_DIR}/test)
include_directories(${source_dir})

list(APPEND data_structure_source
        ${source_dir}/data_structure/linked_list.h
        ${source_dir}/data_structure/avl_tree.h
        ${source_dir}/data_structure/binary_tree.h
        ${source_dir}/data_structure/rb_tree.h
        ${source_dir}/data_structure/array_list.h)
list(APPEND all_exe
        list_test
        simple_test
        )
list(APPEND all_lib
        data_structure
        )
list(APPEND all_target
        ${all_exe}
        ${all_lib})

add_library(data_structure ${data_structure_source})
add_executable(list_test ${test_source_dir}/list.cpp)
add_executable(simple_test ${test_source_dir}/test.cpp)

set_target_properties(${all_target} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${all_lib} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${lib_output_dir})
set_target_properties(${all_exe} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${bin_output_dir})
