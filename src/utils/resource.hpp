#pragma once

#include <string>
#include <fstream>
#include <sstream>

namespace utils {
inline std::string loadResourse(const std::string& path) {
  std::ifstream file(path);
  if (!file.is_open()) throw std::runtime_error("Failed to open resource: " + path);

  std::stringstream buffer;
  buffer << file.rdbuf();

  return buffer.str();
}
}  // namespace utils