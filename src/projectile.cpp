#include "projectile.h"
#include "GUIEngine.h"
#include "Sprite.h"
#include <iostream>
namespace gui {
typedef std::shared_ptr<Projectile> Projectile_ptr;
Projectile::Projectile(float h, float w, std::string path_to_image,
                       std::string spec_id, Sprite_ptr from, Sprite_ptr to)
    : Sprite(0, 0, w, h, path_to_image, spec_id) {
  target_x = to->get_rect().x;
  target_y = to->get_rect().y;
}

Projectile::~Projectile() {};
Projectile_ptr Projectile::make(float h, float w, std::string path_to_image,
                                std::string base_id, Sprite_ptr from,
                                Sprite_ptr to) {
  std::string spec_id = "pr_" + base_id;
  auto proj_ptr =
      Projectile_ptr(new Projectile(h, w, path_to_image, spec_id, from, to));
  proj_ptr->set_track_target(to);
  eng.add_projectile(proj_ptr);
  return proj_ptr;
}

void Projectile::do_track_target() { move_towards_target(target_x, target_y); }
void Projectile::draw() const { Sprite::draw(); }
} // namespace gui
