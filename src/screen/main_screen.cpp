#include <glad/gl.h>
#include "main_screen.hpp"

void MainScreen::update(double delta) {}

void MainScreen::draw(double delta) {
  auto camera = Engine::getInstance().getCamera();
  glm::mat4 view = camera->getViewMatrix();
  glm::mat4 projection = camera->getProjectionMatrix();

  for (const auto& model : models) {
    model->draw(view, projection);
  }
}