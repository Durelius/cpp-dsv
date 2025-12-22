#include "Component.h"
#include "Constants.h"
#include "GUIEngine.h"
#include <iostream>

namespace gui {
Component::Component(float x, float y, float w, float h, std::string id)
    : rect(x, y, w, h), id(id) {}

void Component::set_coordinates(int x, int y) {
  rect.x = x;
  rect.y = y;
}
void Component::move(int x, int y) {
  rect.x += x;
  rect.y += y;
  border_detection();
}
void Component::border_detection() {
  if (rect.x < 0)
    rect.x = 0;
  if (rect.y < 0)
    rect.y = 0;
  int w = 0;
  int h = 0;
  SDL_GetWindowSize(eng.get_window(), &w, &h);
  if (rect.x > w - rect.w)
    rect.x = w - rect.w;
  if (rect.y > h - rect.h)
    rect.y = h - rect.h;
}

} // namespace gui
