#include "food_spawner.h"
#include "Constants.h"
#include "Engine.h"
#include "random.h"
#include <chrono>
#include <iostream>
namespace game {

int Food_Spawner::id_index = 0;
int Food_Spawner::frame_counter = 0;
double Food_Spawner::dynamic_spawn_time = 0;
bool Food_Spawner::on = false;
constexpr double decrement = 0.3;
constexpr int initial_seconds_to_wait = 4;
constexpr int spawn_time = constants::fps * initial_seconds_to_wait;
void Food_Spawner::spawn() {
  if (!is_on())
    return;
  if (dynamic_spawn_time == 0)
    dynamic_spawn_time = initial_seconds_to_wait;
  else
    dynamic_spawn_time -= decrement;
  if (++Food_Spawner::frame_counter == spawn_time) {
    float x = Random::number_between(0, constants::gScreenWidth);
    float y = Random::number_between(0, constants::gScreenHeight);
    auto food_ptr = Food::make(x, y, 20, 20, constants_w::orb_png,
                               Food_Spawner::get_and_increase_id_index());
    frame_counter = 0;
  }
}
void Food_Spawner::clear() {
  id_index = 0;
  frame_counter = 0;
  dynamic_spawn_time = 0;
}
// void Food_Spawner::remove(std::string id) {}

} // namespace game
