#include "DHUD/ScoreDisplay.h"
#include "DCore/ResourceManager.h"
#include <cstdio>
#include <string>

ScoreDisplay::ScoreDisplay() : currentScore(0) {}

void ScoreDisplay::updateScore(long long newScore) 
{
    currentScore = newScore;
}

void ScoreDisplay::draw()
{
    Font font = ResourceManager::GetInstance().GetGameFont();
    float fontSize = 20.0f;
    float spacing = 1.0f;

    DrawTextEx(font, "SCORE", position, fontSize, spacing, WHITE);

    char scoreBuffer[7]; 
    snprintf(scoreBuffer, sizeof(scoreBuffer), "%06lld", currentScore);
    DrawTextEx(font, scoreBuffer, { position.x, position.y + 25 }, fontSize, spacing, WHITE);
    // DrawText(scoreBuffer, position.x, position.y + 25, 20, WHITE);
}

