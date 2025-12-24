#include "GUIEngine.h"
#include "Constants.h"
#include "Player.h"
#include <iostream>
#include <memory>
#include <ostream>

namespace cnts = constants;
namespace gui {

GUIEngine::GUIEngine() {
  SDL_Init(SDL_INIT_VIDEO);
  window = SDL_CreateWindow("GUIExempel", cnts::gScreenWidth,
                            cnts::gScreenHeight, 0);
  renderer = SDL_CreateRenderer(window, NULL);
  TTF_Init();
  font = TTF_OpenFont((cnts::gResPath + "fonts/arial.ttf").c_str(), 24);
}

GUIEngine::~GUIEngine() {
  TTF_CloseFont(font);
  TTF_Quit();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void GUIEngine::add_component(component_ptr c) {
  if (!c) {
    std::cerr << "Tried to add null component" << std::endl;
    throw std::invalid_argument("Tried to add null component");
  }

  for (auto component : components) {
    // std::cout << component->get_id() << std::endl;
    if (c->get_id() == component->get_id()) {
      std::cerr << "ID already exists" << std::endl;
      throw std::invalid_argument("ID already exists");
    }
  }
  this->queue_for_add([this, c]() {
    if (auto sprite = std::dynamic_pointer_cast<Sprite>(c)) {
      int counter = 0;
      while (sprite->get_non_colliding_spawn_point() &&
             eng.is_colliding(*sprite)) {
        sprite->set_coordinates(sprite->get_rect().x + 5,
                                sprite->get_rect().y + 5);
        if (counter > 100)
          break;
      }
    }
    components.push_back(c);
  });
}
component_ptr GUIEngine::get_by_id(std::string id) {
  for (auto& c : components) {
    if (c->get_id() == id) {
      return c;
    }
  }
  return nullptr;
}

void GUIEngine::game_draw() {
  SDL_RenderClear(renderer);
  for (auto component : components)
    component->draw();
  SDL_SetRenderDrawColor(renderer, 9, 13, 19, 255);
  SDL_RenderPresent(renderer);
}

void GUIEngine::game_events() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_EVENT_QUIT:
      running = false;
      break;
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
      for (auto component : components)
        component->on_mouse_down(event);
      break;
    case SDL_EVENT_MOUSE_BUTTON_UP:
      for (auto component : components)
        component->on_mouse_up(event);
      break;
    case SDL_EVENT_KEY_DOWN:
      for (auto component : components) {
        component->on_key_down(event);
      }
      break;
    case SDL_EVENT_KEY_UP:
      for (auto component : components)
        component->on_key_up(event);
      break;
    } // switch
  } // while event
}

void GUIEngine::game_run() {
  running = true;
  while (running) {
    auto start = steady_clock::now();
    game_events();
    player->player_update();
    game_draw();
    handle_creation_queue();
    track_targets();
    lock_frame_rate(start);
  }
}
void GUIEngine::handle_creation_queue() {
  for (auto& task : creation_queue) {
    task();
  }
  creation_queue.clear();
}
bool GUIEngine::is_colliding(const Sprite& moving_object) {
  for (auto& c : components) {
    if (c->get_id() == moving_object.get_id())
      continue;
    if (auto sprite = std::dynamic_pointer_cast<Sprite>(c)) {
      if (sprite->get_collisionable() && sprite->is_colliding(moving_object))
        return true;
    }
  }
  return false;
}
void GUIEngine::track_targets() {
  for (auto& c : components) {
    if (auto interactable = std::dynamic_pointer_cast<Interactable>(c)) {
      if (interactable->track_target_safe())
        interactable->do_track_target();
    }
  }
}

void GUIEngine::lock_frame_rate(time_point start) {
  auto end = steady_clock::now();
  duration d = end - start;
  constexpr auto min_frame = duration(1.0 / 60.0);
  if (d < min_frame) {
    auto delay =
        std::chrono::duration_cast<std::chrono::milliseconds>(min_frame - d);
    SDL_Delay(static_cast<Uint32>(delay.count()));
  }
}

GUIEngine eng;

} // namespace gui
