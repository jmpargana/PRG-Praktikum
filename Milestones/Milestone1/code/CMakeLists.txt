# https://www.jetbrains.com/help/clion/quick-cmake-tutorial.html
# https://riptutorial.com/de/cmake
# https://cliutils.gitlab.io/modern-cmake/chapters/intro/installing.html


cmake_minimum_required(VERSION 3.15)
# project(cmake_prgpr_game_life_vis_crypt)
# project(prgpr_m1)
project(code)
project(vis_crypt)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(vis_crypt
        include/catch.hpp
        include/matrix.hpp
        include/vis_crypt.h
        src/matrix.cpp
        src/vis_crypt.cpp)


add_executable(code
        include/catch.hpp
        include/cellular_automaton.hpp
        include/matrix.hpp
        include/vis_crypt.h
        src/Aufgabe1ab/aufgabe1.cpp
        src/cellular_automaton.cpp
        src/game_of_life.cpp
        src/matrix.cpp
        src/vis_crypt.cpp)
