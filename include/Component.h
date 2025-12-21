#pragma once
#include <memory>
#include <SDL3/SDL.h>

namespace gui{

    class Component{
        public:
            virtual ~Component(){}
            virtual void draw() const = 0;
            const SDL_FRect& getRect() const { return rect; }
            virtual void onMouseDown(const SDL_Event& event){}
            virtual void onMouseUp(const SDL_Event& event){}
            virtual void onKeyDown(const SDL_Event& event){}
            virtual void onKeyUp(const SDL_Event& event){}

            Component(const Component& other) = delete;
            const Component& operator=(const Component& other) = delete;

        protected:
            Component(float x,float y,float w,float h);
        private:
            SDL_FRect rect;
    };
    typedef std::shared_ptr<Component> CompPtr;
}  