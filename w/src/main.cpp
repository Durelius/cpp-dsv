#include "Engine.h"
#include "w_constants.h"
#include <iostream>
using namespace engine;
int main() {
  core.set_background(constants::bg_str, 5);
  core.game_run();
}
