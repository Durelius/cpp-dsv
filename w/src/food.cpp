
#include "food.h"
#include "Component.h"
#include "Engine.h"
#include "Sprite.h"
#include <memory>
namespace game {
Food::Food(float x, float y, float w, float h, std::string path_to_image,
           std::string id)
    : engine::Sprite(x, y, w, h, path_to_image, id) {}

std::shared_ptr<Food> Food::make(float x, float y, float w, float h,
                                 std::string path_to_image, std::string id) {
  std::string spec_id = "fo_" + id;
  auto food_ptr =
      std::shared_ptr<Food>(new Food(x, y, w, h, path_to_image, spec_id));

  engine::core.add_sprite(food_ptr);
  food_ptr->set_velocity(0);
  return food_ptr;
}

void Food::update(std::vector<std::shared_ptr<Sprite>> others) {

  engine::Sprite::update(others);
}

} // namespace game
