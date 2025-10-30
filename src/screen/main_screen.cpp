#include <glad/gl.h>
#include "main_screen.hpp"

void MainScreen::update(double delta) {}

void MainScreen::draw(double delta) {
  auto camera = Engine::getInstance().getCamera();
  if (!camera) return;

  for (const auto& model : models) {
    model->draw(*camera, lights);
  }
}