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

class State
{
public:
    virtual ~State() = default;
    virtual std::unique_ptr<State> HandleInput(Entity &entity) = 0;
    virtual std::unique_ptr<State> Update(Entity &entity) = 0;
    virtual std::unique_ptr<State> Draw(Entity &entity, Sprite &sprite) = 0;
};

// ---------------- Idle State ----------------
class IdleState : public State
{
public:
    std::unique_ptr<State> HandleInput(Entity &entity) override;
    std::unique_ptr<State> Update(Entity &entity) override;
    std::unique_ptr<State> Draw(Entity &entity, Sprite &sprite) override;
};

// ---------------- Walking State ----------------
class WalkingState : public State
{
private:
    Direction direction;
public:
    WalkingState(Direction dir = RIGHT) : direction(dir) {}
    std::unique_ptr<State> HandleInput(Entity &entity) override;
    std::unique_ptr<State> Update(Entity &entity) override;
    std::unique_ptr<State> Draw(Entity &entity, Sprite &sprite) override;
};

// ---------------- Jumping State ----------------
class JumpingState : public State
{
public:
    std::unique_ptr<State> HandleInput(Entity &entity) override;
    std::unique_ptr<State> Update(Entity &entity) override;
    std::unique_ptr<State> Draw(Entity &entity, Sprite &sprite) override;
};

#endif
