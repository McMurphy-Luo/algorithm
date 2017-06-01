cmake_minimum_required(VERSION 3.5)
project(algorithm C CXX)
set(CMAKE_CXX_STANDARD 11)

set(lib_output_dir ${PROJECT_BINARY_DIR}/lib)
set(bin_output_dir ${PROJECT_BINARY_DIR}/bin)
set(source_dir ${PROJECT_SOURCE_DIR}/src)
set(test_source_dir ${PROJECT_SOURCE_DIR}/test)
include_directories(${source_dir})

list(APPEND data_structure_source
        ${source_dir}/config.h
        ${source_dir}/data_structure/linked_list.h
        ${source_dir}/data_structure/avl_tree.h
        ${source_dir}/data_structure/binary_tree.h
        ${source_dir}/data_structure/rb_tree.h
        ${source_dir}/data_structure/array_list.h)

list(APPEND windows_source
        ${source_dir}/windows/render/tree_render.h
        ${source_dir}/windows/render/tree_render.cpp
        ${source_dir}/windows/render/node_render.h
        ${source_dir}/windows/render/node_render.cpp
        ${source_dir}/windows/controller.h
        ${source_dir}/windows/controller.cpp
        ${source_dir}/windows/main_window.h
        ${source_dir}/windows/main_window.cpp
        ${source_dir}/windows/win_main.cpp
        ${source_dir}/windows/graphics/color.h
        ${source_dir}/windows/graphics/d2d_color.h
        ${source_dir}/windows/graphics/d2d_color.cpp
        ${source_dir}/windows/graphics/ellipse.h
        ${source_dir}/windows/graphics/d2d_ellipse.h
        ${source_dir}/windows/graphics/d2d_ellipse.cpp
        ${source_dir}/windows/graphics/image.cpp
        ${source_dir}/windows/graphics/image.h
        ${source_dir}/windows/graphics/point.h
        ${source_dir}/windows/graphics/transformation.h)

add_library(data_structure ${data_structure_source})
add_executable(list_test ${test_source_dir}/list.cpp)
add_executable(simple_test ${test_source_dir}/test.cpp)
add_executable(binary_tree_test ${test_source_dir}/binary_tree.cpp)
add_executable(render ${windows_source})

list(APPEND all_exe
        list_test
        simple_test
        binary_tree_test
        render
        )
list(APPEND all_lib
        data_structure
        )
list(APPEND all_target
        ${all_exe}
        ${all_lib})

set_target_properties(${all_target} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${all_lib} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${lib_output_dir})
set_target_properties(${all_exe} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${bin_output_dir})
