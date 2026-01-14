#include "tail.h"
#include "Engine.h"
#include "constants_w.h"
#include <cmath>
#include <filesystem>
#include <iostream>
#include <memory>
namespace game {

Tail::Tail(float x, float y, float w, float h, std::string path_to_image,
           std::string id)
    : engine::Sprite(x, y, w, h, path_to_image, id) {}
std::shared_ptr<Tail> Tail::make(Player_ptr player, std::string path_to_image,
                                 std::string id) {
  std::string spec_id = "ta_" + id;

  Direction spawn_direction = !player->get_direction();
  float spawn_x = player->get_frect().x;
  float spawn_y = player->get_frect().y;
  switch (spawn_direction) {
  case Direction::UP:
    spawn_y -= player->get_frect().h;
    break;
  case Direction::DOWN:
    spawn_y += player->get_frect().h;
    break;
  case Direction::LEFT:
    spawn_x -= player->get_frect().w;
    break;
  case Direction::RIGHT:
    spawn_x += player->get_frect().w;
    break;
  }
  auto tail_fill = Tail_Fill::make(spawn_x, spawn_y, player->get_frect().h,
                                   player->get_frect().w, path_to_image, id);
  auto tail = std::shared_ptr<Tail>(
      new Tail(spawn_x, spawn_y, player->get_frect().w, player->get_frect().h,
               path_to_image, spec_id));
  engine::core.add_sprite(tail);
  tail->fill_sprite = tail_fill;
  if (spawn_direction == Direction::UP || spawn_direction == Direction::DOWN) {
    tail->set_sprite_image(constants_w::tail_ver);
    tail_fill->set_sprite_image(constants_w::tail_ver);
  } else {
    tail->set_sprite_image(constants_w::tail_hor);
    tail_fill->set_sprite_image(constants_w::tail_ver);
  }
  tail->set_velocity(5);
  tail->set_target(player);
  return tail;
}
std::shared_ptr<Tail> Tail::make(Tail_ptr last_tail, std::string path_to_image,
                                 std::string id) {

  std::string spec_id = "ta_" + id;
  Direction spawn_direction = !last_tail->get_direction();
  float spawn_x = last_tail->get_frect().x;
  float spawn_y = last_tail->get_frect().y;
  switch (spawn_direction) {
  case Direction::UP:
    spawn_y -= last_tail->get_frect().h;
    break;
  case Direction::DOWN:
    spawn_y += last_tail->get_frect().h;
    break;
  case Direction::LEFT:
    spawn_x -= last_tail->get_frect().w;
    break;
  case Direction::RIGHT:
    spawn_x += last_tail->get_frect().w;
    break;
  }
  auto tail_fill = Tail_Fill::make(spawn_x, spawn_y, last_tail->get_frect().h,
                                   last_tail->get_frect().w, path_to_image, id);
  auto tail = std::shared_ptr<Tail>(
      new Tail(spawn_x, spawn_y, last_tail->get_frect().w,
               last_tail->get_frect().h, path_to_image, spec_id));
  tail->fill_sprite = tail_fill;

  if (spawn_direction == Direction::UP || spawn_direction == Direction::DOWN) {

    tail->set_sprite_image(constants_w::tail_ver);
    tail_fill->set_sprite_image(constants_w::tail_ver);
  } else {
    tail->set_sprite_image(constants_w::tail_hor);
    tail_fill->set_sprite_image(constants_w::tail_ver);
  }
  tail->set_velocity(5);
  last_tail->behind = tail;
  tail->set_target(last_tail);
  int count = 0;

  while (tail->is_intersecting(last_tail)) {
    count++;
    switch (spawn_direction) {
    case Direction::UP:
      spawn_y -= 50;
      break;
    case Direction::DOWN:
      spawn_y += 50;
      break;
    case Direction::LEFT:
      spawn_x -= 50;
      break;
    case Direction::RIGHT:
      spawn_x += 50;
      break;
    default:
      spawn_direction = Direction::RIGHT;
    }

    tail->set_coordinates(spawn_x, spawn_y);

    if (count > 100) {
      std::cerr << "couldn't spawn tail" << std::endl;
      return nullptr;
    }
  }
  engine::core.add_sprite(tail);

  return tail;
}
void Tail::update(std::vector<std::shared_ptr<Sprite>> others) {
  engine::Sprite::update(others);
  if (!get_location_safe())
    return;

  move_towards_target(get_location());
}
void Tail::move_towards_target(const std::shared_ptr<Location> loc) {

  float delta_x = get_frect().x - loc->get_x();
  float delta_y = get_frect().y - loc->get_y();

  float vector = sqrt(pow(delta_x, 2) + pow(delta_y, 2));
  float vector_x = delta_x / vector;
  float vector_y = delta_y / vector;
  float movement_x = get_velocity() * vector_x;
  float movement_y = get_velocity() * vector_y;
  // För nån anledning blev matten omvänd så jag skickar in det
  // negativa värdet för jag orkar inte ta reda på varför...
  move(-movement_x, -movement_y);
}
void Tail::pop_queue() {
  std::shared_ptr<Location> location = coordinate_queue.front();
  coordinate_queue.pop_front();
}
const std::shared_ptr<Location> Tail::get_location() {
  return coordinate_queue.front();
}

void Tail::move(float x, float y) {
  if (!get_location_safe()) {
    return;
  }
  std::shared_ptr<Location> loc = get_location();
  direction = loc->get_direction();
  if (is_intersecting(target))
    return;
  if (behind)
    behind->add_to_queue(get_frect().x, get_frect().y, direction);

  if (direction == Direction::UP || direction == Direction::DOWN) {
    set_sprite_image(constants_w::tail_ver);
    fill_sprite->set_sprite_image(constants_w::tail_ver);
  } else {
    set_sprite_image(constants_w::tail_hor);
    fill_sprite->set_sprite_image(constants_w::tail_hor);
  }

  Component::move(x, y);
  float x_middle = (get_frect().x + target->get_frect().x) / 2;
  float y_middle = (get_frect().y + target->get_frect().y) / 2;
  fill_sprite->set_coordinates(x_middle, y_middle);
  if (reached_coordinates(loc->get_x(), loc->get_y(), get_frect().h,
                          get_frect().w)) {
    pop_queue();
  }
}
bool Tail::reached_coordinates(float dest_x, float dest_y, float dest_w,
                               float dest_h) const {

  float y = get_frect().y;
  float x = get_frect().x;
  float w = get_frect().w;
  float h = get_frect().h;

  float this_x_start = x;
  float this_x_end = x + w;
  float this_y_start = y;
  float this_y_end = y + h;

  float other_x_start = dest_x;
  float other_x_end = dest_x + dest_w;
  float other_y_start = dest_y;
  float other_y_end = dest_y + dest_h;

  if (this_y_end < other_y_start)
    return false;
  if (other_y_end < this_y_start)
    return false;
  if (this_x_end < other_x_start)
    return false;
  if (other_x_end < this_x_start)
    return false;

  return true;
}
} // namespace game
