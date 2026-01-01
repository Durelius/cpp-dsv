#include "Pipe.h"
#include "Component.h"
#include "Engine.h"
#include <memory>

namespace game {
Pipe::Pipe(float x, float y, float w, float h, std::string path_to_image,
           std::string id)
    : engine::Sprite(x, y, w, h, path_to_image, id) {}

std::shared_ptr<Pipe> Pipe::make(float x, float y, float w, float h,
                                 std::string path_to_image, std::string id) {
  std::string spec_id = "pi_" + id;
  auto p = std::shared_ptr<Pipe>(new Pipe(x, y, w, h, path_to_image, spec_id));
  engine::core.add_sprite(p);
  p->set_velocity(3);
  return p;
}

void Pipe::update(std::vector<std::shared_ptr<Sprite>> others) {
  engine::Component::move(-get_velocity(), 0);
}

} // namespace game
