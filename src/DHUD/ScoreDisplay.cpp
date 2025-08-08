#include "DHUD/ScoreDisplay.h"

ScoreDisplay::ScoreDisplay() : currentScore(0) {}

void ScoreDisplay::updateScore(long long newScore) 
{
    currentScore = newScore;
}

void ScoreDisplay::draw()
{
    std::string text = "Score: " + std::to_string(currentScore);
    DrawText(text.c_str(), position.x, position.y, 20, BLACK);
}