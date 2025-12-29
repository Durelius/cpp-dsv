#include "Sprite.h"
#include "Component.h"
#include "Engine.h"
#include <cmath>
#include <memory>
namespace engine {
typedef std::shared_ptr<Sprite> sprite_pointer;

Sprite::Sprite(float x, float y, float w, float h, std::string path_to_image,
               std::string id)
    : Component(x, y, w, h, id) {

  sprite_image = IMG_LoadTexture(core.get_renderer(), path_to_image.c_str());
}

void Sprite::draw() const {
  SDL_RenderTexture(core.get_renderer(), sprite_image, NULL, &get_frect());
}
void Sprite::move(int paramX, int paramY) {
  set_coordinates(get_frect().x + paramX, get_frect().y + paramY);
}
bool Sprite::is_intersecting(Sprite_ptr other) {
  if (!other)
    return false;

  return SDL_HasRectIntersectionFloat(&this->get_frect(), &other->get_frect());
}
void Sprite::set_velocity(float v) { velocity = v; }

} // namespace engine
