#include "DGUI/Button.h"
#include "DCore/ResourceManager.h"

Button::Button(Vector2 pos, Vector2 size, std::string text, OnClickAction action)
    : text(std::move(text)), onClickAction(std::move(action))
{
    this->position = pos;
    this->size = size;
    this->isVisible = true;
    this->isEnabled = true;
}

Button::Button(Vector2 pos, std::string text, float fontSize, Vector2 padding, OnClickAction action)
    : text(std::move(text)), onClickAction(std::move(action))
{
    this->position = pos;
    this->fontSize = fontSize;
    this->isVisible = true;
    this->isEnabled = true;
    Font font = ResourceManager::GetInstance().GetGameFont();
    Vector2 textSize = MeasureTextEx(font, this->text.c_str(), this->fontSize, this->spacing);

    this->size.x = textSize.x + padding.x * 2;
    this->size.y = textSize.y + padding.y * 2;
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
        Color currentBgColor = isEnabled ? baseColor : DARKGRAY;
        Color currentTextColor = isEnabled ? textColor : GRAY;

        if (isEnabled && contains(GetMousePosition()))
        {
            currentBgColor = hoverColor;
        }
       
        // Draw the button background and border
        DrawRectangleV(position, size, currentBgColor);
        DrawRectangleLinesEx({position.x, position.y, size.x, size.y}, 2.0f, DARKGRAY);

        Font font = ResourceManager::GetInstance().GetGameFont();
        Vector2 textSize = MeasureTextEx(font, text.c_str(), fontSize, spacing);
        
        Vector2 textPosition = 
        {
            position.x + (size.x - textSize.x) / 2.0f,
            position.y + (size.y - textSize.y) / 2.0f
        };

        DrawTextEx(font, text.c_str(), textPosition, fontSize, spacing, currentTextColor);
        // DrawText(text.c_str(), position.x + (size.x - textWidth) / 2, position.y + size.y/2 - 10, 20, textColor);
    }

}
