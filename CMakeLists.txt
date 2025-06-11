cmake_minimum_required(VERSION 3.10)
project(NetworkTrafficAnalyzer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(network_analyzer
    main.cpp
    NetworkTrafficAnalyzer.cpp
)

target_include_directories(network_analyzer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}) 