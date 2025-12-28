#include "GUIEngine.h"
#include "Constants.h"
#include "random.h"
#include <iostream>
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

void GUIEngine::add_component(Component_ptr c) {
  if (!c) {
    std::cerr << "Tried to add null component" << std::endl;
    throw std::invalid_argument("Tried to add null component");
  }

  this->queue_for_add([this, c]() {
    for (auto component : components) {
      // std::cout << component->get_id() << std::endl;
      if (c->get_id() == component->get_id()) {
        std::cerr << "ID already exists: " << c->get_id() << std::endl;
        throw std::invalid_argument("ID already exists");
      }
    }
    components.push_back(c);
  });
}
void GUIEngine::add_sprite(Sprite_ptr sp) {
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
    prevent_spawn_collision(sp);
    sprites.push_back(sp);
  });
}
void GUIEngine::add_projectile(Projectile_ptr pr) {
  if (!pr) {
    std::cerr << "Tried to add null component" << std::endl;
    throw std::invalid_argument("Tried to add null component");
  }

  this->queue_for_add([this, pr]() {
    for (auto projectile : projectiles) {
      // std::cout << component->get_id() << std::endl;
      if (pr->get_id() == projectile->get_id()) {
        std::cerr << "ID already exists" << std::endl;
        throw std::invalid_argument("ID already exists");
      }
    }
    prevent_spawn_collision(pr);
    projectiles.push_back(pr);
  });
}

// attemps 100 spawn locations incrementing both X and Y by 5, until we give up
void GUIEngine::prevent_spawn_collision(Sprite_ptr sp) {
  int counter = 0;
  while (sp->get_non_colliding_spawn_point() && is_colliding(*sp)) {

    int window_width;
    int window_height;

    SDL_GetWindowSize(eng.get_window(), &window_width, &window_height);
    int random_x = Random::number_between(0, window_width);
    int random_y = Random::number_between(0, window_height);
    sp->set_coordinates(random_x, random_y);
    if (counter > 100) {
      std::cerr << "Sprite with id: " << sp->get_id()
                << "couldn't be spawned because of "
                   "coordinate clash"
                << std::endl;
      queue_sprite_for_deletion(sp);
      return;
    }
    counter++;
  }
}
Component_ptr GUIEngine::get_by_id(std::string id) {
  for (auto& c : components) {
    if (c->get_id() == id) {
      return c;
    }
  }
  for (auto& sp : sprites) {
    if (sp->get_id() == id) {
      return sp;
    }
  }
  return nullptr;
}

Sprite_ptr GUIEngine::get_sprite_by_id(std::string id) {
  for (auto& sp : sprites) {
    if (sp->get_id() == id) {
      return sp;
    }
  }
  return nullptr;
}
Projectile_ptr GUIEngine::get_projectile_by_id(std::string id) {
  for (auto& pr : projectiles) {

    if (pr->get_id() == id) {
      return pr;
    }
  }
  return nullptr;
}

void GUIEngine::game_draw() {
  SDL_RenderClear(renderer);
  for (auto component : components)
    component->draw();
  for (auto sp : sprites)
    sp->draw();
  for (auto pr : projectiles)
    pr->draw();
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
    track_targets();
    delete_scheduled();
    handle_creation_queue();
    display_player_health();
    lock_frame_rate(start);
  }
}
void GUIEngine::set_display_player_health(int x, int y, int w, int h) {
  player_hp_sign_safe = true;

  auto player_hp_sign_1 = Sign::make(x, y, w, h, constants::sign_0, "hp_1");
  player_hp_signs.push_back(player_hp_sign_1);
}
void GUIEngine::display_player_health() {
  if (!player_hp_sign_safe)
    return;
  auto health_str = std::format("{}", player->get_health());
  if (player->get_health() < 0)
    health_str = "0";
  if (health_str.length() == player_hp_signs.size()) {
    for (size_t i = 0; i < health_str.length(); i++) {
      player_hp_signs[i]->set_image(get_number_sign_by_char(health_str[i]));
    }
    return;
  }
  int x = player_hp_signs[0]->get_rect().x;
  int y = player_hp_signs[0]->get_rect().y;
  int h = player_hp_signs[0]->get_rect().h;
  int w = player_hp_signs[0]->get_rect().w;

  for (size_t i = 0; i < player_hp_signs.size(); i++) {
    queue_component_for_deletion(player_hp_signs[i]);
  }
  player_hp_signs.clear();

  for (size_t i = 0; i < health_str.length(); i++) {
    auto sign = Sign::make(x, y, w, h, get_number_sign_by_char(health_str[i]),
                           std::format("hp_{}", i));
    x += w;
    player_hp_signs.push_back(sign);
  }
}
std::string GUIEngine::get_number_sign_by_char(char sign) {
  switch (sign) {
  case '0':
    return constants::sign_0;
  case '1':
    return constants::sign_1;
  case '2':
    return constants::sign_2;
  case '3':
    return constants::sign_3;
  case '4':
    return constants::sign_4;
  case '5':
    return constants::sign_5;
  case '6':
    return constants::sign_6;
  case '7':
    return constants::sign_7;
  case '8':
    return constants::sign_8;
  case '9':
    return constants::sign_9;
  default:
    return constants::sign_0;
  }
}
void GUIEngine::handle_creation_queue() {
  for (auto& task : creation_queue) {
    task();
  }
  creation_queue.clear();
}
bool GUIEngine::coordinate_border_detection(int x, int y, int w, int h) {

  if (x < 0) {
    return true;
  }
  if (y < 0) {
    return true;
  }

  int window_width;
  int window_height;

  SDL_GetWindowSize(eng.get_window(), &window_width, &window_height);
  if (x > window_width - w) {
    return true;
  }
  if (y > window_height - h) {
    return true;
  }

  return false;
}
bool GUIEngine::is_colliding(const Sprite& moving_object) const {
  for (auto& sp : sprites) {
    if (sp->get_id() == moving_object.get_id())
      continue;
    if (sp->is_colliding(moving_object)) {
      return true;
    }
  }
  return false;
}
void GUIEngine::track_targets() {
  for (auto& sp : sprites) {
    if (sp->track_target_safe())
      sp->do_track_target();
  }

  for (auto& pr : projectiles) {
    if (pr->track_target_safe())
      pr->do_track_target();
  }
}
void GUIEngine::delete_scheduled() {

  for (auto pr : projectile_deletion_queue) {
    delete_projectile(pr->get_id());
  }
  projectile_deletion_queue.clear();
  for (auto sp : sprite_deletion_queue) {
    delete_projectile(sp->get_id());
  }
  sprite_deletion_queue.clear();

  for (auto co : component_deletion_queue) {
    delete_component(co->get_id());
  }
  component_deletion_queue.clear();
}
void GUIEngine::delete_projectile(std::string id) {

  for (auto it = projectiles.begin(); it != projectiles.end();) {
    if (it->get()->get_id() == id) {
      it = projectiles.erase(it);
    } else {
      ++it;
    }
  }
}

void GUIEngine::delete_component(std::string id) {

  for (auto it = components.begin(); it != components.end();) {
    if (it->get()->get_id() == id) {
      it = components.erase(it);
    } else {
      ++it;
    }
  }
}
void GUIEngine::delete_sprite(std::string id) {

  for (auto it = sprites.begin(); it != sprites.end();) {
    if (it->get()->get_id() == id) {
      it = sprites.erase(it);
    } else {
      ++it;
    }
  }
}
void GUIEngine::lock_frame_rate(time_point start) {
  auto end = steady_clock::now();
  duration dur = end - start;
  constexpr auto min_frame = duration(1.0 / 60.0);
  if (dur < min_frame) {
    auto delay =
        std::chrono::duration_cast<std::chrono::milliseconds>(min_frame - dur);
    SDL_Delay(static_cast<Uint32>(delay.count()));
  }
}

GUIEngine eng;

} // namespace gui
