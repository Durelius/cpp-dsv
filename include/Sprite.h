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

protected:
  Sprite(float x, float y, float w, float h, std::string path_to_image,
         std::string id);

private:
  SDL_Texture* sprite_image;
};

} // namespace gui
