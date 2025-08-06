#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <raylib.h>
#include <fstream>
#include <sstream>

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
    void Draw(Camera2D &camera) const
    {
        for (int y = 0; y < (int)tiles.size(); y++)
        {
            for (int x = 0; x < (int)tiles[y].size(); x++)
            {
                if (tiles[y][x] > 0)
                {
                    // Rectangle src = {0, 0, TILE_SIZE, TILE_SIZE};
                    // Rectangle dest = {(float)x * TILE_SIZE, (float)y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
                    // DrawTexturePro(tileset, src, dest, {0, 0}, 0.0f, WHITE);
                    DrawTextureEx(tileset, Vector2{(float)x * TILE_SIZE, (float)y * TILE_SIZE}, 0.0f, 2.0f, WHITE); // Draw the tile
                }
            }
        }
    }
    bool CheckCollision(Rectangle hitbox) const
    {
        // Check overlap with solid tiles
        int minX = hitbox.x / TILE_SIZE;
        int maxX = (hitbox.x + hitbox.width) / TILE_SIZE;
        int minY = hitbox.y / TILE_SIZE;
        int maxY = (hitbox.y + hitbox.height) / TILE_SIZE;

        for (int y = minY; y <= maxY; y++)
        {
            for (int x = minX; x <= maxX; x++)
            {
                if (y >= 0 && y < (int)tiles.size() &&
                    x >= 0 && x < (int)tiles[y].size() &&
                    tiles[y][x] > 0)
                {
                    return true;
                }
            }
        }
        return false;
    }
};

#endif // LEVEL_H