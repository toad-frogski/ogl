#pragma once

struct DisplaySettings {
  int width = 1280;
  int height = 720;
  bool fullscreen = false;
};

struct EngineSettings {
  DisplaySettings display;
};