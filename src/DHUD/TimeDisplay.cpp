#include "DHUD/TimeDisplay.h"
#include <string>

TimeDisplay::TimeDisplay(){};

void TimeDisplay::update()
{
    timer += GetFrameTime();
    if (timer >= 0.4f &&  timeRemaining >0)
    {
        timer = 0.0f;
        timeRemaining--;
    }
}

void TimeDisplay::draw()
{
    DrawText("TIME", position.x, position.y, 20, WHITE);
    std::string text = std::to_string(timeRemaining);
    float textWidth = MeasureText(text.c_str(), 20);
    DrawText(text.c_str(), position.x + 60 - textWidth, position.y + 25, 20, WHITE);
}