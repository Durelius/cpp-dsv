#pragma once

#include "Component.h"
#include <string>

namespace engine {
class Sprite;
typedef std::shared_ptr<Sprite> Sprite_ptr;
class Sprite : public Component {

public:
  // static Sprite_ptr make(float x, float y, float w, float h,
  //                        std::string path_to_image, std::string id,
  //                        bool non_colliding_spawn_point);

  const int get_velocity() { return velocity; }
  void draw() const;
  virtual void update() {}
  void set_velocity(float v);
  void move(int x, int y);
  bool is_intersecting(Sprite_ptr other);

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

} // namespace engine
