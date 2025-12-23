#include "Sprite.h"
#include "Component.h"
#include "GUIEngine.h"

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
  // SDL_SetRenderDrawColor(eng.get_renderer(), 255, 0, 0, 255);
  // SDL_RenderFillRect(eng.get_renderer(), &get_rect());
  SDL_RenderTexture(eng.get_renderer(), sprite_image, NULL, &get_rect());
}

void Sprite::set_velocity(int v) {
  velocity = v;
}

} // namespace gui
