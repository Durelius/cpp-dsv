#pragma once
#include "Component.h"
#include <string>
#include <memory>

namespace gui
{
    class Label;

    typedef std::shared_ptr<Label> LabelPtr;

    class Label : public Component
    {
    public:
        static LabelPtr make(float x, float y, float w, float h, std::string txt, std::string id);
        ~Label();
        void draw() const;
        void setText(std::string newText);
        std::string getText() const { return text; }

    protected:
        Label(float x, float y, float w, float h, std::string txt, std::string id);

    private:
        std::string text;
        SDL_Texture *tex;
    };

}