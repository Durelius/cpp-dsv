
#include "random.h"
#include "GUIEngine.h"
#include <random>

using namespace gui;

int Random::number_between(int min, int max) {
  std::random_device ran;
  std::mt19937 rng(ran());

  std::uniform_int_distribution<std::mt19937::result_type> rand_x(min, max);
  return rand_x(rng);
}