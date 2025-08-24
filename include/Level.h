#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <memory>
#include <map>
#include <raylib.h>
#include "FireBar.h"
#include "GlobalVariables.h"

// Forward declaration
class BrickPiece;
class Tile;
class TileInstance;
class Character;

// pipe2: 1
// background: 2
// fortress: 4
// goalpole: 7
// ground: 8
// hardblock: 9
// pipe1: 10
// pipe3: 12
// question: 13
// brick: 17

class EntityManager
{
public:
    std::vector<std::shared_ptr<BrickPiece>> brickPieces;
    std::vector<std::shared_ptr<FireBar>> fireBars;
    std::vector<int> toRemove;

    void addBrickPieces(Vector2 position);
    void addFireBar(Vector2 position, float initial_angle);
    void initFortressFlag(Vector2 position, float fortressWidth);
    void initPlatform();
    void update(Mario &player);
    void render();
    // Need a separate render function for proper displaying 
    void renderFortressFlag(); 
};

class Level
{
public:
    // Flyweight pattern
    std::map<int, std::shared_ptr<Tile>> tileMap;
    std::shared_ptr<TileInstance> tileInstancesGrid[GRID_HEIGHT][GRID_WIDTH] = {nullptr}; // Fast access to tile instances

    // Managing broken brick pieces
    EntityManager entityManager;

    std::shared_ptr<TileInstance> getTileInstance(int x, int y)
    {
        if (x < 0 || x >= tileInstancesGrid.size() || y < 0 || y >= tileInstancesGrid[0].size())
            return nullptr;
        return tileInstancesGrid[x][y];
    }
    int getGridHeight() const { return tileInstancesGrid.size(); }
    int getGridWidth() const { return tileInstancesGrid[0].size(); }

    virtual void update(Mario &player, ItemManager& itemManager ) = 0;
    virtual void render() = 0;
};

class Level_1_1 : public Level
{
public:
    Level_1_1(const char *filePath);
    void addTileInstance(Vector2 &pos, int &tileID, int &x, int &y);
    void update(Mario &player, ItemManager& itemManager) override;
    void render() override;
};

class Level_1_3 : public Level
{
public:
    Level_1_3(const char *filePath);
    void addTileInstance(Vector2 &pos, int &tileID, int &x, int &y);
    void update(Mario &player, ItemManager& itemManager) override;
    void render() override;
};

class Level_1_4 : public Level
{
public:
    Level_1_4(const char *filePath);
    void addTileInstance(Vector2 &pos, int &tileID, int &x, int &y);
    void update(Mario &player, ItemManager& itemManager) override;
    void render() override;
};

// 2: bigfortress
// 3: fortress
// 4: ground
// 5: grassleft
// 6: grassmiddle
// 7: grassright
// 9: hardblock
// 10: goalpole
// 11: grassbrick

// class Level_2 {
// public:
//     std::map<int, std::shared_ptr<Tile>> tileMap;
//     std::shared_ptr<TileInstance> tileInstancesGrid[GRID_HEIGHT][GRID_WIDTH_2] = { nullptr }; // Fast access to tile instances

//     Level_2(const char* filePath);
//     void addTileInstance(Vector2& pos, int& tileID, int& x, int& y);
//     void update(Character& player);
//     void render();
// };

#endif // LEVEL_H