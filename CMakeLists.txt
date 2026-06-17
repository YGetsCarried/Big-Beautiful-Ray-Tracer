cmake_minimum_required(VERSION 3.10)
project(ppm_gradient LANGUAGES CXX)


include_directories(include)
add_executable(ppm_gradient src/main.cpp src/utils.c)