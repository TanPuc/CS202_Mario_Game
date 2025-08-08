#include "../DCore/GUIElement.h"
#include <string>
#include <functional>


class Button : public GUIElement
{
    public:
        std::string text;
        using OnClickAction = std::function<void()>;
    
    private:
        OnClickAction onClickAction;

    public:
        Button (Vector2 pos, Vector2 size, std::string text, OnClickAction action);
        ~Button() override = default;

        void onClick();
        void draw() override;
};

