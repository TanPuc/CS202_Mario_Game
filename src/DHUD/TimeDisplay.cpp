#include "DHUD/TimeDisplay.h"
#include <string>

TimeDisplay::TimeDisplay(){};

void TimeDisplay::reset(int startTime)
{
    timeRemaining = startTime;
    timer = 0.0f;
}
void TimeDisplay::update()
{
    timer += GetFrameTime();
    if (timer >= 1.0f &&  timeRemaining >0)
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
    DrawText(text.c_str(), position.x + 45 - textWidth, position.y + 25, 20, WHITE);
}