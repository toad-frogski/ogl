#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "_glfw_window.hpp"

GLFWWindow::GLFWWindow(GLFWwindow* window, int width, int height) : Window({width, height}), window(window) {
  ctx.window = this;
  glfwSetWindowUserPointer(window, &ctx);
}

GLFWWindow::~GLFWWindow() { glfwTerminate(); }

double GLFWWindow::time() { return glfwGetTime(); }

GLFWWindowContext* GLFWWindow::context() { return &ctx; }

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

  if (!gladLoadGL(glfwGetProcAddress)) {
    return nullptr;
  }

  glViewport(0, 0, width, height);
  glClearColor(0.0f, 0.0f, 0.0f, 1);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glfwSwapInterval(1);

  glm::vec2 scale;
  glfwGetMonitorContentScale(glfwGetPrimaryMonitor(), &scale.x, &scale.y);

  auto windowPtr = std::make_unique<GLFWWindow>(window, width, height);

  return std::move(windowPtr);
}

void GLFWWindow::swapBuffers() { glfwSwapBuffers(window); }

bool GLFWWindow::isShouldClose() const { return glfwWindowShouldClose(window); }

void GLFWWindow::setShouldClose(bool flag) { glfwSetWindowShouldClose(window, flag); }

void* GLFWWindow::nativeHandle() const { return static_cast<void*>(window); }

void GLFWWindow::setSize(int width, int height) { glViewport(0, 0, width, height); }

void GLFWWindow::beforeRender() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
