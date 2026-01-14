#pragma once
#include "Sprite.h"

namespace game {
class Pipe : public engine::Sprite {
public:
  static std::shared_ptr<Pipe> make(float x, float y, float w, float h,
                                    std::string path_to_image,
                                    std::string base_id);
  ~Pipe() {}

  void update(std::vector<std::shared_ptr<Sprite>> others);
protected:
  Pipe(float x, float y, float w, float h, std::string path_to_image,
       std::string id);

private:
};
} // namespace game
