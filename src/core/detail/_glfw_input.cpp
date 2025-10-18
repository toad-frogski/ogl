#include <functional>
#include <cstdint>
#include <memory>
#include <unordered_map>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "../input.hpp"
#include "../engine.hpp"
#include "_glfw_window.hpp"

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
  void toggleCursor() override;

  void onKeyCallback(int key, bool pressed);
  void onMouseCallback(int key, bool pressed);

  void addHandler(int key, std::function<void()> handler) override;
};

void GLFWInput::pollEvents() {
  cursor.delta = {0, 0};
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

  if (width && height) {
    window->setSize(width, height);
  }
}

std::unique_ptr<Input> Input::initialize(Window* window) {
  auto handle = static_cast<GLFWwindow*>(window->nativeHandle());
  auto inputPtr = std::make_unique<GLFWInput>(handle);

  auto* context = static_cast<GLFWWindowContext*>(glfwGetWindowUserPointer(handle));
  context->input = inputPtr.get();

  glfwSetKeyCallback(handle, key_callback);
  glfwSetMouseButtonCallback(handle, mouse_button_callback);
  glfwSetWindowSizeCallback(handle, window_size_callback);

  return std::move(inputPtr);
}

void GLFWInput::onKeyCallback(int key, bool pressed) {
  bool isPrev = keys[key];
  keys[key] = pressed;
  frames[key] = currentFrame;

  if (!pressed) return;

  if (!isPrev) {
    const auto& handler = keyHandlers.find(key);
    if (handler != keyHandlers.end()) handler->second();
  }
}

void GLFWInput::onMouseCallback(int key, bool pressed) { onKeyCallback(key + MOUSE_KEYS_OFFSET, pressed); }

void GLFWInput::addHandler(int key, std::function<void()> handler) {
  if (key < 0 || key >= KEYS_BUFFER_SIZE) return;

  keyHandlers.try_emplace(key, handler);
}
