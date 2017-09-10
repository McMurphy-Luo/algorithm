cmake_minimum_required(VERSION 3.5)
project(algorithm C CXX)
set(CMAKE_CXX_STANDARD 11)

set(lib_output_dir ${PROJECT_BINARY_DIR}/lib)
set(bin_output_dir ${PROJECT_BINARY_DIR}/bin)
set(source_dir ${PROJECT_SOURCE_DIR}/src)
set(test_source_dir ${PROJECT_SOURCE_DIR}/test)
include_directories(${source_dir})

if(${UNIX})
    set(CMAKE_CXX_FLAGS "-Werror -Wall -O0 -g")
endif(${UNIX})

list(APPEND common_source
        ${source_dir}/common/string_util.h
        ${source_dir}/common/string_util.cpp)

list(APPEND data_structure_source
        ${source_dir}/data_structure/tree_node.h
        ${source_dir}/data_structure/linked_list.h
        ${source_dir}/data_structure/avl_tree.h
        ${source_dir}/data_structure/binary_tree.h
        ${source_dir}/data_structure/rb_tree.h
        ${source_dir}/data_structure/array_list.h)

list(APPEND windows_source
        ${source_dir}/windows/render/tree_render.h
        ${source_dir}/windows/render/tree_render.cpp
        ${source_dir}/windows/controller.h
        ${source_dir}/windows/controller.cpp
        ${source_dir}/windows/main_window.h
        ${source_dir}/windows/main_window.cpp
        ${source_dir}/windows/win_main.cpp)

add_library(data_structure ${data_structure_source})
add_executable(list_test ${test_source_dir}/list.cpp)
add_executable(simple_test ${test_source_dir}/test.cpp)
add_executable(binary_tree_test ${test_source_dir}/binary_tree.cpp)
if(${WIN32})
add_executable(render ${windows_source} ${common_source})
target_compile_definitions(render PUBLIC "UNICODE" "_UNICODE")
endif(${WIN32})

list(APPEND all_exe
        list_test
        simple_test
        binary_tree_test
        )
if(${WIN32})
list(APPEND all_exe render)
endif(${WIN32})
list(APPEND all_lib
        data_structure
        )
list(APPEND all_target
        ${all_exe}
        ${all_lib})

if(${WIN32})
    target_link_libraries(render d2d1.lib dwrite.lib)
endif(${WIN32})


set_target_properties(${all_target} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${all_lib} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${lib_output_dir})
if(${WIN32})
    set_target_properties(render PROPERTIES WIN32_EXECUTABLE TRUE)
endif(${WIN32})
set_target_properties(${all_exe} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${bin_output_dir})
