

#pragma once
#include "Sprite.h"
#include "constants_w.h"
#include "food.h"
#include "player.h"
#include <format>
#include <memory>
namespace game {
class Food_Spawner {
public:
  static void start() { on = true; }
  static void stop() { on = false; }
  static bool is_on() { return on; }
  static void spawn();
  static void remove(std::string id);
  static void clear();
  ~Food_Spawner() {}

protected:
  Food_Spawner();

private:
  static std::string get_and_increase_id_index() {
    id_index++;
    return std::format("{}", id_index);
  }
  static int id_index;
  static int frame_counter;
  static bool on;
  static double dynamic_spawn_time;
};
} // namespace game
