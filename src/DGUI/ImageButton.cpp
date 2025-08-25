#include "DGUI/ImageButton.h"
#include "DCore/ResourceManager.h"

ImageButton::ImageButton(Vector2 pos, Vector2 size, Texture2D tex, std::string text, OnClickAction action)
    : texture(tex), text(std::move(text)), onClickAction(std::move(action))
{
  this->position = pos;
  this->size = size;
  this->font = ResourceManager::GetInstance().GetGameFont();
  this->fontSize = 15.0f;
  this->spacing = 1.0f;
  this->isVisible = true;
  this->isEnabled = true;
}

void ImageButton::onClick()
{
    if (isEnabled && isVisible &&  onClickAction)
    {
        onClickAction();
    }
}

void ImageButton::update()
{
    if (isEnabled && isVisible)
    {
        isHovered = contains(GetMousePosition());
    }
    else
    {
        isHovered = false;
    }
}

void ImageButton::setFontSize(float size)
{
    fontSize = size;
}

void ImageButton::draw()
{
     if (!isVisible) return;

    // Color tint = isEnabled ? (isHovered ? hoverColor : WHITE) : GRAY;
    Color tint = WHITE;
    if (!isEnabled) 
    {
        tint = Fade(DARKGRAY, 0.6f); 
    } else if (isHovered) 
    {
        tint = hoverColor; 
    }

    Rectangle source = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
    Rectangle destination = { position.x, position.y, size.x, size.y };

    Vector2 origin = { 0, 0 };

    DrawTexturePro(texture, source, destination, origin, 0.0f, tint);

    Vector2 textSize = MeasureTextEx(font, text.c_str(), fontSize, spacing);
    Vector2 textPosition = {
        position.x + (size.x - textSize.x) / 2.0f,
        position.y + (size.y - textSize.y) / 2.0f
    };

    DrawTextEx(font, text.c_str(), {textPosition.x + 1, textPosition.y + 1}, fontSize, spacing, Fade(BLACK, 0.5f));
    DrawTextEx(font, text.c_str(), textPosition, fontSize, spacing, textColor);
}