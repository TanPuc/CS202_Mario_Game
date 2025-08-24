#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <memory>
#include <map>
#include <raylib.h>
#include "GlobalVariables.h"

// Forward declaration
class PlayingState;
class BrickPiece;
class Tile;
class TileInstance;
class Mario;

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
    std::vector<int> toRemove;

    void addBrickPieces(Vector2 position);
    void update();
    void render();
};

class Level
{
public:
    // Flyweight pattern
    std::map<int, std::shared_ptr<Tile>> tileMap;
    std::shared_ptr<TileInstance> tileInstancesGrid[GRID_HEIGHT][GRID_WIDTH] = {nullptr}; // Fast access to tile instances

    // Managing broken brick pieces
    EntityManager entityManager;

    Level(const char *filePath, PlayingState* ps);
    void addTileInstance(Vector2 pos, int tileID, int x, int y, PlayingState* ps);
    void update(Mario &player, PlayingState* ps);
    void render();
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
//     void update(Mario& player);
//     void render();
// };

#endif // LEVEL_H