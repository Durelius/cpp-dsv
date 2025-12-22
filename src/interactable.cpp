#include "interactable.h"
#include "GUIEngine.h"

namespace gui {
typedef std::shared_ptr<Interactable> interactable_pointer;

Interactable::Interactable(float x, float y, float w, float h,
                           std::string path_to_image, std::string id)
    : Sprite(x, y, w, h, path_to_image, id) {
  keystate = SDL_GetKeyboardState(NULL);
}

interactable_pointer Interactable::make(float x, float y, float w, float h,
                                        std::string path_to_image,
                                        std::string id) {
  auto ip =
      interactable_pointer(new Interactable(x, y, w, h, path_to_image, id));
  eng.add_component(ip);
  return ip;
}

void Interactable::draw() const { Sprite::draw(); }

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
