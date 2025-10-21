#include <functional>
#include <cstdint>
#include <memory>
#include <unordered_map>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "../engine.hpp"
#include "_glfw_window.hpp"
#include "_glfw_input.hpp"

void GLFWInput::pollEvents() {
  currentFrame++;
  glfwPollEvents();
}

bool GLFWInput::pressed(int keycode) const {
  if (keycode < 0 || keycode >= KEYS_BUFFER_SIZE) {
    return false;
  }

  return keys[keycode];
}

bool GLFWInput::jpressed(int keycode) const { return pressed(keycode) && frames[keycode] == currentFrame; }

bool GLFWInput::clicked(int mousecode) const {
  if (mousecode < MOUSE_KEYS_OFFSET || mousecode >= KEYS_BUFFER_SIZE) {
    return false;
  }

  return keys[mousecode];
}

bool GLFWInput::jclicked(int mousecode) const { return clicked(mousecode) && frames[mousecode] == currentFrame; }

CursorState GLFWInput::getCursor() const { return cursor; }

void GLFWInput::toggleCursor() {
  cursor.locked ? glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL)
                : glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  cursor.locked = !cursor.locked;
}

static void key_callback(GLFWwindow* window, int key, int /* scancode */, int action, int /* mode */
) {
  auto* context = static_cast<GLFWWindowContext*>(glfwGetWindowUserPointer(window));
  auto input = context->input;
  if (input == nullptr) return;

  if (key == GLFW_KEY_UNKNOWN) return;

  switch (action) {
    case GLFW_REPEAT:
    case GLFW_PRESS:
      input->onKeyCallback(key, true);
      break;
    case GLFW_RELEASE:
      input->onKeyCallback(key, false);
      break;
  }
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int) {
  auto* context = static_cast<GLFWWindowContext*>(glfwGetWindowUserPointer(window));
  auto input = context->input;
  if (input == nullptr) return;

  input->onMouseCallback(button, action == GLFW_PRESS);
}

static void window_size_callback(GLFWwindow* handle, int width, int height) {
  auto* context = static_cast<GLFWWindowContext*>(glfwGetWindowUserPointer(handle));
  auto window = context->window;
  if (window == nullptr) return;

  auto& settings = Engine::getInstance().getSettings();
  settings.display.width = width;
  settings.display.height = height;
}

static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
  auto* context = static_cast<GLFWWindowContext*>(glfwGetWindowUserPointer(window));
  auto input = context->input;
  if (input == nullptr) return;

  auto cursor = input->getCursor();
  cursor.delta = {xpos - cursor.pos.x, ypos - cursor.pos.y};
  cursor.pos = {xpos, ypos};
  input->setCursor(cursor);
  input->onMouseMoveCallback();
}

std::unique_ptr<Input> Input::initialize(Window* window) {
  auto handle = static_cast<GLFWwindow*>(window->nativeHandle());
  auto inputPtr = std::make_unique<GLFWInput>(handle);

  auto* context = static_cast<GLFWWindowContext*>(glfwGetWindowUserPointer(handle));
  context->input = inputPtr.get();

  glfwSetKeyCallback(handle, key_callback);
  glfwSetMouseButtonCallback(handle, mouse_button_callback);
  glfwSetWindowSizeCallback(handle, window_size_callback);
  glfwSetCursorPosCallback(handle, cursor_pos_callback);

  return std::move(inputPtr);
}

void GLFWInput::onKeyCallback(int key, bool pressed) {
  keys[key] = pressed;
  frames[key] = currentFrame;

  if (!pressed) return;

  const auto& handler = keyHandlers.find(key);
  if (handler != keyHandlers.end()) handler->second();
}

void GLFWInput::onMouseCallback(int key, bool pressed) { onKeyCallback(key + MOUSE_KEYS_OFFSET, pressed); }

void GLFWInput::onMouseMoveCallback() {
  auto cursor = this->getCursor();
  const auto& handler = keyHandlers.find(GLFW_MOUSE_MOVE);
  if (handler != keyHandlers.end()) handler->second();
}

void GLFWInput::addHandler(int key, std::function<void()> handler) {
  if (key < 0 || key >= KEYS_BUFFER_SIZE) return;

  keyHandlers.try_emplace(key, handler);
}

void GLFWInput::setCursor(CursorState cursor) { this->cursor = cursor; }