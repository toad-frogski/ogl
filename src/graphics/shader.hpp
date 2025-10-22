#pragma once

#include <glad/gl.h>
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include <stdexcept>

class Shader {
  GLuint program{};
  std::unordered_map<std::string, GLint> uniforms;

  static GLuint compile(GLenum type, const char* src) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      char info[512];
      glGetShaderInfoLog(shader, 512, nullptr, info);
      throw std::runtime_error(std::string("Shader compile error: ") + info);
    }

    return shader;
  }

 public:
  Shader(const char* vertSrc, const char* fragSrc) {
    GLuint vs = compile(GL_VERTEX_SHADER, vertSrc);
    GLuint fs = compile(GL_FRAGMENT_SHADER, fragSrc);
    program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glDeleteShader(vs);
    glDeleteShader(fs);
  }

  ~Shader() {
    if (program) glDeleteProgram(program);
  }

  GLuint getProgram() { return program; }

  void use() const { glUseProgram(program); }

  GLint getUniformLocation(const std::string& name) {
    auto it = uniforms.find(name);
    if (it != uniforms.end()) return it->second;

    GLint loc = glGetUniformLocation(program, name.c_str());
    uniforms.emplace(name, loc);
    return loc;
  }

  void setUniform(const std::string& name, const glm::mat4& m) {
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &m[0][0]);
  }

  void setUniform(const std::string& name, float value) { glUniform1f(getUniformLocation(name), value); }
};
