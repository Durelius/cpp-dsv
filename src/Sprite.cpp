#include "Sprite.h"
#include "Component.h"
#include "GUIEngine.h"
#include <cmath>
#include <memory>
namespace gui {
typedef std::shared_ptr<Sprite> sprite_pointer;

Sprite::Sprite(float x, float y, float w, float h, std::string path_to_image,
               std::string id)
    : Component(x, y, w, h, id) {

  sprite_image = IMG_LoadTexture(eng.get_renderer(), path_to_image.c_str());
}

// sprite_pointer Sprite::make(float x, float y, float w, float h,
//                             std::string path_to_image, std::string base_id,
//                             bool non_colliding_spawn_point) {
//   std::string spec_id = "sp_" + base_id;
//
//   auto sp = sprite_pointer(new Sprite(x, y, w, h, path_to_image, spec_id));
//
//   eng.add_sprite(sp);
//   sp->non_colliding_spawn_point = non_colliding_spawn_point;
//
//   return sp;
// }

void Sprite::draw() const {
  SDL_RenderTexture(eng.get_renderer(), sprite_image, NULL, &get_rect());
}
// returns false if we move back the sprite
// finns säkert ett bättre sätt att göra detta på, snabb fix! i och med att vi
// hämtar get_rect så många gånger..
bool Sprite::move(int paramX, int paramY) {
  int initialX = get_rect().x;
  int initialY = get_rect().y;
  set_coordinates(initialX + paramX, initialY + paramY);
  border_detection();

  if (eng.is_colliding(*this)) {
    return false;
    set_coordinates(initialX, initialY);
  }
  return true;
}

bool Sprite::border_detection() {
  bool outside_bounds = false;
  int x = get_rect().x;
  int y = get_rect().y;
  int w = get_rect().w;
  int h = get_rect().h;

  if (x < 0) {
    outside_bounds = true;
    x = 0;
  }
  if (y < 0) {
    outside_bounds = true;
    y = 0;
  }

  int window_width;
  int window_height;

  SDL_GetWindowSize(eng.get_window(), &window_width, &window_height);
  if (x > window_width - w) {
    outside_bounds = true;
    x = window_width - w;
  }
  if (y > window_height - h) {
    outside_bounds = true;
    y = window_height - h;
  }

  set_coordinates(x, y);
  return outside_bounds;
}
// return false if the target was stopped in its tracks
bool Sprite::move_towards_target(int target_x, int target_y) {

  float delta_x = get_rect().x - target_x;
  float delta_y = get_rect().y - target_y;

  float vector = sqrt(pow(delta_x, 2) + pow(delta_y, 2));
  float vector_x = delta_x / vector;
  float vector_y = delta_y / vector;

  int movement_x = get_velocity() * vector_x;
  int movement_y = get_velocity() * vector_y;

  // För nån anledning blev matten omvänd så jag skickar in det
  // negativa värdet för jag orkar inte ta reda på varför...
  return move(-movement_x, -movement_y);
}

bool Sprite::is_colliding(const Sprite& other) const {
  if (!can_collide() || !other.can_collide())
    return false;

  return is_overlapping(other);
}
bool Sprite::is_overlapping(const Sprite& other) const {

  int y = other.get_rect().y;
  int x = other.get_rect().x;
  int w = other.get_rect().w;
  int h = other.get_rect().h;
  return reached_coordinates(x, y, w, h);
}
bool Sprite::reached_coordinates(int dest_x, int dest_y, int dest_w,
                                 int dest_h) const {

  int y = get_rect().y;
  int x = get_rect().x;
  int w = get_rect().w;
  int h = get_rect().h;

  int this_x_start = x;
  int this_x_end = x + w;
  int this_y_start = y;
  int this_y_end = y + h;

  int other_x_start = dest_x;
  int other_x_end = dest_x + dest_w;
  int other_y_start = dest_y;
  int other_y_end = dest_y + dest_h;

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

void Sprite::do_track_target() {
  if (is_overlapping(*track_target))
    return;
  move_towards_target(track_target->get_rect().x, track_target->get_rect().y);
}
void Sprite::set_velocity(float v) { velocity = v; }

} // namespace gui
