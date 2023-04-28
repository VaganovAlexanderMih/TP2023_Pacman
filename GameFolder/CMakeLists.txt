cmake_minimum_required(VERSION 3.18)

project(Pacman)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_COMPILER "gcc-4.2")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(Pacman Game.cpp)

target_link_libraries(Pacman sfml-graphics sfml-audio)
