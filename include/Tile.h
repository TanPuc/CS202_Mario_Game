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
#include "FortressFlag.h"

#define HITBOX_WIDTH TILE_SIZE *SCALE / 2 // 16px
#define HITBOX_HEIGHT 6 * SCALE / 2       // 6px

// Forward declaration
class Character;
class PlayingState;

float Q_rsqrt(float number);
bool compare(const std::pair<std::array<int, 2>, float> &a, const std::pair<std::array<int, 2>, float> &b);

class Tile
{
private:
    Texture2D texture;

public:
    // Tile()
    // {
    //     texture = LoadTexture("./assets/Tiles/Overworld.png");
    // }
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
    virtual void update(Character &player, PlayingState *ps) = 0;
    virtual void render() = 0;
};

class DummyInstance : public TileInstance
{
public:
    DummyInstance(Vector2 pos) : TileInstance(pos, nullptr) {}
    void update(Character &player, PlayingState *ps) override {}
    void render() override {}
};

class GroundInstance : public TileInstance
{
public:
    GroundInstance(Vector2 pos, std::shared_ptr<Tile> ground)
        : TileInstance(pos, ground) {}
    void update(Character &player, PlayingState *ps) override {}
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

    void handleAnimation();
    void handleBreaking(Character &player);

public:
    BrickInstance(Vector2 pos, std::shared_ptr<Tile> brick);
    void update(Character &player, PlayingState *ps) override;
    void render() override;
};

class QuestionInstance : public TileInstance
{
private:
    int frameCounter = 0;
    const int frameSpeed = 12;
    const int frameSpeed2 = 36;

    Rectangle hbox;
    Q_B_A q_b_a;

    Rectangle normal = {0, 0, 16, 16};
    Rectangle dest;

    void handleAnimation();
    void handleActivation(Character &player, PlayingState *ps);

public:
    QuestionInstance(Vector2 pos, std::shared_ptr<Tile> question);
    void update(Character &player, PlayingState *ps) override;
    void render() override;
};

class BackgroundInstance : public TileInstance
{
public:
    BackgroundInstance(Vector2 pos, std::shared_ptr<Tile> background);
    void update(Character &player, PlayingState *ps) override {}
    void render() override;
};

class PipeInstance1 : public TileInstance
{
public:
    PipeInstance1(Vector2 pos, std::shared_ptr<Tile> pipe)
        : TileInstance(pos, pipe) {}
    void update(Character &player, PlayingState *ps) override {}
    void render() override;
};
class PipeInstance2 : public TileInstance
{
public:
    PipeInstance2(Vector2 pos, std::shared_ptr<Tile> pipe)
        : TileInstance(pos, pipe) {}
    void update(Character &player, PlayingState *ps) override {}
    void render() override;
};
class PipeInstance3 : public TileInstance
{
public:
    PipeInstance3(Vector2 pos, std::shared_ptr<Tile> pipe)
        : TileInstance(pos, pipe) {}
    void update(Character &player, PlayingState *ps) override {}
    void render() override;
};

class HardblockInstance : public TileInstance
{
public:
    HardblockInstance(Vector2 pos, std::shared_ptr<Tile> hardblock);
    void update(Character &player, PlayingState *ps) override;
    void render() override;
};

class GoalpoleInstance : public TileInstance
{
private:
    Rectangle hbox;
    GoalFlag goalFlag;

public:
    bool isLevelFinished = false; // To indicate if the level is finished
    GoalpoleInstance(Vector2 pos, std::shared_ptr<Tile> goalpole);
    void update(Character &player, PlayingState *ps) override;
    void render() override;
};

class FortressInstance : public TileInstance
{
private:
    Rectangle hbox;
    FortressFlag fortressFlag;

public:
    FortressInstance(Vector2 pos, std::shared_ptr<Tile> fortress)
        : TileInstance(pos, fortress), fortressFlag({pos.x + fortress->getTexture().width * SCALE / 2 - TILE_SIZE * SCALE / 2, pos.y + 16.0f})
    {
        bbox = Rectangle{0, 0, 0, 0};
    }
    void update(Character &player, PlayingState *ps) override;
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
    void update(Character &player, PlayingState *ps) override {}
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
    void update(Character &player, PlayingState *ps) override {}
    void render() override
    {
        DrawTextureEx(tile->getTexture(), pos, 0.0f, SCALE, WHITE);
    }
};

class GrassBrickInstance : public TileInstance
{
public:
    GrassBrickInstance(Vector2 pos, std::shared_ptr<Tile> grass)
        : TileInstance(pos, grass) {}
    void update(Character &player, PlayingState *ps) override {}
    void render() override
    {
        DrawTextureEx(tile->getTexture(), pos, 0.0f, SCALE, WHITE);
    }
};

#endif // TILE_H