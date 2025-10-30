#include <memory>
#include "core/engine.hpp"
#include "graphics/model.hpp"
#include "screen/main_screen.hpp"
#include "utils/resource.hpp"

#include "models/cube.cpp"

void sandbox() {
  auto& engine = Engine::getInstance();
  auto screen = std::static_pointer_cast<MainScreen>(engine.getScreen());
  if (!screen) return;

  auto shader = std::make_shared<Shader>(utils::loadResourse("./res/shaders/vertex.glsl").c_str(),
                                         utils::loadResourse("./res/shaders/base_frag.glsl").c_str());

  auto cube = std::make_shared<Cube>(glm::vec3{0.0f, 0.0f, 0.0f}, 0.5f, shader);
  auto dirLight =
      std::make_shared<Light>(Light{LightType::Directional, glm::vec3(0.0f, -3.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f),
                                    glm::vec3(1.0f, 1.0f, 1.0f), 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f});
  auto spotLight = std::make_shared<Light>(
      Light{LightType::Spot, glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(-2.0f, -2.0f, -2.0f), glm::vec3(1.0f, 1.0f, 1.0f),
            1.0f, 1.0f, 0.09f, 0.032f, glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(17.5f))});

  screen->lights.push_back(dirLight);
  screen->lights.push_back(spotLight);
  screen->models.push_back(cube);
}