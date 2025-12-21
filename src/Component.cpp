#include "Component.h"
#include "GUIEngine.h"

namespace gui {
Component::Component(float x, float y, float w, float h, std::string id)
    : rect(x, y, w, h), id(id) {}

void Component::move(int x, int y) {
  rect.x += x;
  rect.y += y;
}

} // namespace gui
