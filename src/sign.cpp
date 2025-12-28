
#include "sign.h"
#include "Component.h"
#include "GUIEngine.h"
#include <cmath>
#include <memory>
namespace gui {
typedef std::shared_ptr<Sign> Sign_ptr;

Sign::Sign(int x, int y, int w, int h, std::string path_to_image,
           std::string id)
    : Component(x, y, w, h, id) {

  sign_image = IMG_LoadTexture(eng.get_renderer(), path_to_image.c_str());
}

Sign_ptr Sign::make(int x, int y, int w, int h, std::string path_to_image,
                    std::string base_id) {
  std::string spec_id = "si_" + base_id;
  auto sp = Sign_ptr(new Sign(x, y, w, h, path_to_image, spec_id));
  eng.add_component(sp);
  return sp;
}
void Sign::set_image(std::string path_to_image) {
  sign_image = IMG_LoadTexture(eng.get_renderer(), path_to_image.c_str());
}
void Sign::draw() const {
  SDL_RenderTexture(eng.get_renderer(), sign_image, NULL, &get_rect());
}

} // namespace gui
