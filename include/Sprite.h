#pragma once

#include "Component.h"
#include <string>

namespace gui {

class Sprite : public Component {
  typedef std::shared_ptr<Sprite> sprite_pointer;

public:
  static sprite_pointer make(float x, float y, float w, float h,
                             std::string path_to_image, std::string id);
  void draw() const;
  void track_target(sprite_pointer other);

  void set_velocity(float v);
  const int get_velocity() { return velocity; }

  ~Sprite() { SDL_DestroyTexture(sprite_image); }

protected:
  Sprite(float x, float y, float w, float h, std::string path_to_image,
         std::string id);

private:
  SDL_Texture* sprite_image;
  float velocity = 1;
};

} // namespace gui
