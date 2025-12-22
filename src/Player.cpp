#include "Player.h"
#include "GUIEngine.h"

namespace gui {
typedef std::shared_ptr<Player> player_pointer;

Player::Player(float x, float y, float w, float h, std::string path_to_image,
               std::string id)
    : Sprite(x, y, w, h, path_to_image, id) {
  keystate = SDL_GetKeyboardState(NULL);
}

player_pointer Player::make(float x, float y, float w, float h,
                            std::string path_to_image, std::string id) {
  auto pp = player_pointer(new Player(x, y, w, h, path_to_image, id));
  eng.add_component(pp);
  eng.set_player(pp);
  return pp;
}

void Player::draw() const { Sprite::draw(); }

void Player::player_update() {
  if (keystate[SDL_SCANCODE_W] || keystate[SDL_SCANCODE_UP])
      move(0, -get_velocity());
  if (keystate[SDL_SCANCODE_S] || keystate[SDL_SCANCODE_DOWN])
    move(0, get_velocity());
  if (keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_LEFT])
    move(-get_velocity(), 0);
  if (keystate[SDL_SCANCODE_D] || keystate[SDL_SCANCODE_RIGHT])
    move(get_velocity(), 0);
}

} // namespace gui
