#include "Component.h"
#include "Engine.h"
namespace engine {
Component::Component(float x, float y, float w, float h, std::string id)
    : rect(x, y, w, h), id(id) {}

void Component::set_coordinates(float x, float y) {
  rect.x = x;
  rect.y = y;
}

void Component::move(float paramX, float paramY) {

  set_coordinates(get_frect().x + paramX, get_frect().y + paramY);
}

} // namespace engine
