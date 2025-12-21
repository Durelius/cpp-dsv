#include "Sprite.h"
#include "Component.h"
#include "GUIEngine.h"

namespace gui
{
  typedef std::shared_ptr<Sprite> sprite_pointer;

  Sprite::Sprite(float x, float y, float w, float h, std::string path_to_image, std::string id)
      : Component(x, y, w, h, id)
  {
    sprite_image = IMG_LoadTexture(eng.getRen(), path_to_image.c_str());
  }

  sprite_pointer Sprite::make(float x, float y, float w, float h, std::string path_to_image, std::string id)
  {
    return sprite_pointer(new Sprite(x, y, w, h, path_to_image, id));
  }

  void Sprite::draw() const
  {
    SDL_RenderTexture(eng.getRen(), sprite_image, NULL, &getRect());
  }

} // namespace gui
