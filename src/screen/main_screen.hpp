#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "graphics/model.hpp"
#include "core/engine.hpp"

class MainScreen : public Screen {
 public:
  std::vector<std::shared_ptr<Model>> models;
  std::vector<std::shared_ptr<Light>> lights;
  void update(double delta) override;
  void draw(double delta) override;
};