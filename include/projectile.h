
#pragma once

#include "Sprite.h"
#include <SDL3/SDL_video.h>
#include <string>
namespace gui {

class Projectile : public Sprite {
  typedef std::shared_ptr<Projectile> Projectile_ptr;
  typedef std::shared_ptr<Sprite> Sprite_ptr;

public:
  ~Projectile();
  static Projectile_ptr make(float h, float w, std::string path_to_image,
                             std::string base_id, Sprite_ptr from,
                             Sprite_ptr to, int damage);
  void draw() const;

  float get_target_x() { return target_x; }
  float get_target_y() { return target_y; }
  float get_target_h() { return target_h; }
  float get_target_w() { return target_w; }
  void set_target_x(float target_x) { this->target_x = target_x; }
  void set_target_y(float target_y) { this->target_y = target_y; }
  void set_target_h(float target_h) { this->target_h = target_h; }
  void set_target_w(float target_w) { this->target_w = target_w; }
  void set_spawn_sprite(Sprite_ptr sp) { spawn_sprite = sp; }
  Sprite_ptr get_spawn_sprite() { return spawn_sprite; }
  void set_damage(int damage) { this->damage = damage; }
  void do_track_target();
  bool take_damage(int damage) { return true; }

protected:
  Projectile(int x, int y, float h, float w, std::string path_to_image,
             std::string spec_id, int damage);

private:
  Sprite_ptr spawn_sprite;
  float target_x;
  float target_y;
  float target_w;
  float target_h;
  int damage;
};

} // namespace gui
