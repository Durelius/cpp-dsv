#include "GUIEngine.h"
#include "Constants.h"
#include "Player.h"
#include <chrono>
#include <iostream>
#include <memory>

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

void GUIEngine::set_player(std::shared_ptr<Player> p) { player = p; }

void GUIEngine::add_component(component_ptr c) {
  for (auto component : components) {
    std::cout << c->get_id() << component->get_id() << std::endl;
    if (c->get_id() == component->get_id()) {
      throw new std::invalid_argument("ID already exists");
    }
  }

  components.push_back(c);
}

void GUIEngine::game_draw() {
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 9, 13, 19, 255);
  player->draw();
  for (auto component : components)
    component->draw();
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
    auto start = std::chrono::steady_clock::now();
    game_events();
    player->player_update();
    game_draw();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> dur = end - start;
    constexpr auto min_frame = std::chrono::duration<double>(1.0 / 60.0);
    if (dur < min_frame) {
      auto delay = std::chrono::duration_cast<std::chrono::milliseconds>(
          min_frame - dur);

      SDL_Delay(static_cast<Uint32>(delay.count()));
    }
  }
}

GUIEngine eng;

} // namespace gui
