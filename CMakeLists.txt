cmake_minimum_required(VERSION 3.20)
project(cpp_advanced_lab1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(app main.cpp CardDealer.cpp LabAnalyzer.cpp)