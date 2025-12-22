#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <memory>
#include <string>

namespace gui {

class Component {
public:
  virtual ~Component() {}

  virtual void draw() const = 0;
  const SDL_FRect& get_rect() const { return rect; }
  const std::string get_id() const { return id; };

  void move(int x, int y);
  void set_coordinates(int x, int y);
  void border_detection();
  virtual void on_mouse_down(const SDL_Event& event) {}
  virtual void on_mouse_up(const SDL_Event& event) {}
  virtual void on_key_down(const SDL_Event& event) {}
  virtual void on_key_up(const SDL_Event& event) {}

  Component(const Component& other) = delete;
  const Component& operator=(const Component& other) = delete;

protected:
  Component(float x, float y, float w, float h, std::string id);

private:
  SDL_FRect rect;
  std::string id;
};
typedef std::shared_ptr<Component> component_ptr;
} // namespace gui
