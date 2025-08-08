#include "DHUD/ScoreDisplay.h"
#include <cstdio>
#include <string>

ScoreDisplay::ScoreDisplay() : currentScore(0) {}

void ScoreDisplay::updateScore(long long newScore) 
{
    currentScore = newScore;
}

void ScoreDisplay::draw()
{
    DrawText("SCORE", position.x, position.y, 20, WHITE);

    char scoreBuffer[7]; 
    snprintf(scoreBuffer, sizeof(scoreBuffer), "%06lld", currentScore);
    DrawText(scoreBuffer, position.x, position.y + 25, 20, WHITE);
}

