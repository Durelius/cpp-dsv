#pragma once
#include "Component.h"
#include "Player.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <chrono>
#include <functional>
#include <interactable.h>
#include <memory>
#include <vector>

namespace gui {
class Component;

typedef std::shared_ptr<Component> Component_ptr;
typedef std::shared_ptr<Sprite> Sprite_ptr;
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

  void set_player(std::shared_ptr<Player> p) { player = p; }
  // void set_test_sprite(std::shared_ptr<Sprite> s) { test_sprite = s; }
  void add_component(Component_ptr c);
  void add_sprite(Sprite_ptr c);
  void game_draw();
  void game_events();
  void game_run();
  void lock_frame_rate(time_point start);

  // Queues a task to be done on a frame, which prevents memory leaks
  void queue_for_add(std::function<void()> task) {
    creation_queue.push_back(std::move(task));
  }

  void prevent_spawn_collision(Sprite_ptr sp);

  bool is_colliding(const Sprite& moving_object) const;

  Component_ptr get_by_id(std::string id);

  Sprite_ptr get_sprite_by_id(std::string id);

private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  TTF_Font* font;
  std::vector<Component_ptr> components;
  std::vector<Sprite_ptr> sprites;
  std::shared_ptr<Player> player;
  std::vector<std::function<void()>> creation_queue;

  void track_targets();
  void handle_creation_queue();

  // std::shared_ptr<Sprite> test_sprite;
  bool running;
};
extern GUIEngine eng;
} // namespace gui
