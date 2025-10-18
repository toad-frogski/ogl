#include "engine.hpp"

#include "input.hpp"
#include "window.hpp"

Engine::Engine() = default;
Engine::~Engine() = default;

static std::unique_ptr<Engine> instance = nullptr;

Engine& Engine::getInstance() {
  if (!instance) {
    instance = std::make_unique<Engine>();
  }

  return *instance;
}

EngineSettings& Engine::getSettings() { return settings; }
Window& Engine::getWindow() { return *window; }
Input& Engine::getInput() { return *input; }

void Engine::initialize() {
  auto window = Window::initialize(&settings.display, "test");
  if (!window) {
    throw std::runtime_error("Failed to initialize window");
  }

  this->time.set(window->time());
  this->window = std::move(window);

  auto input = Input::initialize(this->window.get());
  if (!input) {
    throw std::runtime_error("Failed to initialize input");
  }

  this->input = std::move(input);
}

void Engine::run() {
  auto& window = this->getWindow();
  while (!window.isShouldClose()) {
    time.update(window.time());
    this->update();
    this->renderFrame();
    this->postUpdate();
    this->nextFrame();
  }
}

void Engine::update() {}

void Engine::renderFrame() {}

void Engine::postUpdate() {}

void Engine::nextFrame() {
  window->swapBuffers();
  input->pollEvents();
}

void Engine::terminate() {}
