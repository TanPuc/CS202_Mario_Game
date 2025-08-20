#include "DHUD/TimeDisplay.h"
#include "DCore/ResourceManager.h"
#include <string>

TimeDisplay::TimeDisplay() {};

void TimeDisplay::reset(int startTime)
{
    timeRemaining = startTime;
    timer = 0.0f;
}
void TimeDisplay::update()
{
    timer += GetFrameTime();
    if (timer >= 1000000.0f && timeRemaining > 0)
    {
        timer = 0.0f;
        timeRemaining--;
    }
}

void TimeDisplay::draw()
{
    Font font = ResourceManager::GetInstance().GetGameFont();
    float fontSize = 20.0f;
    float spacing = 1.0f;

    DrawTextEx(font, "TIME", position, fontSize, spacing, WHITE);
    // DrawText("TIME", position.x, position.y, 20, WHITE);

    std::string text = std::to_string(timeRemaining);
    float textWidth = MeasureText(text.c_str(), 20);
    DrawTextEx(font, text.c_str(), {position.x + 45 - textWidth, position.y + 25}, fontSize, spacing, WHITE);
    // DrawText(text.c_str(), position.x + 45 - textWidth, position.y + 25, 20, WHITE);
}