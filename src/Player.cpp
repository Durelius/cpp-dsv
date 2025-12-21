#include "Player.h"
#include "Component.h"
#include "GUIEngine.h"
#include "Label.h"
#include "Sprite.h"
#include <iostream>

namespace gui
{
  typedef std::shared_ptr<Player> player_pointer;

  Player::Player(float x, float y, float w, float h, std::string path_to_image, std::string id)
      : Sprite(x, y, w, h, path_to_image, id) {}

  player_pointer Player::make(float x, float y, float w, float h,
                              std::string path_to_image, std::string id)
  {
    return player_pointer(new Player(x, y, w, h, path_to_image, id));
  }

  void Player::draw() const { Sprite::draw(); }

  void Player::onKeyDown(const SDL_Event &event)
  {
    switch (event.key.scancode)
    {
    case SDL_SCANCODE_W:
      move(0, -10);
      break;
    case SDL_SCANCODE_A:
      move(-10, 0);
      break;
    case SDL_SCANCODE_S:
      move(0, 10);
      break;
    case SDL_SCANCODE_D:
      move(10, 0);
      break;
    default:
      break;
    }
  }

} // namespace gui
