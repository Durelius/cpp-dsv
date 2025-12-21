#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <vector>
#include <memory>
#include "Component.h"

namespace gui{
    class Component;

    typedef std::shared_ptr<Component> CompPtr;
 
    class GUIEngine{
        public:
            GUIEngine();
            ~GUIEngine();
            SDL_Renderer* getRen() const { return ren; }
            TTF_Font* getFont() const { return font; }
            void add(CompPtr c);
            void run();
        private:
            SDL_Window* win;
            SDL_Renderer* ren;
            TTF_Font* font;
            std::vector<CompPtr> comps;

    };
    
    extern GUIEngine eng;
}