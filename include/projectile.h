
#pragma once

#include "Sprite.h"
#include <string>
namespace gui {

class Projectile : public Sprite {
  typedef std::shared_ptr<Projectile> Projectile_ptr;
  typedef std::shared_ptr<Sprite> Sprite_ptr;

public:
  ~Projectile();
  static Projectile_ptr make(float h, float w, std::string path_to_image,
                             std::string base_id, Sprite_ptr from,
                             Sprite_ptr to);
  void draw() const;
  float get_target_x() { return target_x; }
  float get_target_y() { return target_y; }

  void do_track_target();

protected:
  Projectile(float h, float w, std::string path_to_image, std::string spec_id,
             Sprite_ptr from, Sprite_ptr to);

private:
  float target_x;
  float target_y;
};

} // namespace gui
