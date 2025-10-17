#include <GLFW/glfw3.h>

#include "../window.hpp"

class GLFWWindow : public Window {
  GLFWwindow* window;

 public:
  GLFWWindow(GLFWwindow* window, int width, int height);
  ~GLFWWindow();
  double time() override;
  void swapBuffers() override;
};

GLFWWindow::GLFWWindow(GLFWwindow* window, int width, int height) : Window({width, height}), window(window) {}
GLFWWindow::~GLFWWindow() { glfwTerminate(); }

double GLFWWindow::time() { return glfwGetTime(); }

std::unique_ptr<Window> Window::initialize(DisplaySettings* settings, std::string title) {
  int width = settings->width;
  int height = settings->height;

  if (glfwInit() == GLFW_FALSE) {
    return nullptr;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

  GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (window == nullptr) {
    return nullptr;
  }

  glfwMakeContextCurrent(window);
  glViewport(0, 0, width, height);
  glClearColor(0.0f, 0.0f, 0.0f, 1);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glfwSwapInterval(1);

  glm::vec2 scale;
  glfwGetMonitorContentScale(glfwGetPrimaryMonitor(), &scale.x, &scale.y);

  auto windowPtr = std::make_unique<GLFWWindow>(window, width, height);
  glfwSetWindowUserPointer(window, windowPtr.get());

  return std::move(windowPtr);
}

void GLFWWindow::swapBuffers() { glfwSwapBuffers(window); }
