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
Time& Engine::getTime() { return time; }
Window& Engine::getWindow() { return *window; }
Input& Engine::getInput() { return *input; }

std::shared_ptr<Camera> Engine::getCamera() { return camera; }
void Engine::setCamera(std::shared_ptr<Camera> camera) { this->camera = std::move(camera); }

std::shared_ptr<Screen> Engine::getScreen() { return screen; }
void Engine::setScreen(std::shared_ptr<Screen> screen) { this->screen = std::move(screen); }

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
  auto& time = this->getTime();

  while (!window.isShouldClose()) {
    time.update(window.time());
    this->update();
    this->renderFrame();
    this->postUpdate();
    this->nextFrame();
  }
}

void Engine::update() { screen->update(time.getDelta()); }

void Engine::renderFrame() { screen->draw(time.getDelta()); }

void Engine::postUpdate() {}

void Engine::nextFrame() {
  window->swapBuffers();
  input->pollEvents();
}

void Engine::terminate() {}
