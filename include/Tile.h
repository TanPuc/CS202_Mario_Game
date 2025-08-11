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
#include "Entity.h"
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
#define GRID_WIDTH 211
#define GRID_HEIGHT 15

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
    bool isDestroyed = false;
    Vector2 pos;
    Rectangle bbox;
    std::shared_ptr<Tile> tile;
    TileState state = STATE_NORMAL;
    Rectangle normal = {0, 0, 16, 16};
    Rectangle dest = {0, 0, 16 * scale, 16 * scale};
    void handleCollision( Mario& player );
public:
    Rectangle getBBox() const { return bbox; }
    TileState getState() const { return state; }
    Vector2 getPos() const { return pos; }
    TileInstance(Vector2 pos, std::shared_ptr<Tile> tile);
    virtual void update(Mario& player) = 0;
    virtual void render() = 0;
};

class GroundInstance : public TileInstance {
public:
    GroundInstance(Vector2 pos, std::shared_ptr<Tile> ground);
    void update(Mario& player) override;
    void render() override;
};

class BrickInstance : public TileInstance {
private:
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
    void update(Mario& player) override;
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

class BrickPiece : public Entity {
private:
    int frameCounter = 0;
    const int frameSpeed = 12;
    const float gravity = 1000.0f;
    Rectangle source; 
    Vector2 velocity;
public:
    BrickPiece ( char const *filePath, Vector2 position, Vector2 size, Rectangle source, Vector2 velocity )
        : Entity(filePath, position, size), source(source), velocity(velocity) {}
    void Update() override {
        // Position 
        float deltaTime = GetFrameTime();
        velocity.y += gravity * deltaTime;
        position.x += velocity.x * deltaTime;
        position.y += velocity.y * deltaTime;

        // Animation 
        frameCounter++;
        if (frameCounter >= frameSpeed) {
            frameCounter = 0;
            source.x += 8;
            if (source.x > 24) source.x = 16;
        }

        // IsOutOfBound
        if ( position.y > screenHeight * scale ) isOutOfScreen = true;
    }
    void Draw() {
        rect.x = position.x; rect.y = position.y;
        DrawTexturePro(texture, source, rect, Vector2{0, 0}, 0.0f, WHITE);
    }

};

// class Test {
//     void a() {
//         std::shared_ptr<Entity> brickPiece1 = std::make_shared<BrickPiece>("./assets/tiles/brick.png", Vector2{position.x, position.y}, Vector2{32, 32}, Rectangle{16, 0, 8, 8}, Vector2{-50, -50});
//         std::shared_ptr<Entity> brickPiece2 = std::make_shared<BrickPiece>("./assets/tiles/brick.png", Vector2{position.x + 32, position.y}, Vector2{32, 32}, Rectangle{24, 0, 8, 8}, Vector2{50, -50});
//         std::shared_ptr<Entity> brickPiece3 = std::make_shared<BrickPiece>("./assets/tiles/brick.png", Vector2{position.x, position.y + 32}, Vector2{32, 32}, Rectangle{16, 8, 8, 8}, Vector2{-50, 50});
//         std::shared_ptr<Entity> brickPiece4 = std::make_shared<BrickPiece>("./assets/tiles/brick.png", Vector2{position.x + 32, position.y + 32}, Vector2{32, 32}, Rectangle{24, 8, 8, 8}, Vector2{50, 50});
//         brickPieces.push_back(brickPiece1);
//         brickPieces.push_back(brickPiece2);
//         brickPieces.push_back(brickPiece3);
//         brickPieces.push_back(brickPiece4);
//         for ( const auto& brickPiece : brickPieces ) {
//             brickPiece->Update();
//             brickPiece->Draw();
//         }   
//     }
// };

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
    std::vector<int> toRemoveTiles; // Remove safely while iterating 
    std::vector<std::shared_ptr<Entity>> brickPieces; // Broken brick entities 
    std::vector<int> toRemoveEntities;
    void handleBrickPieces(Vector2 position);
    // std::shared_ptr<TileInstance> gridMap[GRID_HEIGHT][GRID_WIDTH];
public:
    std::shared_ptr<TileInstance> addTileInstance(Vector2 pos, int tileID);
    void update(Mario& player);
    void render();
};

class World1_1 {
private:
    TileManager tileManager;
    int grid[GRID_HEIGHT][GRID_WIDTH];
public:
    World1_1(const std::string& fileName);
    void update(Mario& player);
    void render();
};


#endif // TILE_H