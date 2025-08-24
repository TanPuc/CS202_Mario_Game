#include "DHUD/LifePoint.h"
#include "DCore/ResourceManager.h"
#include <string>

LifePoint::LifePoint(Texture2D heartTexture) : currentLifePoint(maxLifePoint), heartTexture(heartTexture) 
{
    this -> size = {float(heartTexture.width), float(heartTexture.height)};
}

void LifePoint::updateLifePoint(int newCount) 
{
    currentLifePoint = newCount;
}

void LifePoint::draw()
{
    Font font = ResourceManager::GetInstance().GetGameFont();
    float fontSize = 20.0f;
    float spacing = 1.0f;

    DrawTextEx(font, "LIVES", position, fontSize, spacing, WHITE);
    // DrawText("LIVES", position.x, position.y, 20, WHITE);

    float aspectRatio = (float)heartTexture.width / (float)heartTexture.height;
    float iconHeight = 20.0f;
    float iconWidth = iconHeight * aspectRatio;
    Vector2 iconSize = { iconWidth, iconHeight };
    Rectangle iconPosition = { position.x, position.y + 25, iconSize.x, iconSize.y };
    Rectangle sourceRect = { 0, 0, heartTexture.width, heartTexture.height };

    DrawTexturePro(heartTexture, sourceRect, iconPosition, {0, 0}, 0, WHITE);

    std::string lifeText = "x " + std::to_string(currentLifePoint);
    DrawTextEx(font, lifeText.c_str(), {iconPosition.x + iconWidth + 15, iconPosition.y + iconHeight / 2 - MeasureText(lifeText.c_str(), fontSize) / 2 + 5}, fontSize, spacing, WHITE);
    // DrawText(lifeText.c_str(), iconPosition.x + heartTexture.width + 10, iconPosition.y + 5, 20, WHITE);
}
