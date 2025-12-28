
#pragma once

#include "Component.h"
#include <string>

namespace gui {

class Sign : public Component {
  typedef std::shared_ptr<Sign> Sign_ptr;

public:
  // static Sprite_ptr make(float x, float y, float w, float h,
  //                        std::string path_to_image, std::string id,
  //                        bool non_colliding_spawn_point);

  static Sign_ptr make(int x, int y, int w, int h, std::string path_to_image,
                       std::string id);
  ~Sign() { SDL_DestroyTexture(sign_image); }
  void set_image(std::string path_to_image);
  void draw() const;

protected:
  Sign(int x, int y, int w, int h, std::string path_to_image, std::string id);

private:
  SDL_Texture* sign_image;
};

} // namespace gui
