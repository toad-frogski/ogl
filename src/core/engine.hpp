#pragma once

#include <memory>
#include <stdexcept>

#include "settings.hpp"
#include "time.hpp"
#include "input.hpp"
#include "window.hpp"
#include "screen.hpp"
#include "camera.hpp"

class Engine {
  std::unique_ptr<Window> window;
  std::unique_ptr<Input> input;
  std::shared_ptr<Camera> camera;
  std::shared_ptr<Screen> screen;
  Time time;
  EngineSettings settings;

 public:
  Engine();
  ~Engine();

  static Engine& getInstance();

  Time& getTime();
  Window& getWindow();
  Input& getInput();
  EngineSettings& getSettings();

  std::shared_ptr<Camera> getCamera();
  void setCamera(std::shared_ptr<Camera> screen);

  std::shared_ptr<Screen> getScreen();
  void setScreen(std::shared_ptr<Screen> screen);

  void initialize();
  void run();
  static void terminate();

  void update();
  void renderFrame();
  void postUpdate();
  void nextFrame();
};
