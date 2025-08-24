#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <memory>
#include <map>
#include <raylib.h>
#include "FireBar.h"
#include "GlobalVariables.h"

// Forward declaration
class PlatformInstance;
class BrickPiece;
class FortressFlag;
class Tile;
class TileInstance;
class Mario;
class ItemManager;

class EntityManager
{
public:
    std::shared_ptr<FortressFlag> fortressFlag;
    std::vector<std::shared_ptr<PlatformInstance>> platforms;
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

typedef std::vector<std::vector<std::shared_ptr<TileInstance>>> TileInstancesGrid;

class Level
{
public:
    std::map<int, std::shared_ptr<Tile>> tileMap;
    TileInstancesGrid tileInstancesGrid;
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

class LevelFactory
{
public:
    std::shared_ptr<Level> level;
    void createLevel(const std::string &id, const char *filePath)
    {
        // if ( id == "1.1" )
        // {
        //     level = std::make_shared<Level_1_1>(filePath);
        // }
        // else if ( id == "1.3" )
        // {
        //     level = std::make_shared<Level_1_3>(filePath);
        // }
        // else if ( id == "1.4" )
        // {
        //     level = std::make_shared<Level_1_4>(filePath);
        // }
    }
};

// Level 1.1
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

// Level 1.3
// 2: bigfortress
// 3: fortress
// 4: ground
// 5: grassleft
// 6: grassmiddle
// 7: grassright
// 9: hardblock
// 10: goalpole
// 11: grassbrick
// 12: background_3
// 13: question

// Level 1.4
// 3: lava
// 4: lava_surface // Special
// 5: axe
// 7: question // Got
// 8: used_block // Special
// 9: castle_brick
// 10: bridge
// 11: chain

#endif // LEVEL_H