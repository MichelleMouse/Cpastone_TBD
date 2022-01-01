cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall -pthread")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(Snake_Game)

# Locates SDL2 and SDL2_image library
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} src include)

# Find all executables
# include_directories(include)
add_executable(Snake src/main.cpp src/renderer.cpp src/snake.cpp src/game.cpp src/controller.cpp src/food.cpp)

string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(Snake ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
