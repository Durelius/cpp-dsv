#pragma once
#include "Component.h"
#include <memory>
#include <string>

namespace gui {
class Label;

typedef std::shared_ptr<Label> label_ptr;

class Label : public Component {
public:
  static label_ptr make(float x, float y, float w, float h, std::string text,
                       std::string id);
  ~Label();
  void draw() const;
  void set_text(std::string new_text);
  std::string get_text() const { return text; }

protected:
  Label(float x, float y, float w, float h, std::string text, std::string id);

private:
  std::string text;
  SDL_Texture* texture;
};

} // namespace gui
