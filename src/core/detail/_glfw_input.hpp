#pragma once

#include "../input.hpp"


#ifndef GLFW_MOUSE_MOVE
#define GLFW_MOUSE_MOVE 10
#endif

inline constexpr short KEYS_BUFFER_SIZE = 1036;
inline constexpr short MOUSE_KEYS_OFFSET = 1024;

class GLFWInput : public Input {
  GLFWwindow* window;
  CursorState cursor;

 public:
  GLFWInput(GLFWwindow* window) : window(window) {}

  uint32_t currentFrame = 0;
  uint frames[KEYS_BUFFER_SIZE]{};
  bool keys[KEYS_BUFFER_SIZE]{};
  std::unordered_map<int, std::function<void()>> keyHandlers;

  void pollEvents() override;
  bool pressed(int keycode) const override;
  bool jpressed(int keycode) const override;
  bool clicked(int mousecode) const override;
  bool jclicked(int mousecode) const override;
  CursorState getCursor() const override;
  void setCursor(CursorState cursor) override;
  void toggleCursor() override;

  void onKeyCallback(int key, bool pressed);
  void onMouseCallback(int key, bool pressed);
  void onMouseMoveCallback();

  void addHandler(int key, std::function<void()> handler) override;
};
