#pragma once
#include <glm/glm.hpp>

enum class LightType { Directional, Point, Spot };

struct Light {
  LightType type;
  glm::vec3 position;
  glm::vec3 direction;
  glm::vec3 color;
  float intensity;

  float constant = 1.0f;
  float linear = 0.09f;
  float quadratic = 0.032f;

  float cutoff = glm::cos(glm::radians(12.5f));
  float outerCutoff = glm::cos(glm::radians(17.5f));
};
