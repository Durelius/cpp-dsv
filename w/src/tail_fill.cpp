#include "tail_fill.h"
#include "Engine.h"
namespace game {
std::shared_ptr<Tail_Fill> Tail_Fill::make(float x, float y, float h, float w,
                                           std::string path_to_image,
                                           std::string id) {

  std::string spec_id = "tf_" + id;

  auto tail_fill = std::shared_ptr<Tail_Fill>(
      new Tail_Fill(x, y, h, w, path_to_image, spec_id));

  engine::core.add_sprite(tail_fill);

  return tail_fill;
}
} // namespace game
