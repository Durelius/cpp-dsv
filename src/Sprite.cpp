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
  auto sp = sprite_pointer(new Sprite(x, y, w, h, path_to_image, id));
  eng.add_component(sp);
  sp->non_colliding_spawn_point = non_colliding_spawn_point;

  return sp;
}

void Sprite::draw() const {
  SDL_RenderTexture(eng.get_renderer(), sprite_image, NULL, &get_rect());
}
void Sprite::move(int x, int y) {
  int currentX = this->get_rect().x;
  int currentY = this->get_rect().y;
  Component::move(x, y);
  if (eng.is_colliding(*this))
    Component::set_coordinates(currentX, currentY);
}

void Sprite::set_velocity(float v) { velocity = v; }

} // namespace gui
