#include "DHUD/LifePoint.h"

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
    DrawText("LIVES", position.x, position.y, 20, WHITE);
    
    Vector2 iconPosition = { position.x, position.y + 25 };
    DrawTextureV(heartTexture, iconPosition, WHITE);

    std::string lifeText = "x " + std::to_string(currentLifePoint);
    DrawText(lifeText.c_str(), iconPosition.x + heartTexture.width + 10, iconPosition.y + 5, 20, WHITE);
}
