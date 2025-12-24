#pragma once

#include "Component.h"
#include <string>

namespace gui {

class Sprite : public Component {
  typedef std::shared_ptr<Sprite> sprite_pointer;

public:
  static sprite_pointer make(float x, float y, float w, float h,
                             std::string path_to_image, std::string id,
                             bool non_colliding_spawn_point);
  const int get_velocity() { return velocity; }
  const bool get_collisionable() const { return this->collisionable; }
  const bool get_non_colliding_spawn_point() const {
    return this->non_colliding_spawn_point;
  }

  void draw() const;
  void set_collisionable(bool col) { this->collisionable = collisionable; }
  void set_velocity(float v);
  void move(int x, int y);

  ~Sprite() { SDL_DestroyTexture(sprite_image); }

protected:
  Sprite(float x, float y, float w, float h, std::string path_to_image,
         std::string id);

private:
  SDL_Texture* sprite_image;
  float velocity = 1;
  bool collisionable = true;
  bool non_colliding_spawn_point = true;
};

} // namespace gui
