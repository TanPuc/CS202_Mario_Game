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
#include "Entity.h"
#include "Collision.h"
#include "BrickPieces.h"

// Forward declaration
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

#define TILE_SIZE 16.0f
#define GRID_WIDTH 211
#define GRID_HEIGHT 15

float Q_rsqrt( float number );
bool compare(const std::pair<std::array<int, 2>, float>& a, const std::pair<std::array<int, 2>, float>& b);

enum TileState {
    STATE_NORMAL,
    STATE_ACTIVATED,
    STATE_BROKEN
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
public:
    Rectangle& getBBox() { return bbox; }
    TileState getState() const { return state; }
    Vector2 getPos() const { return pos; }
    TileInstance(Vector2 pos, std::shared_ptr<Tile> tile);
    virtual void update(Mario& player) = 0;
    virtual void render() = 0;
};

class DummyInstance : public TileInstance {
public: 
    DummyInstance(Vector2 pos) : TileInstance ( pos, nullptr ) {}
    void update(Mario& player) override {}
    void render() override {}
};

class GroundInstance : public TileInstance {
public:
    GroundInstance(Vector2 pos, std::shared_ptr<Tile> ground);
    void update(Mario& player) override;
    void render() override;
};

class BrickInstance : public TileInstance {
private:
    Rectangle normal = {0, 0, 16, 16};
    Rectangle dest;
    Rectangle hbox;
    void handleBreaking(Mario& player);
public:
    BrickInstance(Vector2 pos, std::shared_ptr<Tile> brick);
    void update(Mario& player) override;
    void render() override;
};

class QuestionInstance : public TileInstance {
private:
    int frameCounter = 0;
    const int frameSpeed = 12;
    const int frameSpeed2 = 36;
    Rectangle normal = {0, 0, 16, 16};
    Rectangle dest;
    Rectangle hbox;
    void handleAnimation();
    void handleActivation(Mario& player);
public:
    QuestionInstance(Vector2 pos, std::shared_ptr<Tile> question);
    void update(Mario& player) override;
    void render() override;
};

class BackgroundInstance : public TileInstance {
public:
    BackgroundInstance(Vector2 pos, std::shared_ptr<Tile> background);
    void update(Mario& player) override {}
    void render() override;
};

class PipeInstance1 : public TileInstance {
public:
    PipeInstance1(Vector2 pos, std::shared_ptr<Tile> pipe);
    void update(Mario& player) override;
    void render() override;
};
class PipeInstance2 : public TileInstance {
public:
    PipeInstance2(Vector2 pos, std::shared_ptr<Tile> pipe);
    void update(Mario& player) override;
    void render() override;
};
class PipeInstance3 : public TileInstance {
public:
    PipeInstance3(Vector2 pos, std::shared_ptr<Tile> pipe);
    void update(Mario& player) override;
    void render() override;
};

class HardblockInstance : public TileInstance {
public:
    HardblockInstance(Vector2 pos, std::shared_ptr<Tile> hardblock);
    void update(Mario& player) override;
    void render() override;
};

class GoalpoleInstance : public TileInstance {  
public:
    GoalpoleInstance(Vector2 pos, std::shared_ptr<Tile> goalpole);
    void update(Mario& player) override;
    void render() override;
};

class FortressInstance : public TileInstance {
public:
    FortressInstance(Vector2 pos, std::shared_ptr<Tile> fortress);
    void update(Mario& player) override {}
    void render() override;
};

class EntityManager {
public:
    std::vector<std::shared_ptr<BrickPiece>> brickPieces;
    std::vector<int> toRemove;

    void addBrickPieces(Vector2 position);
    void update();
    void render();
};

class TileManager {
public:
    // Flyweight pattern 
    std::map<int, std::shared_ptr<Tile>> tileMap;
    std::vector<std::shared_ptr<TileInstance>> tileInstances; // Store all tile instances 
    std::vector<int> toRemove; // Remove safely while iterating 
    std::shared_ptr<TileInstance> tileInstancesGrid[GRID_HEIGHT][GRID_WIDTH] = { nullptr }; // Fast access to tile instances
    // Managing broken brick pieces 
    EntityManager entityManager;

    TileManager();
    void addTileInstance(Vector2 pos, int tileID, int x, int y);
    void update(Mario& player);
    void render();
};

class Level {
public:
    TileManager tileManager;
    Level(const std::string& fileName);
    void run(Mario& player);
};


#endif // TILE_H