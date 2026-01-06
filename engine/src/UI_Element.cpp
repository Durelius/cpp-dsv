#include "UI_Element.h"
#include "Engine.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

namespace engine {

UI_Element_ptr UI_Element::make(float x, float y, float w, float h,
                                std::string text, std::string base_id) {
  std::string spec_id = "lb_" + base_id;
  auto ui_el = UI_Element_ptr(new UI_Element(x, y, w, h, text, spec_id));
  core.add_ui_element(ui_el);
  return ui_el;
}

UI_Element::UI_Element(float x, float y, float w, float h, std::string text,
                       std::string id)
    : Component(x, y, w, h, id), text(text) {
  set_text(text);
}

void UI_Element::draw() const {
  Uint8 prev_r, prev_g, prev_b, prev_a;
  SDL_GetRenderDrawColor(core.get_renderer(), &prev_r, &prev_g, &prev_b,
                         &prev_a);
  auto [r, g, b, a] = get_color();
  SDL_SetRenderDrawColor(core.get_renderer(), r, g, b, a);
  SDL_RenderFillRect(core.get_renderer(), &get_frect());
  SDL_RenderTexture(core.get_renderer(), texture, NULL, &get_frect());
  SDL_SetRenderDrawColor(core.get_renderer(), prev_r, prev_g, prev_b, prev_a);
}
// void UI_Element::update() {
//   SDL_DestroyTexture(texture);
//   auto [r, g, b, a] = text_color;
//   SDL_Surface* surface =
//       TTF_RenderText_Blended(core.get_font(), text.c_str(), 0, {r, g, b, a});
//   texture = SDL_CreateTextureFromSurface(core.get_renderer(), surface);
//   SDL_DestroySurface(surface);
// }
void UI_Element::update() {
  if (texture) {
    SDL_DestroyTexture(texture);
    texture = nullptr;
  }

  auto [r, g, b, a] = text_color;

  auto font = core.get_font();
  SDL_Renderer* renderer = core.get_renderer();

  if (!font) {
    SDL_Log("FONT IS NULL");
    return;
  }

  SDL_Surface* surface =
      TTF_RenderText_Blended(font, text.c_str(), 0, {r, g, b, a});

  if (!surface) {
    SDL_Log("TTF_RenderText failed: %s", SDL_GetError());
    return;
  }

  texture = SDL_CreateTextureFromSurface(renderer, surface);

  if (!texture) {
    SDL_Log("CreateTexture failed: %s", SDL_GetError());
    SDL_DestroySurface(surface);
    return;
  }

  SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
  SDL_DestroySurface(surface);

  float w, h;
  SDL_GetTextureSize(texture, &w, &h);
  SDL_Log("Text texture size: %f x %f", w, h);
}
void UI_Element::set_text(std::string new_text) {
  text = new_text;
  update();
}

void UI_Element::set_text_color(Color color) {
  this->text_color = color;
  update();
}
UI_Element::~UI_Element() { SDL_DestroyTexture(texture); }
} // namespace engine
