
#include "direction.h"
namespace game {

Direction operator!(Direction d) {
  switch (d) {
  case Direction::UP:
    return Direction::DOWN;
  case Direction::DOWN:
    return Direction::UP;
  case Direction::LEFT:
    return Direction::RIGHT;
  case Direction::RIGHT:
    return Direction::LEFT;
  }

  return d;
}
} // namespace game
