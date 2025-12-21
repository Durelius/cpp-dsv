#include "Component.h"
#include "GUIEngine.h"

namespace gui {
Component::Component(float x, float y, float w, float h) : rect(x, y, w, h) {}

void Component::move(int x, int y) {
  rect.x += x;
  rect.y += y;
}

} // namespace gui
