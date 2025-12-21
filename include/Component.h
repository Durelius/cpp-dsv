#pragma once
#include <memory>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

namespace gui
{

    class Component
    {
    public:
        virtual ~Component() {}
        virtual void draw() const = 0;
        const SDL_FRect &getRect() const { return rect; }
        void move(int x, int y);
        virtual void onMouseDown(const SDL_Event &event) {}
        virtual void onMouseUp(const SDL_Event &event) {}
        virtual void onKeyDown(const SDL_Event &event) {}
        virtual void onKeyUp(const SDL_Event &event) {}
        const std::string getId() const { return id; };
        Component(const Component &other) = delete;
        const Component &operator=(const Component &other) = delete;

    protected:
        Component(float x, float y, float w, float h, std::string id);

    private:
        SDL_FRect rect;
        std::string id;
    };
    typedef std::shared_ptr<Component> CompPtr;
}
