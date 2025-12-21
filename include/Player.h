#pragma once

#include "Sprite.h"
#include <string>

namespace gui {

class Player : public Sprite {
  typedef std::shared_ptr<Player> player_pointer;

public:
  static player_pointer make(float x, float y, float w, float h,
                             std::string path_to_image);

  void draw() const;
  void onKeyDown(const SDL_Event& event);

protected:
  Player(float x, float y, float w, float h, std::string path_to_image);
};

} // namespace gui
