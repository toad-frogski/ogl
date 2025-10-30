
#include <graphics/model.hpp>

class Cube : public Model {
  float size;

 public:
  Cube(const glm::vec3& position, float size, std::shared_ptr<Shader> shader)
      : Model(Cube::getMesh(size), shader), size(size) {}

 protected:
  std::shared_ptr<Mesh> getMesh(float& size) {
  std::vector<float> vertices = {
      // Pos           // Normal
      // (+Z)
      -size, -size,  size,  0.0f, 0.0f, 1.0f,
      size, -size,  size,  0.0f, 0.0f, 1.0f,
      size,  size,  size,  0.0f, 0.0f, 1.0f,
      -size, -size,  size,  0.0f, 0.0f, 1.0f,
      size,  size,  size,  0.0f, 0.0f, 1.0f,
      -size,  size,  size,  0.0f, 0.0f, 1.0f,

      // (-Z)
      -size, -size, -size,  0.0f, 0.0f, -1.0f,
      -size,  size, -size,  0.0f, 0.0f, -1.0f,
      size,  size, -size,  0.0f, 0.0f, -1.0f,
      -size, -size, -size,  0.0f, 0.0f, -1.0f,
      size,  size, -size,  0.0f, 0.0f, -1.0f,
      size, -size, -size,  0.0f, 0.0f, -1.0f,

      // (-X)
      -size, -size, -size,  -1.0f, 0.0f, 0.0f,
      -size, -size,  size,  -1.0f, 0.0f, 0.0f,
      -size,  size,  size,  -1.0f, 0.0f, 0.0f,
      -size, -size, -size,  -1.0f, 0.0f, 0.0f,
      -size,  size,  size,  -1.0f, 0.0f, 0.0f,
      -size,  size, -size,  -1.0f, 0.0f, 0.0f,

      // (+X)
      size, -size, -size,  1.0f, 0.0f, 0.0f,
      size,  size, -size,  1.0f, 0.0f, 0.0f,
      size,  size,  size,  1.0f, 0.0f, 0.0f,
      size, -size, -size,  1.0f, 0.0f, 0.0f,
      size,  size,  size,  1.0f, 0.0f, 0.0f,
      size, -size,  size,  1.0f, 0.0f, 0.0f,

      // (+Y)
      -size,  size, -size,  0.0f, 1.0f, 0.0f,
      -size,  size,  size,  0.0f, 1.0f, 0.0f,
      size,  size,  size,  0.0f, 1.0f, 0.0f,
      -size,  size, -size,  0.0f, 1.0f, 0.0f,
      size,  size,  size,  0.0f, 1.0f, 0.0f,
      size,  size, -size,  0.0f, 1.0f, 0.0f,

      // (-Y)
      -size, -size, -size,  0.0f, -1.0f, 0.0f,
      size, -size, -size,  0.0f, -1.0f, 0.0f,
      size, -size,  size,  0.0f, -1.0f, 0.0f,
      -size, -size, -size,  0.0f, -1.0f, 0.0f,
      size, -size,  size,  0.0f, -1.0f, 0.0f,
      -size, -size,  size,  0.0f, -1.0f, 0.0f,
  };

    auto mesh = std::make_shared<Mesh>(vertices);

    return mesh;
  }

};
