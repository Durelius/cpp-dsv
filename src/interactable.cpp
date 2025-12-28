#include "interactable.h"
#include "GUIEngine.h"

namespace gui {
typedef std::shared_ptr<Interactable> Interactable_ptr;

Interactable::Interactable(float x, float y, float w, float h,
                           std::string path_to_image, std::string id)
    : Sprite(x, y, w, h, path_to_image, id) {}

Interactable_ptr Interactable::make(float x, float y, float w, float h,
                                    std::string path_to_image,
                                    std::string base_id,
                                    bool non_colliding_spawn_point) {

  std::string spec_id = "in_" + base_id;
  auto ip =
      Interactable_ptr(new Interactable(x, y, w, h, path_to_image, spec_id));
  eng.add_sprite(ip);
  return ip;
}

// runs once every frame
void Interactable::update() {
  decr_cooldown_counter();
  if (track_target_safe())
    do_track_target();

  if (get_projectile_cooldown() > 0 && get_cooldown_counter() <= 0) {
    auto proj = Projectile::make(10, 10, "resources/images/projectile.png",
                                 "updateshoot", eng.get_sprite_by_id(get_id()),
                                 eng.get_player(), 10);
    set_cooldown_counter();
  }
}
// returns true if target is DEAD, false if target doesn't have health assigned
bool Interactable::take_damage(int damage) {
  if (!has_health)
    return false;
  set_health(*health - damage);
  if (*health <= 0)
    return true;
  return false;
}
void Interactable::draw() const { Sprite::draw(); }

} // namespace gui
