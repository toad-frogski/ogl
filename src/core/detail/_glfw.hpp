#pragma once

class GLFWInput;
class GLFWWindow;

struct GLFWWindowContext {
  GLFWInput* input = nullptr;
  GLFWWindow* window = nullptr;
};
