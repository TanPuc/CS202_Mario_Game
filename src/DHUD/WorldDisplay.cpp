#include "DHUD/WorldDisplay.h"
#include <string>

WorldDisplay::WorldDisplay(){};

void WorldDisplay::updateWorld(int newWorld, int newLevel)
{
    world = newWorld;
    level = newLevel;
}

void WorldDisplay::draw()
{
    DrawText("WORLD", position.x, position.y, 20, WHITE);
    std::string text = std::to_string(world) + " - " + std::to_string(level);
    DrawText(text.c_str(), position.x + 15, position.y + 25, 20, WHITE);
}
