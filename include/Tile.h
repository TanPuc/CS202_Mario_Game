#ifndef TILE_H
#define TILE_H

#include <fstream>
#include <map>
#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <algorithm>
#include <array>
#include <raylib.h>
#include "GlobalVariables.h"
#include "Entity.h"
#include "Collision.h"
#include "BrickPieces.h"
#include "GoalFlag.h"

// To prevent activating 2 blocks simultaneously when Mario is in the middle of 2 tiles
#define HITBOX_WIDTH 1 * SCALE / 2  // 1px
#define HITBOX_HEIGHT 1 * SCALE / 2 // 1px

// Forward declaration
class Character;

float Q_rsqrt(float number);
bool compare(const std::pair<std::array<int, 2>, float> &a, const std::pair<std::array<int, 2>, float> &b);

class Tile
{
private:
    Texture2D texture;

public:
    Tile(const char *filePath)
    {
        texture = LoadTexture(filePath);
    }
    ~Tile()
    {
        UnloadTexture(texture);
    }

    Texture2D &getTexture()
    {
        return texture;
    }
};

class Q_B_A
{
public:
    float originPosY;
    float velY = 0.0f;
    const float jumpForce = 450.0f;
    const float gravity = 4000.0f;

    Q_B_A(float originPosY) : originPosY(originPosY) {}

    void iniVelY() { velY -= jumpForce; }

    bool is_update(float &posY)
    {
        float et = GetFrameTime();
        velY += gravity * et;
        posY += velY * et;
        if (posY >= originPosY)
        {
            posY = originPosY;
            return false;
        }
        return true;
    }
};

class TileInstance
{
public:
    Vector2 pos;
    Rectangle bbox;
    TileState state = STATE_NORMAL;
    std::shared_ptr<Tile> tile;

    Vector2 getPos() const { return pos; }
    TileState getState() const { return state; }

    TileInstance(Vector2 pos, std::shared_ptr<Tile> tile);
    virtual void update(Character &player) = 0;
    virtual void render() = 0;
};

class DummyInstance : public TileInstance
{
public:
    DummyInstance(Vector2 pos) : TileInstance(pos, nullptr) {}
    void update(Character &player) override {}
    void render() override {}
};

class GroundInstance : public TileInstance
{
public:
    GroundInstance(Vector2 pos, std::shared_ptr<Tile> ground)
        : TileInstance(pos, ground) {}
    void update(Character &player) override {}
    void render() override
    {
        DrawTextureEx(tile->getTexture(), pos, 0.0f, SCALE, WHITE);
    }
};

class BrickInstance : public TileInstance
{
private:
    Rectangle normal = {0, 0, 16, 16};
    Rectangle dest;

    Q_B_A q_b_a;
    Rectangle hbox;
    Rectangle originalBBox;

    void handleAnimation();
    void handleBreaking(Character &player);

public:
    BrickInstance(Vector2 pos, std::shared_ptr<Tile> brick);
    void update(Character &player) override;
    void render() override;

    Rectangle& getOriginalBBox()
    {
        return originalBBox;
    }
};

class QuestionInstance : public TileInstance
{
private:
    int frameCounter = 0;
    const int frameSpeed = 12;
    const int frameSpeed2 = 36;

    bool hasFlower = false;
    bool hasMushroom = false;

    Q_B_A q_b_a;
    Rectangle hbox;
    Rectangle originalBBox;

    Rectangle normal = {0, 0, 16, 16};
    Rectangle dest;

    void handleAnimation();
    void handleActivation(Character &player);

public:
    QuestionInstance(Vector2 pos, std::shared_ptr<Tile> question);
    void update(Character &player) override;
    void render() override;

    void setHasFlower() 
    { 
        hasFlower = true; 
    }
    void setHasMushroom() 
    { 
        hasMushroom = true; 
    }
    Rectangle& getOriginalBBox()
    {
        return originalBBox;
    }
};

class BackgroundInstance : public TileInstance
{
public:
    BackgroundInstance(Vector2 pos, std::shared_ptr<Tile> background);
    void update(Character &player) override {}
    void render() override;
};

class PipeInstance1 : public TileInstance
{
public:
    PipeInstance1(Vector2 pos, std::shared_ptr<Tile> pipe)
        : TileInstance(pos, pipe) {}
    void update(Character &player) override {}
    void render() override;
};
class PipeInstance2 : public TileInstance
{
public:
    PipeInstance2(Vector2 pos, std::shared_ptr<Tile> pipe)
        : TileInstance(pos, pipe) {}
    void update(Character &player) override {}
    void render() override;
};
class PipeInstance3 : public TileInstance
{
public:
    PipeInstance3(Vector2 pos, std::shared_ptr<Tile> pipe)
        : TileInstance(pos, pipe) {}
    void update(Character &player) override {}
    void render() override;
};

class HardblockInstance : public TileInstance
{
public:
    HardblockInstance(Vector2 pos, std::shared_ptr<Tile> hardblock);
    void update(Character &player) override;
    void render() override;
    HardblockInstance(Vector2 pos, std::shared_ptr<Tile> hardblock)
        : TileInstance(pos, hardblock) {}
};

class GoalpoleInstance : public TileInstance
{
private:
    Rectangle hbox;
    GoalFlag goalFlag;
public:
    GoalpoleInstance(Vector2 pos, std::shared_ptr<Tile> goalpole)
        : TileInstance(pos, goalpole), hbox(Rectangle{pos.x, pos.y, TILE_SIZE * SCALE, 11 * TILE_SIZE * SCALE}), goalFlag({pos.x - TILE_SIZE * SCALE / 2, pos.y + 1.0625f * TILE_SIZE * SCALE})
    {
        bbox = Rectangle{0, 0, 0, 0};
    }
    void update(Mario &player, ItemManager& itemManager) override;
    GoalpoleInstance(Vector2 pos, std::shared_ptr<Tile> goalpole);
    void update(Character &player) override;
    void render() override;
};

class FortressInstance : public TileInstance
{
private:
    Rectangle hbox;

public:
    FortressInstance(Vector2 pos, std::shared_ptr<Tile> fortress)
        : TileInstance(pos, fortress)
    {
        bbox = Rectangle{0, 0, 0, 0};
    }
    void update(Character &player) override;
    void render() override;
};

class BigFortressInstance : public TileInstance
{
public:
    BigFortressInstance(Vector2 pos, std::shared_ptr<Tile> bigfortress)
        : TileInstance(pos, bigfortress)
    {
        bbox = Rectangle{0, 0, 0, 0};
    }
    void update(Character &player) override {}
    void render() override
    {
        DrawTextureEx(tile->getTexture(), pos, 0.0f, SCALE, WHITE);
    }
};

class GrassInstance : public TileInstance
{
public:
    GrassInstance(Vector2 pos, std::shared_ptr<Tile> grass)
        : TileInstance(pos, grass) {}
    void update(Character &player) override {}
    void render() override
    {
        DrawTextureEx(tile->getTexture(), pos, 0.0f, SCALE, WHITE);
    }
};

class GrassBrickInstance : public TileInstance
{
public:
    GrassBrickInstance(Vector2 pos, std::shared_ptr<Tile> grass)
        : TileInstance(pos, grass) 
    {
        bbox = Rectangle{0, 0, 0, 0};  
    }
        : TileInstance(pos, grass) {}
    void update(Character &player) override {}
    void render() override
    {
        DrawTextureEx(tile->getTexture(), pos, 0.0f, SCALE, WHITE);
    }
};

class PlatformInstance : public TileInstance
{
public:
    std::shared_ptr<Vector2> topPos = nullptr;
    std::shared_ptr<Vector2> bottomPos = nullptr;
    std::shared_ptr<Vector2> leftPos = nullptr;
    std::shared_ptr<Vector2> rightPos = nullptr;
    // Vector2 velocity = {0.0f, 100.0f};

    PlatformInstance(Vector2 pos_1, Vector2 pos_2, std::shared_ptr<Tile> platform, int direction);
    void render() override
    {
        DrawTextureEx(tile->getTexture(), pos, 0.0f, SCALE, WHITE);
        DrawRectangleLinesEx(bbox, 2.0f, RED); // Draw bounding box
    }
    void update(Mario &player, ItemManager& itemManager) override
    {
    }
};

class LavaSurfaceInstance : public TileInstance
{
public:
    Rectangle hbox;
    LavaSurfaceInstance(Vector2 pos, std::shared_ptr<Tile> lavaSurface)
        : TileInstance(pos, lavaSurface), hbox({pos.x, pos.y + 0.25f * TILE_SIZE * SCALE, TILE_SIZE * SCALE, 0.75f * TILE_SIZE * SCALE})
    {
        bbox = Rectangle{0, 0, 0, 0};
    }
    void update(Mario &player, ItemManager& itemManager) override;
    void render() override;
};

class UsedBlockInstance : public TileInstance
{
public:
    UsedBlockInstance(Vector2 pos, std::shared_ptr<Tile> usedBlock)
        : TileInstance(pos, usedBlock) {}
};

    {
        bbox = Rectangle{0, 0, 0, 0};
    }
    void update(Mario &player) override;
    void render() override;
};

class UsedBlockInstance : public TileInstance
{
public:
    UsedBlockInstance(Vector2 pos, std::shared_ptr<Tile> usedBlock)
        : TileInstance(pos, usedBlock) {}
    void update(Mario &player) override {}
};

#endif // TILE_H