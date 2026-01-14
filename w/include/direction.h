#pragma once
namespace game {

enum class Direction { UP, DOWN, RIGHT, LEFT };
Direction operator!(Direction d);
} // namespace game
