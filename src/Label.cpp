#include "Label.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "GUIEngine.h"

namespace gui{

    LabelPtr Label::make(float x,float y,float w,float h,std::string txt){
        return LabelPtr(new Label(x,y,w,h,txt));
    }

    Label::Label(float x,float y,float w,float h,std::string txt):Component(x,y,w,h), text(txt){
        setText(text);
    }

    void Label::draw() const{
        SDL_RenderTexture(eng.getRen(),tex,NULL,&getRect());
    }

    void Label::setText(std::string newText){
        text = newText;
        SDL_DestroyTexture(tex);
        SDL_Surface* surf = TTF_RenderText_Blended(eng.getFont(),text.c_str(),0, {0,0,0});
        tex = SDL_CreateTextureFromSurface(eng.getRen(),surf);
        SDL_DestroySurface(surf);
    }

    Label::~Label(){
        SDL_DestroyTexture(tex);
    }
}
