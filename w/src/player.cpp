#include "player.h"
#include "Component.h"
#include "Constants.h"
#include "Engine.h"
#include "Sprite.h"
#include "UI_Element.h"
#include "constants_w.h"
#include "food_spawner.h"
#include "game.h"
#include "tail.h"
#include <exception>
#include <iostream>
#include <memory>
namespace game {
Player::Player(float x, float y, float w, float h, std::string path_to_image,
               std::string id)
    : engine::Sprite(x, y, w, h, path_to_image, id) {}

std::shared_ptr<Player> Player::make(float x, float y, float w, float h,
                                     std::string path_to_image,
                                     std::string id) {
  std::string spec_id = "pl_" + id;
  auto p =
      std::shared_ptr<Player>(new Player(x, y, w, h, path_to_image, spec_id));
  engine::core.add_sprite(p);
  p->point_sign = engine::UI_Element::make(0, x, 50, 50, "0", "point_sign");
  p->point_sign->set_text_color({255, 255, 255, 0});
  p->point_sign->set_color({0, 0, 0, 255});
  p->point_sign->set_coordinates(0, 0);
  p->set_velocity(5);
  return p;
}

void Player::move(float x, float y) {
  bool x_out, y_out;
  engine::core.out_of_bounds(&x_out, &y_out, get_frect().x + x,
                             get_frect().y + y, get_frect().h, get_frect().w);
  if (!x_out && !y_out) {
    Component::move(x, y);
    if (tails.size() > 0)
      tails.front()->add_to_queue(get_frect().x, get_frect().y, direction);
  }
}
void Player::add_tail() {

  Tail_ptr tail;
  if (tails.size() > 0)
    tail = Tail::make(tails.back(), constants_w::orb_png,
                      std::format("{}", tails.size()));
  else {
    auto sprite_ptr = engine::core.get_sprite_by_id(get_id());
    auto player_ptr = std::dynamic_pointer_cast<Player>(sprite_ptr);
    tail = Tail::make(player_ptr, constants_w::orb_png,
                      std::format("{}", tails.size()));
  }
  tails.push_back(tail);
}
void Player::update(std::vector<std::shared_ptr<Sprite>> others) {
  engine::Sprite::update(others);
  if (game_over)
    return;
  if (direction_change_counter < wait_time)
    direction_change_counter++;
  for (auto sp : others) {
    if (sp->get_id() == get_id())
      continue;
    if (!is_intersecting(sp))
      continue;
    if (sp->get_id().substr(0, 2) == "fo") {
      give_points(5);
      engine::core.delete_sprite(sp);
      add_tail();
      point_sign->set_text(std::format("{}", points));
      continue;
    }

    // the first tail doesn't count as it naturally crashes into the player
    if (!game_over && sp->get_id().substr(0, 2) == "ta" &&
        sp->get_id().substr(3, 1) != "0") {
      // game over
      auto game_over =
          engine::UI_Element::make(constants::gScreenWidth * 0.5f - 200,
                                   constants::gScreenHeight * 0.5f - 50, 200,
                                   50, "GAME OVER", "game_over");
      auto restart =
          engine::UI_Element::make(constants::gScreenWidth * 0.5f - 200,
                                   constants::gScreenHeight * 0.5f + 50, 200,
                                   50, "PRESS SPACE TO RESTART", "restart");
      set_game_over();
      Food_Spawner::stop();
      return;
    }
  }
  switch (direction) {
  case Direction::UP:
    move(0, -get_velocity());
    break;
  case Direction::DOWN:
    move(0, get_velocity());
    break;
  case Direction::LEFT:
    move(-get_velocity(), 0);
    break;
  case Direction::RIGHT:
    move(get_velocity(), 0);
    break;
  }
}

void Player::on_action_key_space() {
  if (game_over)
    game::Game::restart();
}
void Player::on_action_key_up() {
  if (direction_change_counter < wait_time)
    return;
  if (direction != Direction::DOWN) { // Can’t reverse
    direction = Direction::UP;
    direction_change_counter = 0;
    set_sprite_image(constants_w::head_up);
  }
}

void Player::on_action_key_down() {
  if (direction_change_counter < wait_time)
    return;
  if (direction != Direction::UP) { // Can’t reverse
    direction = Direction::DOWN;
    direction_change_counter = 0;
    set_sprite_image(constants_w::head_down);
  }
}

void Player::on_action_key_left() {
  if (direction_change_counter < wait_time)
    return;
  if (direction != Direction::RIGHT) { // Can’t reverse
    direction = Direction::LEFT;
    direction_change_counter = 0;
    set_sprite_image(constants_w::head_left);
  }
}

void Player::on_action_key_right() {
  if (direction_change_counter < wait_time)
    return;
  if (direction != Direction::LEFT) { // Can’t reverse
    direction = Direction::RIGHT;
    direction_change_counter = 0;
    set_sprite_image(constants_w::head_right);
  }
}
} // namespace game
