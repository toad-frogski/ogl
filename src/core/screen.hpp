#pragma once

class Screen {
 public:
  virtual void update(double delta) = 0;
  virtual void draw(double delta) = 0;
};
