#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <string>

#include "settings.hpp"

class Window {
 public:
  Window(glm::ivec2 size) : size(std::move(size)) {}
  virtual ~Window() = default;
  virtual void swapBuffers() = 0;
  virtual double time() = 0;

  static std::unique_ptr<Window> initialize(DisplaySettings* settings, std::string title);

 protected:
  glm::ivec2 size;
};