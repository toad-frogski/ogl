#pragma once

#include <memory>
#include <stdexcept>

#include "settings.hpp"
#include "time.hpp"

class Window;
class Input;

class Engine {
  std::unique_ptr<Window> window;
  std::unique_ptr<Input> input;
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

  void initialize();
  void run();
  static void terminate();

  void update();
  void renderFrame();
  void postUpdate();
  void nextFrame();
};
