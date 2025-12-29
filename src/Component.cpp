#include "Component.h"
#include "Engine.h"
#include <iostream>
#include <typeinfo>
namespace engine {
Component::Component(float x, float y, float w, float h, std::string id)
    : rect(x, y, w, h), id(id) {}

void Component::set_coordinates(int x, int y) {
  rect.x = x;
  rect.y = y;
}

} // namespace engine
