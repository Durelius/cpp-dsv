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
  Uint8 r, g, b, a;
  SDL_GetRenderDrawColor(core.get_renderer(), &r, &g, &b, &a);
  if (down)
    SDL_SetRenderDrawColor(core.get_renderer(), 255, 0, 0, 255);
  else
    SDL_SetRenderDrawColor(core.get_renderer(), 255, 192, 203, 255); // rosa
  SDL_RenderFillRect(core.get_renderer(), &get_frect());
  SDL_SetRenderDrawColor(core.get_renderer(), r, g, b, a);
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
