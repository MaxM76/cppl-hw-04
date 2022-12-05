cmake_minimum_required(VERSION 3.22.0)
project(using_catch2_project)

add_executable(using_catch2_program cppl-hw-4.1.cpp)

find_package(Catch2 CONFIG REQUIRED)
target_link_libraries(using_catch2_program PRIVATE Catch2::Catch2 Catch2::Catch2WithMain)