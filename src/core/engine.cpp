#include "engine.hpp"

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

void Engine::initialize() {
  auto window = Window::initialize(&settings.display, "test");

  if (!window) {
    throw std::runtime_error("Failed to initialize window");
  }

  this->time.set(window->time());
  this->window = std::move(window);
}

void Engine::run() {}

void Engine::terminate() {}