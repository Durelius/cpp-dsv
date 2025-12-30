#pragma once
#include "UI_Element.h"
#include <string>

namespace engine {

typedef void (*Action)(std::string);

class Button : public UI_Element {

public:
  static std::shared_ptr<Button> make(float x, float y, float w, float h,
                                      std::string text, Action action,
                                      std::string id);
  void on_mouse_down(const SDL_Event& event);
  void on_mouse_up(const SDL_Event& event);
  void draw() const;
  void set_color_pressed(Color color) { color_pressed = color; }

protected:
  Button(float x, float y, float w, float h, std::string text, Action action,
         std::string id);

private:
  Action action;
  bool down = false;
  Color color_pressed = {255, 192, 203, 255};
};
typedef std::shared_ptr<Button> Button_ptr;

} // namespace engine
