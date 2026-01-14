#pragma once
#include "Component.h"
#include <memory>
#include <string>

namespace engine {
class UI_Element;

struct Color {
  Uint8 r;
  Uint8 g;
  Uint8 b;
  Uint8 a;
};
typedef std::shared_ptr<UI_Element> UI_Element_ptr;
class UI_Element : public Component {
public:
  static UI_Element_ptr make(float x, float y, float w, float h,
                             std::string text, std::string id);
  ~UI_Element();
  void draw() const;
  void set_text(std::string new_text);
  std::string get_text() const { return text; }
  void set_color(Color color);
  void set_text_color(Color color);
  Color get_text_color() const { return text_color; }

  Color get_color() const { return color; }

protected:
  UI_Element(float x, float y, float w, float h, std::string text,
             std::string id);

private:
  std::string text;
  SDL_Texture* texture;
  Color color = {255, 255, 255, 255};
  Color text_color = {0, 0, 0, 255};
  void update();
};

} // namespace engine
