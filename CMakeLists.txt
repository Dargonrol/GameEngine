cmake_minimum_required(VERSION 3.16)
project(Pong VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Pong
	src/main.cpp
)
