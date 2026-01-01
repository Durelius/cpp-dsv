#include "Sprite.h"
#include "Component.h"
#include "Engine.h"
#include <SDL3/SDL_video.h>
#include <memory>
namespace engine {
typedef std::shared_ptr<Sprite> Sprite_ptr;

Sprite::Sprite(float x, float y, float w, float h, std::string path_to_image,
               std::string id)
    : Component(x, y, w, h, id) {
  sprite_image = IMG_LoadTexture(core.get_renderer(), path_to_image.c_str());
  keystate = SDL_GetKeyboardState(NULL);
}

Sprite_ptr Sprite::make(float x, float y, float w, float h,
                        std::string path_to_image, std::string base_id) {
  std::string spec_id = "sp_" + base_id;
  auto sp = Sprite_ptr(new Sprite(x, y, w, h, path_to_image, spec_id));
  core.add_sprite(sp);
  return sp;
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
void Sprite::out_of_bounds(bool* x, bool* y) {

  int win_height, win_width;
  SDL_GetWindowSize(core.get_window(), &win_width, &win_height);
  if (x)
    *x = get_frect().x < 0 || get_frect().x > win_width - get_frect().w;
  if (y)
    *y = get_frect().y < 0 || get_frect().y > win_height - get_frect().h;
}

bool Sprite::is_intersecting(Sprite_ptr other) {
  if (!other)
    return false;

  return SDL_HasRectIntersectionFloat(&this->get_frect(), &other->get_frect());
}

void Sprite::set_velocity(float v) { velocity = v; }

} // namespace engine
