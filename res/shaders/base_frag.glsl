#version 330 core

struct Light {
  int type;
  vec3 position;
  vec3 direction;
  vec3 color;
  float intensity;
  float constant;
  float linear;
  float quadratic;
  float cutoff;
  float outerCutoff;
};

#define MAX_LIGHTS 8
uniform vec3 cameraPos;
uniform int numLights;
uniform Light lights[MAX_LIGHTS];

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

void main() {
  vec3 norm = normalize(Normal);
  vec3 result = 0.2 * vec3(1.0);

  for (int i = 0; i < numLights; i++) {
    vec3 lightDir;
    float attenuation = 1.0;

    if (lights[i].type == 0) {
      // directional
      lightDir = normalize(-lights[i].direction);
    } else {
      // point or spot
      lightDir = normalize(lights[i].position - FragPos);
      float distance = length(lights[i].position - FragPos);
      attenuation = 1.0 / (lights[i].constant + lights[i].linear * distance + lights[i].quadratic * distance * distance);
    }

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lights[i].color * lights[i].intensity * attenuation;

    // spot light
    if (lights[i].type == 2) {
      float theta = dot(lightDir, normalize(-lights[i].direction));
      float epsilon = lights[i].cutoff - lights[i].outerCutoff;
      float intensity = clamp((theta - lights[i].outerCutoff) / epsilon, 0.0, 1.0);
      diffuse *= intensity;
    }

    result += diffuse;
  }

  FragColor = vec4(result, 1.0);
}
