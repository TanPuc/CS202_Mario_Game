#include "DHUD/CoinDisplay.h"
#include "DCore/ResourceManager.h"
#include <string>
#include <cstdio>

CoinDisplay::CoinDisplay(Texture2D coinTexture) : currentCoins(0), coinTexture(coinTexture) 
{
    this->size = {float(coinTexture.width), float(coinTexture.height)};
}

void CoinDisplay::updateCoins(int newCount) 
{
    currentCoins = newCount;
}

void CoinDisplay::draw()
{
    Font font  = ResourceManager::GetInstance().GetGameFont();
    float fontSize = 20.0f;
    float spacing = 1.0f;

    DrawTextEx(font, "COINS", {position.x, position.y}, fontSize, spacing, WHITE);

    // DrawText ("COINS", position.x, position.y, 20, WHITE);

    DrawTextureV(coinTexture, {position.x, position.y +25}, WHITE);

    std::string text = "x " + std::to_string(currentCoins);

    float textPositionX = position.x + coinTexture.width + 8;
    float textPositionY = position.y + (coinTexture.height / 2.0f) - 10; 
    DrawTextEx(font, text.c_str(), {textPositionX, textPositionY + 25}, fontSize, spacing, GOLD);
}
