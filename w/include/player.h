#pragma once
#include "Constants.h"
#include "Sprite.h"
#include "UI_Element.h"
#include "direction.h"
#include <memory>
#include <vector>
namespace game {
class Tail;
constexpr float seconds_to_wait = 0.1;
constexpr float wait_time = seconds_to_wait * constants::fps;
using Tail_ptr = std::shared_ptr<Tail>;
class Player : public engine::Sprite {
public:
  static std::shared_ptr<Player> make(float x, float y, float w, float h,
                                      std::string path_to_image,
                                      std::string base_id);
  ~Player() {}

  void update(std::vector<std::shared_ptr<Sprite>> others);
  void on_action_key_up();
  void on_action_key_down();
  void on_action_key_left();
  void on_action_key_right();
  void on_action_key_space();
  void move(float x, float y);
  Direction get_direction() { return direction; }
  void give_points(int points) { this->points += points; }
  void add_tail();
  void set_game_over() { game_over = true; }
  bool get_game_over() { return game_over; }

protected:
  Player(float x, float y, float w, float h, std::string path_to_image,
         std::string id);

private:
  Direction direction = Direction::RIGHT;
  int direction_change_counter = wait_time;
  int points = 0;
  std::vector<Tail_ptr> tails;
  std::shared_ptr<engine::UI_Element> point_sign;
  bool game_over = false;
};
} // namespace game
