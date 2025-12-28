#pragma once

#include "Component.h"
#include <string>

namespace gui {

class Sprite : public Component {
  typedef std::shared_ptr<Sprite> Sprite_ptr;

public:
  // static Sprite_ptr make(float x, float y, float w, float h,
  //                        std::string path_to_image, std::string id,
  //                        bool non_colliding_spawn_point);
  const int get_velocity() { return velocity; }
  const bool can_collide() const { return this->collisionable; }

  void do_track_target();
  void set_track_target(Sprite_ptr other) {
    track_target = other;
    has_track_target = true;
  };
  const Sprite_ptr get_track_target() { return track_target; }
  const bool track_target_safe() { return has_track_target; }
  void draw() const;
  virtual bool take_damage(int damage) { return true; }
  virtual void update() {}
  void set_can_collide(bool col) { this->collisionable = col; }
  void set_velocity(float v);
  bool move(int x, int y);
  bool border_detection();
  // frames between proejctile shootings, 0 is no projectiles'
  void set_projectile_cooldown(float cd) { projectile_cooldown = cd * 60; }
  float get_projectile_cooldown() { return projectile_cooldown; }
  void set_cooldown_counter() { cooldown_counter = projectile_cooldown; }
  int get_cooldown_counter() { return cooldown_counter; }
  void decr_cooldown_counter() { cooldown_counter--; }
  bool move_towards_target(int target_x, int target_y);
  bool is_colliding(const Sprite& other) const;
  bool is_overlapping(const Sprite& other) const;

  bool reached_coordinates(int x, int y, int w, int h) const;
  ~Sprite() { SDL_DestroyTexture(sprite_image); }

protected:
  Sprite(float x, float y, float w, float h, std::string path_to_image,
         std::string id);

private:
  SDL_Texture* sprite_image;
  float velocity = 5;
  bool collisionable = true;

  int cooldown_counter = 0;
  float projectile_cooldown = 0;
  Sprite_ptr track_target;
  bool has_track_target = false;
};

} // namespace gui
