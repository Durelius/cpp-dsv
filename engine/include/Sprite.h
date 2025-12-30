#pragma once

#include "Component.h"
#include <string>
#include <vector>
namespace engine {
class Sprite;
typedef std::shared_ptr<Sprite> Sprite_ptr;
class Sprite : public Component {

public:
  static Sprite_ptr make(float x, float y, float w, float h,
                         std::string path_to_image, std::string base_id);
  const float get_velocity() { return velocity; }
  void draw() const;
  void set_velocity(float v);
  void move(float x, float y);
  // returns true if other exists and is intersecting
  bool is_intersecting(Sprite_ptr other);
  // overshadowable method that runs on every frame
  virtual void update(std::vector<Sprite_ptr> others);
  // applies on both A and left arrow
  virtual void on_action_key_left() {}
  // applies on both D and right arrow
  virtual void on_action_key_right() {}
  // applies on both W and up arrow
  virtual void on_action_key_up() {}
  // applies on both S and down arrow
  virtual void on_action_key_down() {}
  virtual void on_action_key_space() {}
  virtual ~Sprite() { SDL_DestroyTexture(sprite_image); }

protected:
  Sprite(float x, float y, float w, float h, std::string path_to_image,
         std::string id);

private:
  SDL_Texture* sprite_image;
  float velocity = 5;
  const bool* keystate;
};

} // namespace engine
