#include "Button.h"
#include "Engine.h"
#include "UI_Element.h"

namespace engine {
Button_ptr Button::make(float x, float y, float w, float h, std::string text,
                        Action action, std::string base_id) {
  std::string spec_id = "bt_" + base_id;
  auto btn_ptr = Button_ptr(new Button(x, y, w, h, text, action, spec_id));

  core.add_ui_element(btn_ptr);

  return btn_ptr;
}

Button::Button(float x, float y, float w, float h, std::string text,
               Action action, std::string id)
    : UI_Element(x, y, w, h, text, id), action(action) {}

void Button::draw() const {
  Uint8 prev_r, prev_g, prev_b, prev_a;
  SDL_GetRenderDrawColor(core.get_renderer(), &prev_r, &prev_g, &prev_b,
                         &prev_a);
  if (down)
    SDL_SetRenderDrawColor(core.get_renderer(), color_pressed.r,
                           color_pressed.g, color_pressed.b, color_pressed.a);
  else {
    auto [r, g, b, a] = get_color();
    SDL_SetRenderDrawColor(core.get_renderer(), r, g, b, a);
  }
  SDL_RenderFillRect(core.get_renderer(), &get_frect());
  SDL_SetRenderDrawColor(core.get_renderer(), prev_r, prev_g, prev_b, prev_a);
  UI_Element::draw();
}

void Button::on_mouse_down(const SDL_Event& event) {
  SDL_FPoint point = {event.button.x, event.button.y};
  if (SDL_PointInRectFloat(&point, &get_frect())) {
    down = true;
  }
} // onMouseDown

void Button::on_mouse_up(const SDL_Event& event) {
  SDL_FPoint point = {event.button.x, event.button.y};
  if (down && SDL_PointInRectFloat(&point, &get_frect())) {
    action(get_id());
  }
  down = false;
}

} // namespace engine
