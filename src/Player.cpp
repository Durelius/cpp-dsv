#include "Player.h"
#include "GUIEngine.h"
#include "projectile.h"
#include <SDL3/SDL_scancode.h>
#include <iostream>
namespace gui {
typedef std::shared_ptr<Player> player_pointer;

Player::Player(float x, float y, float w, float h, std::string path_to_image,
               std::string id)
    : Sprite(x, y, w, h, path_to_image, id) {
  keystate = SDL_GetKeyboardState(NULL);
}

player_pointer Player::make(float x, float y, float w, float h,
                            std::string path_to_image, std::string base_id) {
  std::string spec_id = "pl_" + base_id;
  auto pp = player_pointer(new Player(x, y, w, h, path_to_image, spec_id));
  pp->set_health(100);
  eng.add_sprite(pp);
  eng.set_player(pp);
  return pp;
}

bool Player::take_damage(int damage) {
  set_health(*health - damage);
  if (*health <= 0)
    return true;
  return false;
}
void Player::draw() const { Sprite::draw(); }

void Player::update() {
  if (keystate[SDL_SCANCODE_W] || keystate[SDL_SCANCODE_UP])
    move(0, -get_velocity());
  if (keystate[SDL_SCANCODE_S] || keystate[SDL_SCANCODE_DOWN])
    move(0, get_velocity());
  if (keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_LEFT])
    move(-get_velocity(), 0);
  if (keystate[SDL_SCANCODE_D] || keystate[SDL_SCANCODE_RIGHT])
    move(get_velocity(), 0);
  if (keystate[SDL_SCANCODE_SPACE]) {

    decr_cooldown_counter();
    if (get_projectile_cooldown() > 0 && get_cooldown_counter() <= 0) {
      auto proj =
          Projectile::make(10, 10, "resources/images/projectile.png",
                           "updateshoot", eng.get_player(), 10, Projectile::UP);
      set_cooldown_counter();
    }
  }
}

} // namespace gui
