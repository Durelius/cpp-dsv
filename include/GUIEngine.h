#pragma once
#include "Component.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <memory>
#include <vector>

namespace gui {
class Component;

typedef std::shared_ptr<Component> component_ptr;

class GUIEngine {
public:
  GUIEngine();
  ~GUIEngine();
  SDL_Renderer* get_renderer() const { return renderer; }
  TTF_Font* get_font() const { return font; }

  void add_component(component_ptr c);
  void game_draw();
  void game_events();
  void game_run();

private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  TTF_Font* font;
  std::vector<component_ptr> components;
  bool running;
};
extern GUIEngine eng;
} // namespace gui
