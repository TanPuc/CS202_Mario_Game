#include "DHUD/WorldDisplay.h"
#include "DCore/ResourceManager.h"
#include <string>

WorldDisplay::WorldDisplay(){};

void WorldDisplay::updateWorld(int newWorld, int newLevel)
{
    world = newWorld;
    level = newLevel;
}

void WorldDisplay::draw()
{
    Font font = ResourceManager::GetInstance().GetGameFont();
    float fontSize = 20.0f;
    float spacing = 1.0f;
    DrawTextEx(font, "WORLD", position, fontSize, spacing, WHITE);
    // DrawText("WORLD", position.x, position.y, 20, WHITE);
    std::string text = std::to_string(world) + " - " + std::to_string(level);
    DrawTextEx(font, text.c_str(), {position.x, position.y + 25}, fontSize, spacing, WHITE);
    // DrawText(text.c_str(), position.x + 15, position.y + 25, 20, WHITE);
}
