#include "Button.h"
#include "GUIEngine.h"

namespace gui {
button_ptr Button::make(float x, float y, float w, float h, std::string text,
                        Action action, std::string id) {
  id = "btn_" + id;
  auto button_pointer = button_ptr(new Button(x, y, w, h, text, action, id));

  eng.add_component(button_pointer);

  return button_pointer;
}

Button::Button(float x, float y, float w, float h, std::string text,
               Action action, std::string id)
    : Label(x, y, w, h, text, id), action(action) {}

void Button::draw() const {
  Uint8 r, g, b, a;
  SDL_GetRenderDrawColor(eng.get_renderer(), &r, &g, &b, &a);
  if (down)
    SDL_SetRenderDrawColor(eng.get_renderer(), 255, 0, 0, 255);
  else
    SDL_SetRenderDrawColor(eng.get_renderer(), 255, 192, 203, 255); // rosa
  SDL_RenderFillRect(eng.get_renderer(), &get_rect());
  SDL_SetRenderDrawColor(eng.get_renderer(), r, g, b, a);
  Label::draw();
}

void Button::on_mouse_down(const SDL_Event& event) {
  SDL_FPoint point = {event.button.x, event.button.y};
  if (SDL_PointInRectFloat(&point, &get_rect())) {
    down = true;
  }
} // onMouseDown

void Button::on_mouse_up(const SDL_Event& event) {
  SDL_FPoint point = {event.button.x, event.button.y};
  if (down && SDL_PointInRectFloat(&point, &get_rect())) {
    action(get_id());
  }
  down = false;
}

} // namespace gui
