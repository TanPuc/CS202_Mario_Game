#include "../DCore/GUIElement.h"
#include <string>
#include <functional>


class Button : public GUIElement
{
    public:
        std::string text;
        using OnClickAction = std::function<void()>;

        Color baseColor = LIGHTGRAY;
        Color hoverColor = DARKGRAY;
        Color textColor = BLACK;
        float fontSize= 20.0f;
        float spacing = 1.0f;
    private:
        OnClickAction onClickAction;

    public:
        Button (Vector2 pos, Vector2 size, std::string text, OnClickAction action);
        Button (Vector2 pos, std::string text, float fontSize, Vector2 padding, OnClickAction action);
        
        ~Button() override = default;

        void onClick();
        void draw() override;
};

