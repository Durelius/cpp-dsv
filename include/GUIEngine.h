#pragma once
#include "Component.h"
#include "Player.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <chrono>
#include <memory>
#include <vector>

namespace gui {
class Component;

typedef std::shared_ptr<Component> component_ptr;
typedef std::chrono::steady_clock::time_point time_point;
typedef std::chrono::steady_clock steady_clock;
typedef std::chrono::duration<double> duration;

class GUIEngine {
public:
  GUIEngine();
  ~GUIEngine();
  SDL_Renderer* get_renderer() const { return renderer; }
  TTF_Font* get_font() const { return font; }
  SDL_Window* get_window() const { return window; }

  void set_player(std::shared_ptr<Player> p);
  void add_component(component_ptr c);
  void game_draw();
  void game_events();
  void game_run();
  void lock_frame_rate(time_point start);

private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  TTF_Font* font;
  std::vector<component_ptr> components;
  std::shared_ptr<Player> player;
  bool running;
};
extern GUIEngine eng;
} // namespace gui
