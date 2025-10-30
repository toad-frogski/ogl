#pragma once
#include "mesh.hpp"
#include "shader.hpp"
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

  void draw(const glm::mat4& view, const glm::mat4& projection) const {
    shader->use();
    shader->setUniform("model", transform);
    shader->setUniform("view", view);
    shader->setUniform("projection", projection);
    mesh->draw();
  }
};
