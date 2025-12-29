#include "UI_Element.h"
#include "Engine.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

namespace engine {

UI_Element_ptr UI_Element::make(float x, float y, float w, float h,
                                std::string text, std::string base_id) {
  std::string spec_id = "lb_" + base_id;

  return UI_Element_ptr(new UI_Element(x, y, w, h, text, spec_id));
}

UI_Element::UI_Element(float x, float y, float w, float h, std::string text,
                       std::string id)
    : Component(x, y, w, h, id), text(text) {
  set_text(text);
}

void UI_Element::draw() const {
  SDL_RenderTexture(core.get_renderer(), texture, NULL, &get_frect());
}

void UI_Element::set_text(std::string new_text) {
  text = new_text;
  SDL_DestroyTexture(texture);
  SDL_Surface* surface =
      TTF_RenderText_Blended(core.get_font(), text.c_str(), 0, {0, 0, 0});
  texture = SDL_CreateTextureFromSurface(core.get_renderer(), surface);
  SDL_DestroySurface(surface);
}

UI_Element::~UI_Element() { SDL_DestroyTexture(texture); }
} // namespace engine
