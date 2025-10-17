project(olg)

file(GLOB_RECURSE source CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE headers CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
list(REMOVE_ITEM source ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm CONFIG REQUIRED)

add_library(olgSrc STATIC ${source} ${headers})

target_include_directories(olgSrc PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(olgSrc PRIVATE
  glad
  glfw
  OpenGL::GL
  glm::glm
)