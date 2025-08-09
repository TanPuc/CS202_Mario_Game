#ifndef TILE_H
#define TILE_H
// #pragma once

#include <fstream>
#include <map>
#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Mario.h"
#include "raylib.h"

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

#define TILE_SIZE 16.0f
#define SCALE 4.0f
const float scale = 4.0f;
const int gridWidth = 211;
const int gridHeight = 15;

enum TileState {
    STATE_NORMAL,
    STATE_ACTIVATED
};

class Tile {
protected:
    Texture2D texture;
public:
    Texture2D& getTexture() { return texture; }
    virtual ~Tile() { UnloadTexture(texture); }
};

class Ground : public Tile {
public:
    Ground() { texture = LoadTexture("./assets/tiles/ground.png"); }
};

class Brick : public Tile {
public:
    Brick() { texture = LoadTexture("./assets/tiles/brick.png"); }
};

class Question : public Tile {
public:
    Question() { texture = LoadTexture("./assets/tiles/question.png"); }
};

class Background : public Tile {
public:
    Background() { texture = LoadTexture("./assets/tiles/background.png"); }
};

class Pipe1 : public Tile {
public:
    Pipe1() { texture = LoadTexture("./assets/tiles/pipe1.png"); }
};
class Pipe2 : public Tile {
public:
    Pipe2() { texture = LoadTexture("./assets/tiles/pipe2.png"); }
};
class Pipe3 : public Tile {
public:
    Pipe3() { texture = LoadTexture("./assets/tiles/pipe3.png"); }
};

class Hardblock : public Tile {
public:
    Hardblock() { texture = LoadTexture("./assets/tiles/hardblock.png"); }
};

class Goalpole : public Tile {
public:
    Goalpole() { texture = LoadTexture("./assets/tiles/goalpole.png"); }
};

class Fortress : public Tile {
public:
    Fortress() { texture = LoadTexture("./assets/tiles/fortress.png"); }
};

class TileInstance {
protected:
    Vector2 pos;
    Rectangle bbox;
    std::shared_ptr<Tile> tile;
    TileState state = STATE_NORMAL;
    Rectangle normal = {0, 0, 16, 16};
    Rectangle dest = {0, 0, 16 * scale, 16 * scale};
public:
    Rectangle getBBox() const { return bbox; }
    TileInstance(Vector2 pos, std::shared_ptr<Tile> tile);
    virtual void handleCollision( Mario& player ) = 0;
    virtual void render() = 0;
};

class GroundInstance : public TileInstance {
public:
    GroundInstance(Vector2 pos, std::shared_ptr<Tile> ground);
    void handleCollision(Mario& player) override;
    void render() override;
};

class BrickInstance : public TileInstance {
public:
    BrickInstance(Vector2 pos, std::shared_ptr<Tile> brick);
    void handleCollision(Mario& player) override;
    void render() override;
};

class QuestionInstance : public TileInstance {
private:
    int frameCounter = 0;
    const int frameSpeed = 12;
    const int frameSpeed2 = 36;
public:
    QuestionInstance(Vector2 pos, std::shared_ptr<Tile> question);
    void handleCollision(Mario& player) override;
    void render() override;
};

class BackgroundInstance : public TileInstance {
public:
    BackgroundInstance(Vector2 pos, std::shared_ptr<Tile> background);
    void handleCollision(Mario& player) override {}
    void render() override;
};

class PipeInstance1 : public TileInstance {
public:
    PipeInstance1(Vector2 pos, std::shared_ptr<Tile> pipe);
    void handleCollision(Mario& player) override;
    void render() override;
};
class PipeInstance2 : public TileInstance {
public:
    PipeInstance2(Vector2 pos, std::shared_ptr<Tile> pipe);
    void handleCollision(Mario& player) override;
    void render() override;
};
class PipeInstance3 : public TileInstance {
public:
    PipeInstance3(Vector2 pos, std::shared_ptr<Tile> pipe);
    void handleCollision(Mario& player) override;
    void render() override;
};

class HardblockInstance : public TileInstance {
public:
    HardblockInstance(Vector2 pos, std::shared_ptr<Tile> hardblock);
    void handleCollision(Mario& player) override;
    void render() override;
};

class GoalpoleInstance : public TileInstance {  
public:
    GoalpoleInstance(Vector2 pos, std::shared_ptr<Tile> goalpole);
    void handleCollision(Mario& player) override {}
    void render() override;
};

class FortressInstance : public TileInstance {
public:
    FortressInstance(Vector2 pos, std::shared_ptr<Tile> fortress);
    void handleCollision(Mario& player) override {}
    void render() override;
};

class TileManager {
private:
    // Flyweight pattern 
    std::shared_ptr<Tile> fortress = std::make_shared<Fortress>();
    std::shared_ptr<Tile> goalpole = std::make_shared<Goalpole>();
    std::shared_ptr<Tile> hardblock = std::make_shared<Hardblock>();
    std::shared_ptr<Tile> pipe1 = std::make_shared<Pipe1>();
    std::shared_ptr<Tile> pipe2 = std::make_shared<Pipe2>();
    std::shared_ptr<Tile> pipe3 = std::make_shared<Pipe3>();
    std::shared_ptr<Tile> background = std::make_shared<Background>();
    std::shared_ptr<Tile> question = std::make_shared<Question>();
    std::shared_ptr<Tile> brick = std::make_shared<Brick>();
    std::shared_ptr<Tile> ground = std::make_shared<Ground>();
    std::vector<std::shared_ptr<TileInstance>> tileInstances;
public:
    std::shared_ptr<TileInstance> addTileInstance(Vector2 pos, int tileID);
    void handleCollision(Mario& player);
    void render();
};

class World1_1 {
private:
    TileManager tileManager;
    int grid[gridHeight][gridWidth];
public:
    World1_1(const std::string& fileName);
    void update( Mario& player );
    void render();
};


#endif // TILE_H