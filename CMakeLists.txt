cmake_minimum_required(VERSION 3.15)
project(untitled2)

set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR "C:/Users/NATALIA WATSON/Downloads/SFML-2.6.2-windows-gcc-13.1.0-mingw-64-bit/SFML-2.6.2/lib/cmake/SFML")

find_package(SFML COMPONENTS graphics window system REQUIRED)

add_executable(AED-quadtree main.cpp quadtree.cpp)
target_link_libraries(AED-quadtree sfml-graphics sfml-window sfml-system)