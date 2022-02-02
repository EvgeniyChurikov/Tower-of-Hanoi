cmake_minimum_required(VERSION 3.21)
project(Tower-of-Hanoi)

set(CMAKE_CXX_STANDARD 23)

set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS graphics)

add_executable(Tower-of-Hanoi main.cpp Towers.cpp Towers.h Gui.cpp Gui.h Solver.cpp Solver.h)

target_link_libraries(Tower-of-Hanoi sfml-graphics)
