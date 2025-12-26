#include "interactable.h"
#include "GUIEngine.h"
#include <cmath>

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

void Interactable::do_track_target() {
  if (is_overlapping(*track_target))
    return;

  float delta_x = get_rect().x - track_target->get_rect().x;
  float delta_y = get_rect().y - track_target->get_rect().y;

  float vector = sqrt(pow(delta_x, 2) + pow(delta_y, 2));
  float vector_x = delta_x / vector;
  float vector_y = delta_y / vector;

  int movement_x = 5 * vector_x;
  int movement_y = 5 * vector_y;

  // För nån anledning blev matten omvänd så jag skickar in det
  // negativa värdet för jag orkar inte ta reda på varför...
  move(-movement_x, -movement_y);
}

} // namespace gui
