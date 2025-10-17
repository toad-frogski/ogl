#pragma once

#include <memory>
#include <stdexcept>

#include "settings.hpp"
#include "time.hpp"

class Window;

class Engine {
  std::unique_ptr<Window> window;
  Time time;
  EngineSettings settings;

 public:
  Engine();
  ~Engine();

  static Engine& getInstance();

  Time& getTime();

  EngineSettings& getSettings();

  void initialize();
  void run();
  static void terminate();
};