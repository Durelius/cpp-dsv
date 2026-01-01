// #include "player.h"
// #include "Engine.h"
// #include <filesystem>
//
// void Player::update(std::vector<Sprite_ptr> others) {
//   engine::Sprite::update(others);
// }
// Player_ptr Player::make(float x, float y, float w, float h,
//                         std::string path_to_image, std::string base_id) {
//   std::string spec_id = "sp_" + base_id;
//   auto player = new Player(x, y, w, h, path_to_image, spec_id);
//   auto sp_ptr = Sprite::make(x, y, w, h, path_to_image, spec_id);
//   engine::core.add_sprite(sp_ptr);
//   return sp;
// }
