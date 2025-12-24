#include "Sprite.h"
#include "Component.h"
#include "GUIEngine.h"
#include <iostream>

namespace gui {
typedef std::shared_ptr<Sprite> sprite_pointer;

Sprite::Sprite(float x, float y, float w, float h, std::string path_to_image,
               std::string id)
    : Component(x, y, w, h, id) {

  sprite_image = IMG_LoadTexture(eng.get_renderer(), path_to_image.c_str());
}

sprite_pointer Sprite::make(float x, float y, float w, float h,
                            std::string path_to_image, std::string id,
                            bool non_colliding_spawn_point) {
  id = "sp_" + id;
  auto sp = sprite_pointer(new Sprite(x, y, w, h, path_to_image, id));

  eng.add_sprite(sp);
  sp->non_colliding_spawn_point = non_colliding_spawn_point;

  return sp;
}

void Sprite::draw() const {
  SDL_RenderTexture(eng.get_renderer(), sprite_image, NULL, &get_rect());
}

// finns säkert ett bättre sätt att göra detta på, snabb fix! i och med att vi
// hämtar get_rect så många gånger..
void Sprite::move(int paramX, int paramY) {
  int initialX = this->get_rect().x;
  int initialY = this->get_rect().y;
  set_coordinates(initialX + paramX, initialY + paramY);
  border_detection();
  if (eng.is_colliding(*this))
    set_coordinates(initialX, initialY);
}

void Sprite::border_detection() {

  int x = this->get_rect().x;
  int y = this->get_rect().y;
  int w = this->get_rect().w;
  int h = this->get_rect().h;

  if (x < 0)
    x = 0;
  if (y < 0)
    y = 0;

  int window_width;
  int window_height;

  SDL_GetWindowSize(eng.get_window(), &window_width, &window_height);
  if (x > window_width - w)
    x = window_width - w;
  if (y > window_height - h)
    y = window_height - h;

  set_coordinates(x, y);
}
bool Sprite::is_colliding(const Sprite& other) const {
  if (!can_collide() || !other.can_collide())
    return false;
  int x = this->get_rect().x;
  int y = this->get_rect().y;
  int w = this->get_rect().w;
  int h = this->get_rect().h;

  int this_x_start = x;
  int this_x_end = x + w;
  int this_y_start = y;
  int this_y_end = y + h;

  int other_x_start = other.get_rect().x;
  int other_x_end = other.get_rect().x + other.get_rect().w;
  int other_y_start = other.get_rect().y;
  int other_y_end = other.get_rect().y + other.get_rect().h;

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

void Sprite::set_velocity(float v) { velocity = v; }

} // namespace gui
