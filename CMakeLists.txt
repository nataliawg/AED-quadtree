cmake_minimum_required(VERSION 3.16)
project(QuadTreeGraphics)

set(CMAKE_CXX_STANDARD 17)

# Ruta a SFML
set(SFML_DIR "C:/Users/DELL/CLionProjects/QuadTreeGraphics/cmake-build-debug/SFML-2.6.2")  # Cambia esta ruta según tu sistema

# Incluir SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Archivo fuente
add_executable(QuadTreeGraphics main.cpp)

# Enlazar las bibliotecas de SFML
target_link_libraries(QuadTreeGraphics sfml-graphics sfml-window sfml-system)
