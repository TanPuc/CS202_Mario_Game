#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <memory>
#include <map>
#include <raylib.h>
#include "FireBar.h"
#include "GlobalVariables.h"

// Forward declaration
class PlayingState;
class BrickPiece;
class Tile;
class TileInstance;
class PlatformInstance;
class Character;
class ItemManager;
class FortressFlag;

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
    void update(Character &player);
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

    virtual void update(Character &player, ItemManager &itemManager, PlayingState *ps) = 0;
    virtual void render() = 0;

    virtual ~Level() = default;
};

class Level_1_1 : public Level
{
public:
    Level_1_1(const char *filePath, PlayingState *ps);
    void addTileInstance(Vector2 &pos, int &tileID, int &x, int &y, PlayingState *ps);
    void update(Character &player, ItemManager &itemManager, PlayingState *ps) override;
    void render() override;
};

class Level_1_3 : public Level
{
public:
    Level_1_3(const char *filePath, PlayingState *ps);
    void addTileInstance(Vector2 &pos, int &tileID, int &x, int &y, PlayingState *ps);
    void update(Character &player, ItemManager &itemManager, PlayingState *ps) override;
    void render() override;
};

class Level_1_4 : public Level
{
public:
    Level_1_4(const char *filePath, PlayingState *ps);
    void addTileInstance(Vector2 &pos, int &tileID, int &x, int &y, PlayingState *ps);
    void update(Character &player, ItemManager &itemManager, PlayingState *ps) override;
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
#endif // LEVEL_H