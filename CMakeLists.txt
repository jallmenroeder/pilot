cmake_minimum_required(VERSION 3.20)
project(pilot)

set(CMAKE_CXX_STANDARD 20)

find_package(Vulkan)
if (NOT Vulkan_FOUND)
    message( FATAL_ERROR "Vulkan not found" )
endif()

add_executable(pilot main.cpp)
