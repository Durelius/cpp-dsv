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
    move(0, -5);
  if (keystate[SDL_SCANCODE_S] || keystate[SDL_SCANCODE_DOWN])
    move(0, 5);
  if (keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_LEFT])
    move(-5, 0);
  if (keystate[SDL_SCANCODE_D] || keystate[SDL_SCANCODE_RIGHT])
    move(5, 0);
}

// void Player::on_key_down(const SDL_Event& event) {
//   switch (event.key.scancode) {
//   case SDL_SCANCODE_W:
//     move(0, -10);
//     break;
//   case SDL_SCANCODE_A:
//     move(-10, 0);
//     break;
//   case SDL_SCANCODE_S:
//     move(0, 10);
//     break;
//   case SDL_SCANCODE_D:
//     move(10, 0);
//     break;
//   default:
//     break;
//   }
// }

} // namespace gui
