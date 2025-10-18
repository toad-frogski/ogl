#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "core/engine.hpp"
#include "bootstrap.cpp"

int main() {
  auto& engine = Engine::getInstance();

  try {
    engine.initialize();

    bootstrap(&engine);

    engine.run();
  } catch (const std::exception& err) {
    throw;
  }

  Engine::terminate();
  return 0;
}
