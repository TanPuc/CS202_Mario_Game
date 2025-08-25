#pragma once
#include "DCore/GUIElement.h"
#include<string>
#include <functional>

class ImageButton : public GUIElement
{
    public:
        using OnClickAction = std::function<void()>;

        Texture2D texture;
        std::string text;
        Font font;
        float fontSize;
        float spacing;
        Color textColor = WHITE;
        Color hoverColor = LIGHTGRAY;
    
    private:
        OnClickAction onClickAction;
        bool isHovered = false;
    
    public:
        ImageButton(Vector2 pos, Vector2 size, Texture2D tex, std::string text, OnClickAction action);
        ~ImageButton() override = default;

        void onClick();
        void update();
        void setFontSize(float size);
        void draw() override;
};