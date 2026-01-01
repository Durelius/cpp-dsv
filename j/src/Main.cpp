#include "Engine.h"
#include "J_Constants.h"
#include "Pipe.h"
#include "Player.h"
#include "Sprite.h"
#include <cstddef>
#include <random>
#include <string>

using namespace engine;
using namespace game;
namespace cns = j_constants;

int get_random_in_split_ranges() {
  static std::random_device rd;
  static std::mt19937 gen(rd());

  // 1. Flip a coin (0 or 1)
  std::uniform_int_distribution<> coin_flip(0, 1);

  if (coin_flip(gen) == 0) {
    // Range A: [-640, -340]
    std::uniform_int_distribution<> dist_a(-540, -340);
    return dist_a(gen);
  } else {
    // Range B: [100, 400]
    std::uniform_int_distribution<> dist_b(100, 300);
    return dist_b(gen);
  }
}

float closest_pipe = 0;
int id = 0;

int main(int argc, char* argv[]) {

  auto p = Player::make(64, 64, 50, 50, cns::player_str, "player");
  core.set_background(j_constants::bg_str, .1);

  core.set_custom_logic([&]() {
    bool collided = false;
    for (auto s : core.get_sprites()) {
      if (s->get_id().substr(0, 2) == "pi") {
        if (p->is_intersecting(s)) {
          collided = true;
        }
      }
    }
    bool y;
    p->out_of_bounds(nullptr, &y);
    if (y)
      collided = true;
    // if (p->get_frect().y < 0 || p->get_frect().y > cns::gScreenHeight - 50) {
    //   collided = true;
    // }

    if (collided) {
      for (auto s : core.get_sprites()) {
        if (s->get_id().substr(0, 2) == "pi") {
          core.delete_sprite(s);
        }
      }
      p->set_coordinates(100, 100);
    }

    for (auto s : core.get_sprites()) {
      if (s->get_id().substr(0, 2) == "pi") {
        if (s->get_frect().x > closest_pipe) {
          closest_pipe = s->get_frect().x;
        }
      }
    }

    if (closest_pipe < 400) {
      Pipe::make(cns::gScreenWidth + 100, get_random_in_split_ranges(), 60, 720,
                 cns::pipe_str, std::to_string(id));
      id++;
    }

    closest_pipe = 0;

    for (auto s : core.get_sprites()) {
      if (s->get_id().substr(0, 2) == "pi") {
        if (s->get_frect().x < -100) {
          core.delete_sprite(s);
        }
      }
    }
  });
  core.game_run();
}
