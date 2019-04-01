cmake_minimum_required(VERSION 3.0)

project(Ants)

set(CMAKE_CXX_STANDARD 17)

# If you want to link SFML statically
set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
#set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS graphics window system REQUIRED)

add_executable(Ants src/main.cpp src/Application.cpp src/Ant.cpp  src/Grain.cpp src/EntityManager.cpp)

target_link_libraries(Ants sfml-graphics sfml-window sfml-system)
