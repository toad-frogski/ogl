#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "core/engine.hpp"
#include "screen/main_screen.cpp"

static void register_handlers(Engine* engine) {
  auto& input = engine->getInput();

  input.addHandler(GLFW_KEY_ESCAPE, []() {
    auto& window = Engine::getInstance().getWindow();
    window.setShouldClose(true);
  });

  input.addHandler(GLFW_KEY_SPACE, []() {
    auto camera = Engine::getInstance().getCamera();
    fprintf(stderr, "[camera] position (%f, %f, %f)\n", camera->position.x, camera->position.y, camera->position.z);
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
}

static void set_screen(Engine* engine) {
  auto screen = std::make_shared<MainScreen>();
  auto& settings = engine->getSettings();

  auto shader = std::make_shared<Shader>(
      R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    uniform mat4 mvp;
    void main() {
      gl_Position = mvp * vec4(aPos, 1.0);
    }
  )",
      R"(
    #version 330 core
    out vec4 FragColor;
    void main() {
      FragColor = vec4(0.2, 0.7, 1.0, 1.0);
    }
  )");

  std::vector<float> cubeVertices = {
      -0.5, -0.5, 0.5, 0.5, -0.5, 0.5, 0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, 0.5, 0.5, -0.5, 0.5, 0.5,
  };
  auto mesh = std::make_shared<Mesh>(cubeVertices);
  auto cube = std::make_shared<Model>(mesh, shader);

  screen->models.push_back(cube);

  auto camera =
      std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
                               60.0f, (float)settings.display.width / settings.display.height, 0.1f, 100.0f);

  engine->setCamera(camera);
  engine->setScreen(screen);
}

static void bootstrap(Engine* engine) {
  set_screen(engine);
  register_handlers(engine);
}