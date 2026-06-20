cmake_minimum_required(VERSION 3.10)
project(ppm_gradient LANGUAGES CXX)

include_directories(src)
add_executable(ppm_gradient src/main.cpp src/vec3.h src/color.h src/ray.h)