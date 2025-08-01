#include "DGUI/Button.h"

Button::Button(Vector2 pos, Vector2 size, std::string text, OnClickAction action)
    : text(std::move(text)), onClickAction(std::move(action))
{
    this->position = pos;
    this->size = size;
    this->isVisible = true;
    this->isEnabled = true;
}

void Button::onClick()
{
    if (isEnabled && isVisible && onClickAction)
    {
        onClickAction();
    }
}

void Button::draw()
{
    if (isVisible)
    {
        Color bgColor = isEnabled ? LIGHTGRAY : DARKGRAY;
        Color textColor = isEnabled ? BLACK : GRAY;

        if (isEnabled && contains(GetMousePosition()))
        {
            bgColor = GRAY;
        }
        DrawRectangleV(position, size, bgColor);
        DrawRectangleLinesEx({position.x, position.y, size.x, size.y}, 2.0f, DARKGRAY);
        float textWidth = MeasureText(text.c_str(), 20);
        DrawText(text.c_str(), position.x + (size.x - textWidth) / 2, position.y + size.y/2 - 10, 20, textColor);
    }

}
