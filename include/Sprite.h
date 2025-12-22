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
  void set_velocity(int v);
  const int get_velocity() { return velocity; }

  ~Sprite() { SDL_DestroyTexture(sprite_image); }

protected:
  Sprite(float x, float y, float w, float h, std::string path_to_image,
         std::string id);

private:
  SDL_Texture* sprite_image;
  int velocity = 1;
};

} // namespace gui
