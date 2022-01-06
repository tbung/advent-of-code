cmake_minimum_required(VERSION 3.16)

project(AOC VERSION 1.0
                  DESCRIPTION "Very nice project"
                  LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS yes)

file(GLOB_RECURSE source_list RELATIVE ${CMAKE_SOURCE_DIR} "src/*")

foreach(file_path ${source_list})
    string(REPLACE ".cpp" "" new_name ${file_path} )
    get_filename_component(filename ${new_name} NAME)
    add_executable( ${filename} ${file_path} )
    set_property(TARGET ${filename} PROPERTY CXX_STANDARD 20)
endforeach()
