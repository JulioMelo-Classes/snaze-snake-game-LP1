cmake_minimum_required(VERSION 3.5)
project(Snaze VERSION 0.1 LANGUAGES CXX )

include_directories( include )
set (CMAKE_CXX_FLAGS "-g -W")

add_executable( snaze
                src/SnakeGame.cpp
                src/Level.cpp
                src/Player.cpp
                src/utils.cpp
                src/main.cpp
                )