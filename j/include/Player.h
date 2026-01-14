#pragma once
#include "Sprite.h"
#include <memory>

namespace game {
class Player : public engine::Sprite {
public:
  static std::shared_ptr<Player> make(float x, float y, float w, float h,
                                      std::string path_to_image,
                                      std::string base_id);
  ~Player() {}

  void update(std::vector<std::shared_ptr<Sprite>> others);
  void on_action_key_space();

protected:
  Player(float x, float y, float w, float h, std::string path_to_image,
         std::string id);

private:
  int jump_timer = 5;
};
} // namespace game
