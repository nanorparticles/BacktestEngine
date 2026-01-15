cmake_minimum_required(VERSION 3.10)
project(BacktestEngine)

set(CMAKE_CXX_STANDARD 17)
include_directories(include)

add_executable(BacktestEngine src/main.cpp src/engine.cpp)