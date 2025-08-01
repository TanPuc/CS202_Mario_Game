#include "DGUI/UIImage.h"

UIImage::UIImage(Texture2D tex, Vector2 pos )
{
    this -> texture = tex;
    this -> position = pos;
    this -> size = {float(tex.width), float(tex.height)};
}

void UIImage::draw()
{
    if (isVisible)
    {
        DrawTexture(texture, (int)position.x, (int)position.y, WHITE);
    }
}