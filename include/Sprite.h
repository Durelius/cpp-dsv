#pragma once

#include "Component.h"
#include <string>

namespace gui {

class Sprite : public Component {
  typedef std::shared_ptr<Sprite> Sprite_ptr;

public:
  static Sprite_ptr make(float x, float y, float w, float h,
                         std::string path_to_image, std::string id,
                         bool non_colliding_spawn_point);
  const int get_velocity() { return velocity; }
  const bool can_collide() const { return this->collisionable; }
  const bool get_non_colliding_spawn_point() const {
    return this->non_colliding_spawn_point;
  }

  void do_track_target();
  void set_track_target(Sprite_ptr other) {
    track_target = other;
    has_track_target = true;
  };
  bool track_target_safe() { return has_track_target; }
  void draw() const;
  void set_can_collide(bool col) { this->collisionable = col; }
  void set_velocity(float v);
  void move(int x, int y);
  bool border_detection();
  void move_towards_target(int target_x, int target_y);
  bool is_colliding(const Sprite& other) const;
  bool is_overlapping(const Sprite& other) const;
  ~Sprite() { SDL_DestroyTexture(sprite_image); }

protected:
  Sprite(float x, float y, float w, float h, std::string path_to_image,
         std::string id);

private:
  SDL_Texture* sprite_image;
  float velocity = 1;
  bool collisionable = true;
  bool non_colliding_spawn_point = true;

  Sprite_ptr track_target;
  bool has_track_target = false;
};

} // namespace gui
