#pragma once

#include "../window.hpp"

class GLFWInput;

struct GLFWWindowContext {
  GLFWInput* input = nullptr;
  class GLFWWindow* window = nullptr;
};

class GLFWWindow : public Window {
  GLFWwindow* window;
  GLFWWindowContext ctx;

 public:
  GLFWWindow(GLFWwindow* window, int width, int height);
  ~GLFWWindow();
  double time() override;
  void swapBuffers() override;
  void beforeRender() override;
  bool isShouldClose() const override;
  void setShouldClose(bool flag) override;
  void setSize(int width, int height) override;
  void* nativeHandle() const override;

  GLFWWindowContext* context();
};