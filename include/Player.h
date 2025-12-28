#pragma once

#include "Sprite.h"
#include <string>

namespace gui {

class Player : public Sprite {
  typedef std::shared_ptr<Player> player_pointer;

public:
  static player_pointer make(float x, float y, float w, float h,
                             std::string path_to_image, std::string id);

  bool take_damage(int damage);
  void draw() const;
  void update();

  const int get_health() const { return *health; }
  void set_health(int health) { this->health = std::make_unique<int>(health); }

protected:
  Player(float x, float y, float w, float h, std::string path_to_image,
         std::string id);

private:
  const bool* keystate;
  std::unique_ptr<int> health;
};

} // namespace gui
