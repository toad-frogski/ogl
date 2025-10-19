#include <glad/gl.h>

#include <iostream>
#include <vector>
#include <memory>
#include "core/screen.hpp"
#include "core/model.hpp"
#include "core/engine.hpp"

class MainScreen : public Screen {
 public:
  std::vector<std::shared_ptr<Model>> models;
  void update(double delta) override;
  void draw(double delta) override;
};

void MainScreen::update(double delta) {}

void MainScreen::draw(double delta) {
  auto camera = Engine::getInstance().getCamera();
  glm::mat4 viewProj = camera->getProjectionMatrix() * camera->getViewMatrix();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  for (const auto& model : models) {
    model->draw(viewProj);
  }
  fprintf(stderr, "[camera] position (%f, %f, %f)\n", camera->position.x, camera->position.y, camera->position.z);
  fprintf(stderr, "[camera] yaw %f pitch %f\n", camera->yaw, camera->pitch);
}