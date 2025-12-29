#include "Engine.h"
#include "Constants.h"
#include "Sprite.h"
#include "UI_Element.h"
#include <iostream>
#include <memory>

namespace cnts = constants;
namespace engine {

Engine::Engine() {
  SDL_Init(SDL_INIT_VIDEO);
  window = SDL_CreateWindow("GUIExempel", cnts::gScreenWidth,
                            cnts::gScreenHeight, 0);
  renderer = SDL_CreateRenderer(window, NULL);
  TTF_Init();
  font = TTF_OpenFont((cnts::gResPath + "fonts/arial.ttf").c_str(), 24);
}

Engine::~Engine() {
  TTF_CloseFont(font);
  TTF_Quit();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void Engine::add_ui_element(UI_Element_ptr ui_ptr) {
  if (!ui_ptr) {
    std::cerr << "Tried to add null ui element" << std::endl;
    throw std::invalid_argument("Tried to add null ui element");
  }

  this->queue_for_add([this, ui_ptr]() {
    for (auto el : ui_elements) {
      // std::cout << component->get_id() << std::endl;
      if (ui_ptr->get_id() == el->get_id()) {
        std::cerr << "ID already exists: " << ui_ptr->get_id() << std::endl;
        throw std::invalid_argument("ID already exists");
      }
    }
    ui_elements.push_back(ui_ptr);
  });
}
void Engine::add_sprite(Sprite_ptr sp) {
  if (!sp) {
    std::cerr << "Tried to add null component" << std::endl;
    throw std::invalid_argument("Tried to add null component");
  }

  this->queue_for_add([this, sp]() {
    for (auto sprite : sprites) {
      // std::cout << component->get_id() << std::endl;
      if (sp->get_id() == sprite->get_id()) {
        std::cerr << "ID already exists" << std::endl;
        throw std::invalid_argument("ID already exists");
      }
    }
    sprites.push_back(sp);
  });
}

UI_Element_ptr Engine::get_ui_element_by_id(std::string id) {

  for (auto& ui_el : ui_elements) {
    if (ui_el->get_id() == id) {
      return ui_el;
    }
  }
  return nullptr;
}
Sprite_ptr Engine::get_sprite_by_id(std::string id) {
  for (auto& sp : sprites) {
    if (sp->get_id() == id) {
      return sp;
    }
  }
  return nullptr;
}
void Engine::game_draw() {
  SDL_RenderClear(renderer);
  for (auto ui_el : ui_elements)
    ui_el->draw();
  for (auto sp : sprites)
    sp->draw();
  SDL_SetRenderDrawColor(renderer, 9, 13, 19, 255);
  SDL_RenderPresent(renderer);
}

void Engine::game_events() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_EVENT_QUIT:
      running = false;
      break;
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
      for (auto ui_el : ui_elements)
        ui_el->on_mouse_down(event);
      break;
    case SDL_EVENT_MOUSE_BUTTON_UP:
      for (auto ui_el : ui_elements)
        ui_el->on_mouse_up(event);
      break;
    case SDL_EVENT_KEY_DOWN:
      for (auto ui_el : ui_elements) {
        ui_el->on_key_down(event);
      }
      break;
    case SDL_EVENT_KEY_UP:
      for (auto ui_el : ui_elements)
        ui_el->on_key_up(event);
      break;
    } // switch
  } // while event
}

void Engine::game_run() {
  running = true;
  while (running) {
    auto start = steady_clock::now();
    game_events();
    update_sprites();
    delete_scheduled();
    handle_creation_queue();
    game_draw();
    lock_frame_rate(start);
  }
}
void Engine::handle_creation_queue() {
  for (auto& task : creation_queue) {
    task();
  }
  creation_queue.clear();
}
void Engine::update_sprites() {
  for (auto& sp : sprites) {
    sp->update(sprites);
  }
}
void Engine::delete_scheduled() {

  for (auto sp : sprite_deletion_queue) {
    delete_sprite_from_vector(sp);
  }
  sprite_deletion_queue.clear();

  for (auto ui_el : ui_element_deletion_queue) {
    delete_ui_element_from_vector(ui_el);
  }
  ui_element_deletion_queue.clear();
}
void Engine::delete_sprite_from_vector(Sprite_ptr sp) {

  std::string id = sp->get_id();
  for (auto it = sprites.begin(); it != sprites.end();) {
    if (it->get()->get_id() == id) {
      it = sprites.erase(it);
    } else {
      ++it;
    }
  }
}
void Engine::delete_ui_element_from_vector(UI_Element_ptr ui_el) {
  std::string id = ui_el->get_id();
  for (auto it = sprites.begin(); it != sprites.end();) {
    if (it->get()->get_id() == id) {
      it = sprites.erase(it);
    } else {
      ++it;
    }
  }
}
void Engine::lock_frame_rate(time_point start) {
  auto end = steady_clock::now();
  duration dur = end - start;
  constexpr auto min_frame = duration(1.0 / 60.0);
  if (dur < min_frame) {
    auto delay =
        std::chrono::duration_cast<std::chrono::milliseconds>(min_frame - dur);
    SDL_Delay(static_cast<Uint32>(delay.count()));
  }
}

Engine core;

} // namespace engine
