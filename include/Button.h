#pragma once
#include "Label.h"
#include <string>

namespace gui
{

    typedef void (*Action)(std::string);

    class Button : public Label
    {
    public:
        static std::shared_ptr<Button> make(float x, float y, float w, float h, std::string txt, Action doWhat, std::string id);
        void onMouseDown(const SDL_Event &event);
        void onMouseUp(const SDL_Event &event);
        void draw() const;

    protected:
        Button(float x, float y, float w, float h, std::string txt, Action doWhat, std::string id);

    private:
        Action doIt;
        bool down = false;
    };

    typedef std::shared_ptr<Button> ButtonPtr;
}