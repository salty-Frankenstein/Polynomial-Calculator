cmake_minimum_required(VERSION 2.8)
project(Cal)
aux_source_directory(src SRC_LIST)
add_compile_options(-std=c++11)
add_executable(cal ${SRC_LIST})

