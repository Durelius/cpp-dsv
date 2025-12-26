#include "interactable.h"
#include "GUIEngine.h"

namespace gui {
typedef std::shared_ptr<Interactable> Interactable_ptr;

Interactable::Interactable(float x, float y, float w, float h,
                           std::string path_to_image, std::string id)
    : Sprite(x, y, w, h, path_to_image, id) {}

Interactable_ptr Interactable::make(float x, float y, float w, float h,
                                    std::string path_to_image,
                                    std::string base_id,
                                    bool non_colliding_spawn_point) {

  std::string spec_id = "in_" + base_id;
  auto ip =
      Interactable_ptr(new Interactable(x, y, w, h, path_to_image, spec_id));
  eng.add_sprite(ip);
  return ip;
}

void Interactable::draw() const { Sprite::draw(); }

} // namespace gui
