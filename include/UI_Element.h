#pragma once
#include "Component.h"
#include <memory>
#include <string>

namespace engine {
class UI_Element;

typedef std::shared_ptr<UI_Element> UI_Element_ptr;
class UI_Element : public Component {
public:
  static UI_Element_ptr make(float x, float y, float w, float h,
                             std::string text, std::string id);
  ~UI_Element();
  void draw() const;
  void set_text(std::string new_text);
  std::string get_text() const { return text; }

protected:
  UI_Element(float x, float y, float w, float h, std::string text,
             std::string id);

private:
  std::string text;
  SDL_Texture* texture;
};

} // namespace engine
