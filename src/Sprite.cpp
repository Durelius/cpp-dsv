#include "Sprite.h"
#include "Component.h"
#include "GUIEngine.h"
#include <cmath>

namespace gui {
typedef std::shared_ptr<Sprite> sprite_pointer;

Sprite::Sprite(float x, float y, float w, float h, std::string path_to_image,
               std::string id)
    : Component(x, y, w, h, id) {
  sprite_image = IMG_LoadTexture(eng.get_renderer(), path_to_image.c_str());
}

sprite_pointer Sprite::make(float x, float y, float w, float h,
                            std::string path_to_image, std::string id) {
  auto sp = sprite_pointer(new Sprite(x, y, w, h, path_to_image, id));
  eng.add_component(sp);
  return sp;
}

void Sprite::draw() const {
  SDL_RenderTexture(eng.get_renderer(), sprite_image, NULL, &get_rect());
}

void Sprite::track_target(sprite_pointer other) {
  float delta_x = get_rect().x - other->get_rect().x;
  float delta_y = get_rect().y - other->get_rect().y;

  float vector = sqrt(pow(delta_x, 2) + pow(delta_y, 2));
  float vector_x = delta_x / vector;
  float vector_y = delta_y / vector;

  int movement_x = 5 * vector_x;
  int movement_y = 5 * vector_y;

  // För nån anledning blev matten omvänd så jag skickar in det
  // negativa värdet för jag orkar inte ta reda på varför...
  move(-movement_x, -movement_y);
}

void Sprite::set_velocity(float v) {
  velocity = v;
}

} // namespace gui
