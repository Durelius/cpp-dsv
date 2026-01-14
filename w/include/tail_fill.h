#pragma once
#include "Sprite.h"

namespace game {
class Tail_Fill : public engine::Sprite {
public:
  static std::shared_ptr<Tail_Fill> make(float x, float y, float h, float w,
                                         std::string path_to_image,

                                         std::string base_id);

protected:
  Tail_Fill(float x, float y, float h, float w, std::string path_to_image,
            std::string spec_id)
      : Sprite(x, y, h, w, path_to_image, spec_id) {}
};

} // namespace game
