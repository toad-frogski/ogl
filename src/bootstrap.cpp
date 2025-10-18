#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "core/engine.hpp"

inline void register_handlers(Engine* engine) {
  auto& input = engine->getInput();

  input.addHandler(GLFW_KEY_ESCAPE, []() {
    auto& window = Engine::getInstance().getWindow();
    window.setShouldClose(true);
  });
}

static void bootstrap(Engine *engine) {
  register_handlers(engine);
}