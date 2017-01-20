# Checkout : https://rix0r.nl/blog/2015/08/13/cmake-guide/

cmake_minimum_required(VERSION 3.3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

get_filename_component(NAME ${CMAKE_SOURCE_DIR} NAME)
project(${NAME}) #another comment
#comment1
#comment2

#comment3

include(files.cmake)

add_executable(${NAME} ${FILES})

if(${NAME} EQUAL "test")
    add_test(${NAME} ${FILES})
endif()
