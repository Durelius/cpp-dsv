#include "game.h"
#include "Engine.h"
#include "food_spawner.h"
#include "player.h"
#include <chrono>
#include <iostream>
#include <thread>
namespace game {

void Game::start() {

  engine::core.set_background(constants_w::bg_str, 0);
  auto p = Player::make(64, 64, 50, 50, constants_w::head_right, "player");
  Food_Spawner::start();
  engine::core.set_custom_logic([&]() { Food_Spawner::spawn(); });
  engine::core.game_run();
}
void Game::restart() {
  Food_Spawner::clear();

  auto sprites = engine::core.get_sprites();
  for (auto sp : sprites) {
    engine::core.delete_sprite(sp);
  }
  auto ui_elements = engine::core.get_ui_elements();
  for (auto ue : ui_elements) {
    engine::core.delete_ui_element(ue);
  }

  engine::core.set_custom_logic([&]() {
    if (engine::core.get_sprites().size() == 0 &&
        engine::core.get_ui_elements().size() == 0) {
      start();
    }
  });
}

} // namespace game
