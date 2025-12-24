#include "Label.h"
#include "GUIEngine.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

namespace gui {

label_ptr Label::make(float x, float y, float w, float h, std::string text,
                      std::string id) {
  id = "lbl_" + id;

  return label_ptr(new Label(x, y, w, h, text, id));
}

Label::Label(float x, float y, float w, float h, std::string text,
             std::string id)
    : Component(x, y, w, h, id), text(text) {
  set_text(text);
}

void Label::draw() const {
  SDL_RenderTexture(eng.get_renderer(), texture, NULL, &get_rect());
}

void Label::set_text(std::string new_text) {
  text = new_text;
  SDL_DestroyTexture(texture);
  SDL_Surface* surface =
      TTF_RenderText_Blended(eng.get_font(), text.c_str(), 0, {0, 0, 0});
  texture = SDL_CreateTextureFromSurface(eng.get_renderer(), surface);
  SDL_DestroySurface(surface);
}

Label::~Label() { SDL_DestroyTexture(texture); }
} // namespace gui
