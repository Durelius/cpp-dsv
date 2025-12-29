#pragma once
#include "Component.h"
#include "Sprite.h"
#include "UI_Element.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <chrono>
#include <functional>
#include <memory>
#include <set>
#include <vector>
namespace engine {

class Component;

typedef std::chrono::steady_clock::time_point time_point;
typedef std::chrono::steady_clock steady_clock;
typedef std::chrono::duration<double> duration;

class Engine {
public:
  Engine();
  ~Engine();
  SDL_Renderer* get_renderer() const { return renderer; }
  TTF_Font* get_font() const { return font; }
  SDL_Window* get_window() const { return window; }
  Sprite_ptr get_sprite_by_id(std::string id);
  UI_Element_ptr get_ui_element_by_id(std::string id);

  void add_ui_element(UI_Element_ptr c);
  void add_sprite(Sprite_ptr c);
  void queue_for_add(std::function<void()> task) {
    creation_queue.push_back(std::move(task));
  }

  void set_font(std::string path, float ptsize);

  void delete_sprite(Sprite_ptr sp) { sprite_deletion_queue.insert(sp); }
  void delete_ui_element(UI_Element_ptr ui_el) {
    ui_element_deletion_queue.insert(ui_el);
  }
  void delete_scheduled();

  void game_draw();
  void game_events();
  void game_run();
  void lock_frame_rate(time_point start);

private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  TTF_Font* font;
  std::vector<std::function<void()>> creation_queue;
  std::vector<Sprite_ptr> sprites;
  std::vector<UI_Element_ptr> ui_elements;
  std::set<Sprite_ptr> sprite_deletion_queue;
  std::set<UI_Element_ptr> ui_element_deletion_queue;
  void handle_creation_queue();
  void delete_sprite_from_vector(Sprite_ptr sp);
  void delete_ui_element_from_vector(UI_Element_ptr sp);
  void update_sprites();
  bool running;
};
extern Engine core;
} // namespace engine
