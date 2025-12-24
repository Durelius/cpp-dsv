#include "interactable.h"
#include "GUIEngine.h"
#include <cmath>

namespace gui {
typedef std::shared_ptr<Interactable> interactable_pointer;

Interactable::Interactable(float x, float y, float w, float h,
                           std::string path_to_image, std::string id)
    : Sprite(x, y, w, h, path_to_image, id) {}

interactable_pointer Interactable::make(float x, float y, float w, float h,
                                        std::string path_to_image,
                                        std::string id,
                                        bool non_colliding_spawn_point) {
  auto ip =
      interactable_pointer(new Interactable(x, y, w, h, path_to_image, id));
  eng.add_component(ip);

  return ip;
}

void Interactable::draw() const { Sprite::draw(); }

void Interactable::do_track_target() {
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

// void Player::on_key_down(const SDL_Event& event) {
//   switch (event.key.scancode) {
//   case SDL_SCANCODE_W:
//     move(0, -10);
//     break;
//   case SDL_SCANCODE_A:
//     move(-10, 0);
//     break;
//   case SDL_SCANCODE_S:
//     move(0, 10);
//     break;
//   case SDL_SCANCODE_D:
//     move(10, 0);
//     break;
//   default:
//     break;
//   }
// }

} // namespace gui
