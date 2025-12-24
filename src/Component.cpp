#include "Component.h"
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

  int window_width;
  int window_height;

  SDL_GetWindowSize(eng.get_window(), &window_width, &window_height);
  if (rect.x > window_width - rect.w)
    rect.x = window_width - rect.w;
  if (rect.y > window_height - rect.h)
    rect.y = window_height - rect.h;
}
bool Component::is_colliding(const Component& other) {
  int this_x_start = rect.x;
  int this_x_end = rect.x + rect.w;
  int this_y_start = rect.y;
  int this_y_end = rect.y + rect.h;

  int other_x_start = other.get_rect().x;
  int other_x_end = other.get_rect().x + other.get_rect().w;
  int other_y_start = other.get_rect().y;
  int other_y_end = other.get_rect().y + other.get_rect().h;

  if (this_y_end < other_y_start)
    return false;
  if (other_y_end < this_y_start)
    return false;
  if (this_x_end < other_x_start)
    return false;
  if (other_x_end < this_x_start)
    return false;

  return true;
}

} // namespace gui
