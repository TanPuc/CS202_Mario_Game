#include "DHUD/CoinDisplay.h"

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
    DrawTextureV(coinTexture, position, WHITE);

    std::string text = "x " + std::to_string(currentCoins);

    float textPositionX = position.x + coinTexture.width + 8;
    float textPositionY = position.y + (coinTexture.height / 2.0f) - 10; 
    DrawText(text.c_str(), textPositionX, textPositionY, 20, GOLD);
}
