#pragma once
#include "Label.h"
#include <string>

namespace gui {

typedef void (*Action)(std::string);

class Button : public Label {
public:
  static std::shared_ptr<Button> make(float x, float y, float w, float h,
                                      std::string text, Action action,
                                      std::string id);
  void on_mouse_down(const SDL_Event& event);
  void on_mouse_up(const SDL_Event& event);
  void draw() const;

protected:
  Button(float x, float y, float w, float h, std::string text, Action action,
         std::string id);

private:
  Action action;
  bool down = false;
};

typedef std::shared_ptr<Button> button_ptr;
} // namespace gui
