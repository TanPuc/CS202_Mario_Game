#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <raylib.h>
#include <fstream>
#include <sstream>
#include <iostream>

#define TILE_SIZE 32.0f // Size of each tile in pixels

class Level
{
public:
    std::vector<std::vector<int>> tiles;
    Texture2D tileset;

    Level()
    {
        tileset = LoadTexture("assets/brick.png");
    }

    ~Level()
    {
        UnloadTexture(tileset);
    }

    bool LoadFromFile(const std::string &mapFile)
    {
        std::ifstream file(mapFile);
        if (!file.is_open())
            return false;

        tiles.clear();
        std::string line;
        while (std::getline(file, line))
        {
            std::istringstream ss(line);
            int tile;
            std::vector<int> row;
            while (ss >> tile)
                row.push_back(tile);
            tiles.push_back(row);
        }
        return true;
    }
    void Draw() const
    {
        for (int y = 0; y < tiles.size(); y++)
        {
            for (int x = 0; x < tiles[y].size(); x++)
            {
                if (tiles[y][x] > 0)
                {
                    DrawTextureEx(tileset, Vector2({(float)x * TILE_SIZE, (float)y * TILE_SIZE}), 0.0f, 2.0f, WHITE); // Draw the tile
                    DrawRectangleLines(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, RED);                      // Draw hitbox for debugging
                }
            }
        }
    }
    bool CheckCollision(Rectangle hitbox) const
    {
        // Check overlap with solid tiles
        int minX = floor(hitbox.x / TILE_SIZE);
        int maxX = floor((hitbox.x + hitbox.width) / TILE_SIZE);
        int minY = floor(hitbox.y / TILE_SIZE);
        int maxY = floor((hitbox.y + hitbox.height) / TILE_SIZE);

        for (int y = minY; y <= maxY; y++)
        {
            for (int x = minX; x <= maxX; x++)
            {
                Rectangle rect = {float(x * TILE_SIZE), float(y * TILE_SIZE), float(TILE_SIZE), float(TILE_SIZE)};
                if (CheckCollisionRecs(hitbox, rect) && tiles[y][x] > 0) // Check if the tile is solid
                {
                    std::cout << "Collision detected at tile (" << x << ", " << y << ")" << std::endl;
                    return true;
                }
            }
        }
        return false;
    }
};

#endif // LEVEL_H