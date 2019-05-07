cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME raytracer)

project(${PROJECT_NAME})

include_directories("src")

file(GLOB SOURCES "src/*.cc")

add_executable(${PROJECT_NAME} ${SOURCES})
