#ifndef STATE_H
#define STATE_H

#include <raylib.h>
#include "Entity.h"
#include "Level.h"
#include "GlobalVariables.h"
#include "Sprite.h"
#include <iostream>
#include <memory>

enum Direction
{
    LEFT,
    RIGHT
};

// Forward declarations
class WalkingState;
class JumpingState;

class MarioState
{
public:
    virtual ~MarioState() = default;
    virtual std::unique_ptr<MarioState> HandleInput(Entity &entity) = 0;
    virtual std::unique_ptr<MarioState> Update(Entity &entity) = 0;
    virtual std::unique_ptr<MarioState> Draw(Entity &entity, Sprite &sprite) = 0;
};

// ---------------- Idle MarioState ----------------
class IdleState : public MarioState
{
public:
    std::unique_ptr<MarioState> HandleInput(Entity &entity) override;
    std::unique_ptr<MarioState> Update(Entity &entity) override;
    std::unique_ptr<MarioState> Draw(Entity &entity, Sprite &sprite) override;
};

// ---------------- Walking MarioState ----------------
class WalkingState : public MarioState
{
private:
    Direction direction;
public:
    WalkingState(Direction dir = RIGHT) : direction(dir) {}
    std::unique_ptr<MarioState> HandleInput(Entity &entity) override;
    std::unique_ptr<MarioState> Update(Entity &entity) override;
    std::unique_ptr<MarioState> Draw(Entity &entity, Sprite &sprite) override;
};

// ---------------- Jumping MarioState ----------------
class JumpingState : public MarioState
{
public:
    std::unique_ptr<MarioState> HandleInput(Entity &entity) override;
    std::unique_ptr<MarioState> Update(Entity &entity) override;
    std::unique_ptr<MarioState> Draw(Entity &entity, Sprite &sprite) override;
};

#endif
