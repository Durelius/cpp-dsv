#include "game.h"
#include "Engine.h"
#include "food_spawner.h"
#include "player.h"
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
  engine::core.clear();
  start();
}

} // namespace game
