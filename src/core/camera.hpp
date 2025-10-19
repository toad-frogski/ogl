#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
 public:
  glm::vec3 position;
  glm::vec3 front;
  glm::vec3 right;
  glm::vec3 up;
  const glm::vec3 worldUp;

  float yaw;
  float pitch;

  float fov;
  float aspect;
  float nearPlane;
  float farPlane;

  Camera(glm::vec3 pos = {0.0f, 0.0f, -3.0f}, glm::vec3 target = {0.0f, 0.0f, 0.0f},
         glm::vec3 worldUp = {0.0f, 1.0f, 0.0f}, float fov = 45.0f, float aspect = 4.0f / 3.0f, float nearPlane = 0.1f,
         float farPlane = 100.0f)
      : position(pos),
        worldUp(worldUp),
        up(worldUp),
        fov(fov),
        aspect(aspect),
        nearPlane(nearPlane),
        farPlane(farPlane) {
    front = glm::normalize(target - position);
    right = glm::normalize(glm::cross(front, up));
    pitch = 0.0f;
    yaw = -90.0f;
  }

  glm::mat4 getViewMatrix() const { return glm::lookAt(position, position + front, up); }
  glm::mat4 getProjectionMatrix() const { return glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane); }

  void rotate(float xoffset, float yoffset, float sensivity = 0.1f) {
    xoffset *= sensivity;
    yoffset *= sensivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;
  }

 private:
  void updateCameraVectors() {
    glm::vec3 f;
    f.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    f.y = sin(glm::radians(pitch));
    f.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(f);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
  }
};
