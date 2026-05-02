cmake_minimum_required(VERSION 3.21)
project(OpenGLTriangle VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenGL REQUIRED)
find_package(FreeGLUT CONFIG REQUIRED)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
