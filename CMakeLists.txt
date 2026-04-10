cmake_minimum_required(VERSION 3.16)

project(eos VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DPROJECT_ROOT=\"${CMAKE_SOURCE_DIR}\")

add_subdirectory(manager)

