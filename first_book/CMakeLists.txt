cmake_minimum_required(VERSION 3.27)
project(ray_tracing)

set(CMAKE_CXX_STANDARD 17)

add_executable(ray_tracing main.cpp
        vec3.h
        color.h
        ray.h
        hittable.h
        sphere.h
        hittableList.h
        constants.h
        interval.h
        camera.h
        material.h)
