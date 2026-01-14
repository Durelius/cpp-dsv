#include "Engine.h"
#include "Constants.h"
#include "Sprite.h"
#include "UI_Element.h"
#include <iostream>
#include <memory>
#include <print>
#include <string>

namespace cnts = constants;
namespace engine {

Engine::Engine() {
  SDL_Init(SDL_INIT_VIDEO);

  window = SDL_CreateWindow("GUIExempel", cnts::gScreenWidth,
                            cnts::gScreenHeight, 0);
  renderer = SDL_CreateRenderer(window, NULL);
  TTF_Init();

  // TTL_OpenFont loads the relative path in another way than the sprite,
  // forcing us to use this constant
  //  font = TTF_OpenFont((cnts::gResPath + "fonts/ARIAL.TTF").c_str(), 24);
  font = TTF_OpenFont((cnts::standard_font).c_str(), 24);
  if (!font) {
    printf("%s\n", SDL_GetBasePath());
    printf("TTF_OpenFont Error: %s\n", SDL_GetError());
    return;
  }
}

Engine::~Engine() {
  SDL_DestroyTexture(background);
  TTF_CloseFont(font);
  TTF_Quit();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void Engine::clear() { clearing = true; }
void Engine::set_background(std::string path_to_image, float velocity) {
  background = IMG_LoadTexture(renderer, path_to_image.c_str());
  background_velocity = velocity;
}

void Engine::set_font(std::string path, float ptsize) {
  font = TTF_OpenFont(path.c_str(), ptsize);
}

void Engine::out_of_bounds(bool* x_res, bool* y_res, int x, int y, int h,
                           int w) {
  int win_height, win_width;
  SDL_GetWindowSize(core.get_window(), &win_width, &win_height);
  if (x_res)
    *x_res = x < 0 || x > win_width - w;
  if (y_res)
    *y_res = y < 0 || y > win_height - h;
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
  draw_background();
  for (auto ui_el : ui_elements)
    ui_el->draw();
  for (auto sp : sprites)
    sp->draw();
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
  while (running && !clearing) {
    auto start = steady_clock::now();
    game_events();
    update_sprites();

    if (custom_logic) {
      custom_logic();
    }

    delete_scheduled();
    handle_creation_queue();
    game_draw();
    lock_frame_rate(start);
  }
  if (clearing) {
    for (auto ui : ui_elements) {
      delete_ui_element(ui);
    }
    for (auto sprite : sprites) {
      delete_sprite(sprite);
    }
    delete_scheduled();
    clearing = false;
  }
}

void Engine::handle_creation_queue() {
  for (auto& task : creation_queue) {
    task();
  }
  creation_queue.clear();
}

void Engine::draw_background() {
  SDL_FRect dst{scroll_offset, 0, constants::gScreenWidth,
                constants::gScreenHeight};
  SDL_RenderTexture(renderer, background, NULL, &dst);

  if (background_velocity == 0)
    return;

  scroll_offset -= background_velocity;

  if (scroll_offset < -constants::gScreenWidth) {
    scroll_offset = 0;
  }

  SDL_FRect dst_offset{scroll_offset + constants::gScreenWidth, 0,
                       constants::gScreenWidth, constants::gScreenHeight};

  SDL_RenderTexture(renderer, background, NULL, &dst_offset);
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
