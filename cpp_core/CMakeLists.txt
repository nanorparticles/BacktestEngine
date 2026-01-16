cmake_minimum_required(VERSION 3.10)
project(BacktestEngine)

set(CMAKE_CXX_STANDARD 17)
include_directories(include)

set(SOURCES
    src/main.cpp
    src/BacktestEngine.cpp
    src/BuyAndHoldStrategy.cpp
    src/Event.cpp
    src/Asset.cpp
    src/Portfolio.cpp
    src/Strategy.cpp
    src/RiskManager.cpp
    src/Metrics.cpp
)

add_executable(BacktestEngine ${SOURCES})