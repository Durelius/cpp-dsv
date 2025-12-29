#include "Sprite.h"
#include "Component.h"
#include "Engine.h"
#include <memory>
namespace engine {
typedef std::shared_ptr<Sprite> sprite_pointer;

Sprite::Sprite(float x, float y, float w, float h, std::string path_to_image,
               std::string id)
    : Component(x, y, w, h, id) {

  sprite_image = IMG_LoadTexture(core.get_renderer(), path_to_image.c_str());
  keystate = SDL_GetKeyboardState(NULL);
}
void Sprite::update(std::vector<Sprite_ptr> others) {
  if (keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_A])
    on_action_key_left();
  if (keystate[SDL_SCANCODE_RIGHT] || keystate[SDL_SCANCODE_D])
    on_action_key_right();
  if (keystate[SDL_SCANCODE_UP] || keystate[SDL_SCANCODE_W])
    on_action_key_up();
  if (keystate[SDL_SCANCODE_DOWN] || keystate[SDL_SCANCODE_S])
    on_action_key_down();
  if (keystate[SDL_SCANCODE_SPACE])
    on_action_key_space();
}

void Sprite::draw() const {
  SDL_RenderTexture(core.get_renderer(), sprite_image, NULL, &get_frect());
}
bool Sprite::is_intersecting(Sprite_ptr other) {
  if (!other)
    return false;

  return SDL_HasRectIntersectionFloat(&this->get_frect(), &other->get_frect());
}
void Sprite::set_velocity(float v) { velocity = v; }

} // namespace engine
