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
    Font font = ResourceManager::GetInstance().GetGameFont();
    float fontSize = 20.0f;
    float spacing = 1.0f;

    DrawTextEx(font, "COINS", {position.x, position.y}, fontSize, spacing, WHITE);

    // DrawText ("COINS", position.x, position.y, 20, WHITE);
    float aspectRatio = (float)coinTexture.width / (float)coinTexture.height;
    float coinDisplayHeight = 20.0f;
    float coinDisplayWidth = coinDisplayHeight * aspectRatio;
    Vector2 coinSize = {coinDisplayWidth, coinDisplayHeight};
    Rectangle coinRect = {position.x, position.y + 25, coinSize.x, coinSize.y};
    Rectangle sourceRect = {0, 0, static_cast<float>(coinTexture.width), static_cast<float>(coinTexture.height)};

    DrawTexturePro(coinTexture, sourceRect, coinRect, {0, 0}, 0, WHITE);

    std::string text = "x " + std::to_string(currentCoins);

    float textPositionX = position.x + coinDisplayWidth + 15;
    float textPositionY = position.y + (coinDisplayHeight / 2.0f) - MeasureText(text.c_str(), fontSize) / 2.0f + 4;
    DrawTextEx(font, text.c_str(), {textPositionX, textPositionY + 25}, fontSize, spacing, GOLD);
}
