#include "Button.h"
#include "GUIEngine.h"

namespace gui{
    ButtonPtr Button::make(float x,float y,float w,float h,std::string txt,Action doWhat){
        return ButtonPtr(new Button(x,y,w,h,txt,doWhat));
    }
    
    Button::Button(float x,float y,float w,float h,std::string txt,Action doWhat):Label(x,y,w,h,txt),doIt(doWhat){}

    void Button::draw() const{
        Uint8 r, g, b, a;
        SDL_GetRenderDrawColor(eng.getRen(), &r,&g,&b,&a);
        if (down)
            SDL_SetRenderDrawColor(eng.getRen(),255,0,0,255);
        else
            SDL_SetRenderDrawColor(eng.getRen(),255,192,203,255); // rosa
        SDL_RenderFillRect(eng.getRen(), &getRect());
        SDL_SetRenderDrawColor(eng.getRen(), r,g,b,a);
        Label::draw();
    }

    void Button::onMouseDown(const SDL_Event& event){
        SDL_FPoint point = {event.button.x, event.button.y};
        if (SDL_PointInRectFloat(&point, &getRect())){
            down = true;
        }
    } // onMouseDown
    
    void Button::onMouseUp(const SDL_Event& event){
        SDL_FPoint point = {event.button.x, event.button.y};
        if (down && SDL_PointInRectFloat(&point, &getRect())){
            doIt(getText());    
        }
        down = false;
    }
}