cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME raytracer)

project(${PROJECT_NAME})

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)
find_package(SDL2 REQUIRED)

include_directories("src")
include_directories(${SDL2_INCLUDE_DIRS})

file(GLOB SOURCES "src/*.cc")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} Threads::Threads)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
