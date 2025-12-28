#include "projectile.h"
#include "GUIEngine.h"
#include "Sprite.h"
#include "random.h"
#include <cmath>
#include <iostream>
namespace gui {
typedef std::shared_ptr<Projectile> Projectile_ptr;
Projectile::Projectile(int x, int y, float h, float w,
                       std::string path_to_image, std::string spec_id,
                       int damage)
    : Sprite(x, y, w, h, path_to_image, spec_id) {
  // y = kx+  m;
}
Projectile::~Projectile() {};
// uses power of math to find out where the final destination should be of the
// projectile, and removes itself when it reaches that point, collides with
// another collisionable or gets out of bounds
Projectile_ptr Projectile::make(float h, float w, std::string path_to_image,
                                std::string base_id, Sprite_ptr from,
                                Sprite_ptr to, int damage) {
  std::string spec_id = std::format("pr_{}_{}_from:{}_to:{}", base_id,
                                    Random::number_between(0, 50000),
                                    from->get_id(), to->get_id());

  float from_x = from->get_rect().x;
  float target_x = to->get_rect().x;
  float from_y = from->get_rect().y;
  float target_y = to->get_rect().y;
  float target_h = to->get_rect().h;
  float target_w = to->get_rect().w;
  auto proj_ptr = Projectile_ptr(
      new Projectile(from_x, from_y, h, w, path_to_image, spec_id, damage));
  proj_ptr->set_track_target(to);
  proj_ptr->set_spawn_sprite(from);

  float delta_x = target_x - from_x;
  float delta_y = target_y - from_y;
  float length = std::sqrt(std::pow(delta_x, 2) + std::pow(delta_y, 2));
  delta_x = delta_x / length;
  delta_y = delta_y / length;

  while (!eng.coordinate_border_detection(target_x, target_y, target_w,
                                          target_h)) {
    target_x += delta_x;
    target_y += delta_y;
  }
  proj_ptr->set_target_x(target_x);
  proj_ptr->set_target_y(target_y);
  proj_ptr->set_target_w(target_w);
  proj_ptr->set_target_h(target_h);
  proj_ptr->set_damage(damage);
  eng.add_projectile(proj_ptr);
  return proj_ptr;
}
Projectile_ptr Projectile::make(float h, float w, std::string path_to_image,
                                std::string base_id, Player_ptr player,
                                int damage, Direction direction) {
  std::string spec_id =
      std::format("pr_{}_{}_player:{}", base_id,
                  Random::number_between(0, 50000), player->get_id());

  float from_x = player->get_rect().x;
  float from_y = player->get_rect().y;
  auto proj_ptr = Projectile_ptr(
      new Projectile(from_x, from_y, h, w, path_to_image, spec_id, damage));
  proj_ptr->set_spawn_sprite(player);
  switch (direction) {
  case UP:
    proj_ptr->set_target_y(0);
    proj_ptr->set_target_x(from_x);
  }
  proj_ptr->set_damage(damage);
  eng.add_projectile(proj_ptr);
  return proj_ptr;
}
void Projectile::update() {
  if (track_target_safe())
    do_track_target();
  else
    move_towards_target(target_x, target_y);
}
void Projectile::do_track_target() {

  Projectile_ptr pr_ptr = eng.get_projectile_by_id(get_id());
  auto target = get_track_target();
  if (is_colliding(*target)) {
    target->take_damage(damage);
    eng.queue_projectile_for_deletion(pr_ptr);
    return;
  }
  if (border_detection() ||
      reached_coordinates(target_x, target_y, target_w, target_h)) {
    eng.queue_projectile_for_deletion(pr_ptr);
    return;
  }

  if (!move_towards_target(target_x, target_y)) {
    target->take_damage(damage);
    eng.queue_projectile_for_deletion(pr_ptr);
  }
}
void Projectile::draw() const { Sprite::draw(); }
} // namespace gui
