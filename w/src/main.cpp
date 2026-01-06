#include "Constants.h"
#include "Engine.h"
#include "UI_Element.h"
#include "constants_w.h"
#include "food_spawner.h"
#include "player.h"
#include <iostream>
using namespace engine;
using namespace game;
int main() {
  // core.set_background(constants_w::bg_str, 0);
  // auto p = Player::make(64, 64, 50, 50, constants_w::head_right, "player");
  // Food_Spawner::start();
  // core.set_custom_logic([&]() { Food_Spawner::spawn(); });
  auto sign = engine::UI_Element::make(0, 0, 100, 100, "test", "test");
  sign->set_text_color({0, 20, 25, 55});
  // core.set_custom_logic([&]() { sign->set_text("test"); });
  core.set_font(constants::standard_font, 24);
  core.game_run();
}
