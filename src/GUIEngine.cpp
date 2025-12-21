#include "GUIEngine.h"
#include "Constants.h"
#include <iostream>

namespace cnts = constants;
namespace gui {

GUIEngine::GUIEngine() {
  SDL_Init(SDL_INIT_VIDEO);
  win = SDL_CreateWindow("GUIExempel", cnts::gScreenWidth, cnts::gScreenHeight,
                         0);
  ren = SDL_CreateRenderer(win, NULL);
  TTF_Init();
  font = TTF_OpenFont((cnts::gResPath + "fonts/arial.ttf").c_str(), 24);
}

GUIEngine::~GUIEngine() {
  TTF_CloseFont(font);
  TTF_Quit();
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();
}

void GUIEngine::add(CompPtr c) { comps.push_back(c); }

void GUIEngine::run() {
  bool running = true;
  while (running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_EVENT_QUIT:
        running = false;
        break;
      case SDL_EVENT_MOUSE_BUTTON_DOWN:
        for (CompPtr comp : comps)
          comp->onMouseDown(event);
        break;
      case SDL_EVENT_MOUSE_BUTTON_UP:
        for (CompPtr comp : comps)
          comp->onMouseUp(event);
        break;
      case SDL_EVENT_KEY_DOWN:
        for (CompPtr comp : comps) {
          comp->onKeyDown(event);
        }
        break;
      case SDL_EVENT_KEY_UP:
        for (CompPtr comp : comps)
          comp->onKeyUp(event);
        break;

      } // switch
    } // while event

    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    SDL_RenderClear(ren);
    for (CompPtr comp : comps)
      comp->draw();
    SDL_RenderPresent(ren);
  } // while running
} // run

GUIEngine eng;

} // namespace gui
