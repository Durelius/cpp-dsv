#include "GUIEngine.h"
#include "Constants.h"
#include <iostream>

namespace cnts = constants;
namespace gui {

GUIEngine::GUIEngine() {
  SDL_Init(SDL_INIT_VIDEO);
  window = SDL_CreateWindow("GUIExempel", cnts::gScreenWidth, cnts::gScreenHeight,
                         0);
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
    game_events();
    game_draw();
  }
}

GUIEngine eng;

} // namespace gui
