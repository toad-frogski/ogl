cmake_minimum_required(VERSION 3.30)
project(ogl)

cmake_policy(SET CMP0072 NEW)

add_library(glad external/glad/src/gl.c)
target_include_directories(glad PUBLIC external/glad/include)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm CONFIG REQUIRED)

add_subdirectory(src)
add_executable(ogl src/main.cpp)

target_link_libraries(ogl PRIVATE
  glad
  glfw
  OpenGL::GL
  glm::glm
  olgSrc
)
