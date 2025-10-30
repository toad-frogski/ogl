#pragma once
#include "mesh.hpp"
#include "shader.hpp"
#include "light.hpp"
#include "core/camera.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

class Model {
  std::shared_ptr<Mesh> mesh;
  std::shared_ptr<Shader> shader;
  glm::mat4 transform{1.0f};

 public:
  Model(std::shared_ptr<Mesh> m, std::shared_ptr<Shader> s) : mesh(std::move(m)), shader(std::move(s)) {}

  void setTransform(const glm::mat4& t) { transform = t; }

  void draw(Camera& camera, const std::vector<std::shared_ptr<Light>>& lights) const {
    auto view = camera.getViewMatrix();
    auto projection = camera.getProjectionMatrix();

    shader->use();
    shader->setUniform("model", transform);
    shader->setUniform("view", view);
    shader->setUniform("projection", projection);
    shader->setUniform("cameraPos", camera.position);
    shader->setUniform("numLights", static_cast<int>(lights.size()));

    for (size_t i = 0; i < lights.size(); ++i) {
      const auto& light = lights[i];
      if (!light) continue;

      std::string base = "lights[" + std::to_string(i) + "]";
      shader->setUniform(base + ".type", static_cast<int>(light->type));
      shader->setUniform(base + ".position", light->position);
      shader->setUniform(base + ".direction", light->direction);
      shader->setUniform(base + ".color", light->color);
      shader->setUniform(base + ".intensity", light->intensity);
      shader->setUniform(base + ".constant", light->constant);
      shader->setUniform(base + ".linear", light->linear);
      shader->setUniform(base + ".quadratic", light->quadratic);
      shader->setUniform(base + ".cutoff", light->cutoff);
      shader->setUniform(base + ".outerCutoff", light->outerCutoff);
    }

    mesh->draw();
  }
};
