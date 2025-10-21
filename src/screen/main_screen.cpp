#include <glad/gl.h>
#include "main_screen.hpp"

void MainScreen::update(double delta) {}

void MainScreen::draw(double delta) {
  auto camera = Engine::getInstance().getCamera();
  glm::mat4 viewProj = camera->getProjectionMatrix() * camera->getViewMatrix();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  for (const auto& model : models) {
    model->draw(viewProj);
  }
}