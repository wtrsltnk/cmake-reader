# Checkout : https://rix0r.nl/blog/2015/08/13/cmake-guide/

cmake_minimum_required(VERSION 3.3)

project(subcmake)

add_executable(subcmake
    program.cpp
    tokenizer.cpp
    tokenizer.h
    interpreter.cpp
    interpreter.h
    )

target_compile_features(subcmake
    PRIVATE cxx_nullptr
    PRIVATE cxx_range_for
    )
