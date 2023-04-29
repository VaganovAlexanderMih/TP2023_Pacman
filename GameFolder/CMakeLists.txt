cmake_minimum_required(VERSION 3.18)

project(Pacman)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(Pacman SinglePlayer.cpp GameMenu.cpp GameCore.cpp Maps.cpp Game.cpp)

target_link_libraries(Pacman sfml-graphics sfml-audio)
