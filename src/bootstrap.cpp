#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "core/engine.hpp"
#include "core/detail/_glfw_input.hpp"
#include "screen/main_screen.cpp"

static void register_handlers(Engine* engine) {
  auto& input = engine->getInput();

  input.addHandler(GLFW_KEY_ESCAPE, []() {
    auto& window = Engine::getInstance().getWindow();
    window.setShouldClose(true);
  });

  input.addHandler(GLFW_KEY_GRAVE_ACCENT, []() {
    auto& input = Engine::getInstance().getInput();
    input.toggleCursor();
  });

  input.addHandler(GLFW_KEY_W, []() {
    auto camera = Engine::getInstance().getCamera();
    if (!camera) return;

    auto offset = camera->front;
    offset *= 0.1f;
    camera->position += offset;
  });

  input.addHandler(GLFW_KEY_S, []() {
    auto camera = Engine::getInstance().getCamera();
    if (!camera) return;

    auto offset = camera->front;
    offset *= 0.1f;
    camera->position -= offset;
  });

  input.addHandler(GLFW_KEY_D, []() {
    auto camera = Engine::getInstance().getCamera();
    if (!camera) return;

    auto offset = camera->right;
    offset *= 0.1f;
    camera->position += offset;
  });

  input.addHandler(GLFW_KEY_A, []() {
    auto camera = Engine::getInstance().getCamera();
    if (!camera) return;
    auto offset = camera->right;
    offset *= 0.1f;
    camera->position -= offset;
  });

  input.addHandler(GLFW_MOUSE_MOVE, []() {
    auto cursor = Engine::getInstance().getInput().getCursor();
    auto camera = Engine::getInstance().getCamera();
    if (!camera) return;
    camera->rotate(cursor.delta.x, cursor.delta.y);
  });
}

static void set_screen(Engine* engine) {
  auto screen = std::make_shared<MainScreen>();
  auto& settings = engine->getSettings();

  auto camera =
      std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
                               60.0f, (float)settings.display.width / settings.display.height, 0.1f, 100.0f);

  engine->setCamera(camera);
  engine->setScreen(screen);
}

static void bootstrap() {
  auto& engine = Engine::getInstance();

  set_screen(&engine);
  register_handlers(&engine);
}