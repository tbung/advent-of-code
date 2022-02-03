cmake_minimum_required(VERSION 3.16)

project(AOC VERSION 1.0
                  DESCRIPTION "Very nice project"
                  LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS yes)

file(GLOB_RECURSE source_list RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c")

foreach(file_path ${source_list})
    string(REPLACE ".c" "" new_name ${file_path} )
    get_filename_component(filename ${new_name} NAME)
    add_executable( ${filename} ${file_path} "src/util.h")
endforeach()
