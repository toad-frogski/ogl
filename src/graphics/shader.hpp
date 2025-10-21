#pragma once

#include <glad/gl.h>
#include <string>
#include <stdexcept>

class Shader {
  GLuint program{};

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
};
