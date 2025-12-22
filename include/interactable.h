#pragma once

#include "Sprite.h"
#include <string>
// movable ? - bool, setmovable, default to false
// health ? - int, set to 0 for immortal ?, sethealth, default to null
// collisionable - bool, setcollisionable, default to true
// points to give on death - int, default to 0 or null
namespace gui {

class Interactable : public Sprite {
  typedef std::shared_ptr<Interactable> interactable_pointer;

public:
  static interactable_pointer make(float x, float y, float w, float h,
                                   std::string path_to_image, std::string id);

  void draw() const;
  // void on_key_down(const SDL_Event& event);
  const int get_health() const { return *this->health; }
  const int get_points_on_death() const { return *this->points_on_death; }
  const bool get_collisionable() const { return this->collisionable; }

  void set_health(int health) { this->health = &health; }
  void set_points_on_death(int points_on_death) {
    this->points_on_death = &points_on_death;
  }
  void set_collisionable(bool col) { this->collisionable = &collisionable; }

protected:
  Interactable(float x, float y, float w, float h, std::string path_to_image,
               std::string id);

private:
  const bool* keystate;
  int* health = nullptr;
  int* points_on_death = nullptr;
  bool collisionable = true;
};

} // namespace gui
