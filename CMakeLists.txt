cmake_minimum_required(VERSION 3.5)

project(snake LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

add_executable(snake main.cpp game.hpp game.cpp snake.hpp snake.cpp)

target_link_libraries(snake sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
