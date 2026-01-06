
#pragma once
#include "Sprite.h"
#include "food_spawner.h"
#include <memory>
namespace game {
class Food : public engine::Sprite {
public:
  static std::shared_ptr<Food> make(float x, float y, float w, float h,
                                    std::string path_to_image,
                                    std::string base_id);
  ~Food() {}

  void update(std::vector<std::shared_ptr<Sprite>> others);

protected:
  Food(float x, float y, float w, float h, std::string path_to_image,
       std::string id);

private:
};
} // namespace game
