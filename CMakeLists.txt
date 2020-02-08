cmake_minimum_required(VERSION 3.15)
project(yellow_final)

set(CMAKE_CXX_STANDARD 17)

add_executable(yellow_final main.cpp token.cpp token.h condition_parser.cpp condition_parser.h test_runner.h condition_parser_test.cpp node.cpp node.h date.cpp date.h database.cpp database.h)