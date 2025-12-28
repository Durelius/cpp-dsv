#pragma once
#include "Component.h"
#include "Player.h"
#include "projectile.h"
#include "sign.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <chrono>
#include <functional>
#include <interactable.h>
#include <memory>
#include <set>
#include <vector>
namespace gui {
class Component;

typedef std::shared_ptr<Component> Component_ptr;
typedef std::shared_ptr<Sprite> Sprite_ptr;
typedef std::shared_ptr<Player> Player_ptr;
typedef std::shared_ptr<Projectile> Projectile_ptr;
typedef std::shared_ptr<Sign> Sign_ptr;
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

  void add_projectile(Projectile_ptr pr);
  void game_draw();
  void game_events();
  void game_run();
  void lock_frame_rate(time_point start);
  void queue_projectile_for_deletion(Projectile_ptr proj) {
    projectile_deletion_queue.insert(proj);
  }
  void queue_component_for_deletion(Component_ptr comp) {
    component_deletion_queue.insert(comp);
  }
  bool coordinate_border_detection(int x, int y, int w, int h);
  void delete_scheduled();
  void queue_sprite_for_deletion(Sprite_ptr proj) {
    sprite_deletion_queue.insert(proj);
  }
  void set_display_player_health(int x, int y, int h, int w);
  // Queues a task to be done on a frame, which prevents memory leaks
  void queue_for_add(std::function<void()> task) {
    creation_queue.push_back(std::move(task));
  }

  void delete_projectile(std::string id);
  void delete_sprite(std::string id);
  void delete_component(std::string id);
  void prevent_spawn_collision(Sprite_ptr sp);

  bool is_colliding(const Sprite& moving_object) const;

  Component_ptr get_by_id(std::string id);

  Sprite_ptr get_sprite_by_id(std::string id);
  Projectile_ptr get_projectile_by_id(std::string id);

private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  TTF_Font* font;
  std::vector<Component_ptr> components;
  std::vector<Sprite_ptr> sprites;
  std::vector<Projectile_ptr> projectiles;
  Player_ptr player;
  std::vector<std::function<void()>> creation_queue;
  std::set<Projectile_ptr> projectile_deletion_queue;
  std::set<Sprite_ptr> sprite_deletion_queue;
  std::set<Component_ptr> component_deletion_queue;
  void track_targets();
  void handle_creation_queue();
  void display_player_health();

  std::string get_number_sign_by_char(char sign);
  std::vector<Sign_ptr> player_hp_signs;

  bool player_hp_sign_safe = false;

  // std::shared_ptr<Sprite> test_sprite;
  bool running;
};
extern GUIEngine eng;
} // namespace gui
