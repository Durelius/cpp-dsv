#pragma once
#include "Sprite.h"
#include "location.h"
#include "player.h"
#include "tail_fill.h"
#include <deque>
namespace game {
class Tail;
using Player_ptr = std::shared_ptr<Player>;
typedef std::shared_ptr<Player> Player_ptr;
typedef std::shared_ptr<Tail> Tail_ptr;
typedef std::shared_ptr<Tail_Fill> Tail_Fill_ptr;
class Tail : public engine::Sprite {
public:
  static std::shared_ptr<Tail> make(Tail_ptr, std::string path_to_image,
                                    std::string base_id);
  static std::shared_ptr<Tail> make(Player_ptr, std::string path_to_image,
                                    std::string base_id);
  ~Tail() {}
  void add_to_queue(float x, float y, Direction direction) {
    auto loc = std::make_shared<Location>(x, y, direction);
    coordinate_queue.push_back(loc);
  }
  void pop_queue();
  const std::shared_ptr<Location> get_location();
  bool get_location_safe() { return coordinate_queue.size() > 0; }
  bool reached_coordinates(float x, float y, float h, float w) const;
  Direction get_direction() { return direction; }
  void set_direction(Direction direction) { this->direction = direction; }
  void move(float x, float y);
  void update(std::vector<std::shared_ptr<engine::Sprite>> others) override;
  void move_towards_target(const std::shared_ptr<Location> loc);
  void set_behind(Tail_ptr behind) { this->behind = behind; }
  void set_target(engine::Sprite_ptr target) { this->target = target; }

protected:
  Tail(float x, float y, float w, float h, std::string path_to_image,
       std::string id);

private:
  Direction direction;
  std::deque<std::shared_ptr<Location>> coordinate_queue;
  Tail_ptr behind;
  engine::Sprite_ptr target;
  Tail_Fill_ptr fill_sprite;
};
} // namespace game
