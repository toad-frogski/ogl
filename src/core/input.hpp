#pragma once

#include <glm/vec2.hpp>

#include "window.hpp"

struct CursorState {
  bool locked = false;
  glm::vec2 pos{};
};

class Input {
 public:
  virtual ~Input() = default;

  static std::unique_ptr<Input> initialize(Window* window);

  virtual void pollEvents() = 0;

  virtual bool pressed(int keycode) const = 0;
  virtual bool jpressed(int keycode) const = 0;
  virtual bool clicked(int mousecode) const = 0;
  virtual bool jclicked(int mousecode) const = 0;

  virtual void toggleCursor() = 0;

  virtual CursorState getCursor() const = 0;
  virtual void setCursor(CursorState cursor) = 0;

  virtual void addHandler(int key, std::function<void()> handler) = 0;
};
