#pragma once

#include "Sprite.h"
#include <string>
// movable ? - bool, setmovable, default to false
// health ? - int, set to 0 for immortal ?, sethealth, default to null
// points to give on death - int, default to 0 or null
namespace gui {

class Interactable : public Sprite {
  typedef std::shared_ptr<Interactable> Interactable_ptr;
  typedef std::shared_ptr<Sprite> Sprite_ptr;

public:
  static Interactable_ptr make(float x, float y, float w, float h,
                               std::string path_to_image, std::string id,
                               bool non_colliding_spawn_point);
  void draw() const;
  const int get_health() const { return *this->health; }
  const int get_points_on_death() const { return *this->points_on_death; }

  const bool get_health_safe() const { return this->has_health; }
  const bool get_points_on_death_safe() const {
    return this->has_points_on_death;
  }
  // seconds between proejctile shootings, 0 is no projectiles
  void set_projectile_cooldown(float cd) { projectile_cooldown = cd; }

  bool take_damage(int damage);
  void set_health(int health) {
    has_health = true;

    this->health = std::make_unique<int>(health);
  }
  void set_points_on_death(int points_on_death) {
    has_points_on_death = true;
    this->points_on_death = std::make_unique<int>(points_on_death);
  }

protected:
  Interactable(float x, float y, float w, float h, std::string path_to_image,
               std::string id);

private:
  std::unique_ptr<int> health;
  std::unique_ptr<int> points_on_death;
  float projectile_cooldown = 0;
  bool has_health = false;
  bool has_points_on_death = false;
};

} // namespace gui
