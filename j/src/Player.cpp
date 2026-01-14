#include "Player.h"
#include "Component.h"
#include "Engine.h"
#include "Sprite.h"
#include <memory>

namespace game {
Player::Player(float x, float y, float w, float h, std::string path_to_image,
               std::string id)
    : engine::Sprite(x, y, w, h, path_to_image, id) {}

std::shared_ptr<Player> Player::make(float x, float y, float w, float h,
                                     std::string path_to_image,
                                     std::string id) {
  std::string spec_id = "pl_" + id;
  auto p =
      std::shared_ptr<Player>(new Player(x, y, w, h, path_to_image, spec_id));
  engine::core.add_sprite(p);
  p->set_velocity(5);
  return p;
}

void Player::update(std::vector<std::shared_ptr<Sprite>> others) {
  if (jump_timer > 0) {
    jump_timer--;
  }

  if (get_velocity() < 5) {
    set_velocity(get_velocity() + 0.25);
  }

  engine::Sprite::update(others);
  engine::Component::move(0, get_velocity());
}

void Player::on_action_key_space() {
  if (jump_timer > 0)
    return;

  set_velocity(-5);

  jump_timer = 10;
}

} // namespace game
