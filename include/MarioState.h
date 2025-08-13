#ifndef STATE_H
#define STATE_H

#include <raylib.h>
#include "Entity.h"
#include "Level.h"
#include "GlobalVariables.h"
#include "Physics.h"
#include "sprite/MarioSprite.h"
#include <iostream>
#include <memory>

// Forward declarations
class WalkingState;
class JumpingState;

class MarioState
{
public:
    virtual ~MarioState() = default;
    virtual std::unique_ptr<MarioState> HandleInput(Entity &entity, Sprite &sprite) = 0;
    virtual std::unique_ptr<MarioState> Update(Entity &entity, Sprite &sprite) = 0;
    virtual void Draw(Entity &entity, Sprite &sprite) = 0;
    virtual STATE GetType() const = 0; // To get the current state type
};

// ---------------- Idle MarioState ----------------
class IdleState : public MarioState
{
public:
    std::unique_ptr<MarioState> HandleInput(Entity &entity, Sprite &sprite) override;
    std::unique_ptr<MarioState> Update(Entity &entity, Sprite &sprite) override;
    void Draw(Entity &entity, Sprite &sprite) override;
    STATE GetType() const override { return STATE_IDLE; } // Return the current state type
};

// ---------------- Walking MarioState ----------------
class WalkingState : public MarioState
{
public:
    std::unique_ptr<MarioState> HandleInput(Entity &entity, Sprite &sprite) override;
    std::unique_ptr<MarioState> Update(Entity &entity, Sprite &sprite) override;
    void Draw(Entity &entity, Sprite &sprite) override;
    STATE GetType() const override { return STATE_WALKING; } // Return the current state type
};

// ---------------- Jumping MarioState ----------------
class JumpingState : public MarioState
{
public:
    std::unique_ptr<MarioState> HandleInput(Entity &entity, Sprite &sprite) override;
    std::unique_ptr<MarioState> Update(Entity &entity, Sprite &sprite) override;
    void Draw(Entity &entity, Sprite &sprite) override;
    STATE GetType() const override { return STATE_JUMPING; } // Return the current state type
};

#endif
