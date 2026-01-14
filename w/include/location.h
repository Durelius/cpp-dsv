#pragma once
#include "direction.h"
namespace game {
class Location {
public:
  Location(float x, float y, Direction direction)
      : x(x), y(y), direction(direction) {}
  const Location& get() { return *this; }
  float get_x() const { return x; }
  float get_y() const { return y; }
  Direction get_direction() const { return direction; }
  void out(int& x, int& y) {
    x = this->x;
    y = this->y;
  }

private:
  float x;
  float y;
  Direction direction;
};
} // namespace game
