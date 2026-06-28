cmake_minimum_required(VERSION 3.10)
project(ray_tracer LANGUAGES CXX)

include_directories(src)
add_executable(ray_tracer src/main.cpp src/vec3.h src/color.h src/ray.h src/sphere.h src/rtweekend.h src/hittable_lists.h src/hittable.h src/camera.h)