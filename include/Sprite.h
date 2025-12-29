#pragma once

#include "Component.h"
#include <string>
#include <vector>
namespace engine {
class Sprite;
typedef std::shared_ptr<Sprite> Sprite_ptr;
class Sprite : public Component {

public:
  const float get_velocity() { return velocity; }
  void draw() const;
  void set_velocity(float v);
  void move(float x, float y);
  bool is_intersecting(Sprite_ptr other);
  virtual void update(std::vector<Sprite_ptr> others);
  virtual void on_action_key_left() {}
  virtual void on_action_key_right() {}
  virtual void on_action_key_up() {}
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
