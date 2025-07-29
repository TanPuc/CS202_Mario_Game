#include "MarioState.h"
#define SPEED 200.0f

// ---------------- IdleState ----------------
std::unique_ptr<MarioState> IdleState::HandleInput(Entity &entity)
{
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT))
    {
        std::cout << "Switching to Walking MarioState" << std::endl;
        entity.velocity.x = (IsKeyDown(KEY_RIGHT) ? SPEED : -SPEED);
        entity.direction = IsKeyDown(KEY_RIGHT) ? RIGHT : LEFT; // Update direction
        std::cout << "Current MarioState: Walking to the " << (entity.direction == RIGHT ? "right" : "left") << std::endl;
        // Switch to WalkingState
        return std::make_unique<WalkingState>();
    }
    else if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP))
    {
        std::cout << "Switching to Jumping MarioState" << std::endl;
        return std::make_unique<JumpingState>();
    }
    return nullptr; // Stay in Idle
}

std::unique_ptr<MarioState> IdleState::Update(Entity &entity)
{
    std::cout << "Current MarioState: Idle" << std::endl;
    return nullptr;
}

std::unique_ptr<MarioState> IdleState::Draw(Entity &entity, Sprite &sprite)
{
    sprite.SwitchAnimation(STATE_IDLE);
    sprite.Draw(entity);
    return nullptr;
}

// ---------------- WalkingState ----------------
std::unique_ptr<MarioState> WalkingState::HandleInput(Entity &entity)
{
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT))
    {
        entity.velocity.x = (IsKeyDown(KEY_RIGHT) ? SPEED : -SPEED);
        entity.direction = IsKeyDown(KEY_RIGHT) ? RIGHT : LEFT; // Update direction
        std::cout << "Current MarioState: Walking to the " << (entity.direction == RIGHT ? "right" : "left") << std::endl;
        return nullptr; // Keep walking
    }
    else if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP))
    {
        std::cout << "Switching to Jumping MarioState" << std::endl;
        return std::make_unique<JumpingState>();
    }
    entity.velocity.x = 0;
    std::cout << "Switching to Idle MarioState" << std::endl;
    return std::make_unique<IdleState>();
}

std::unique_ptr<MarioState> WalkingState::Update(Entity &entity)
{
    std::cout << "Current MarioState: Walking" << std::endl;
    return nullptr;
}

std::unique_ptr<MarioState> WalkingState::Draw(Entity &entity, Sprite &sprite)
{
    sprite.SwitchAnimation(STATE_WALKING); // Update entity direction
    sprite.Draw(entity);
    return nullptr;
}

// ---------------- JumpingState ----------------
std::unique_ptr<MarioState> JumpingState::HandleInput(Entity &entity)
{
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT))
    {
        entity.velocity.x = (IsKeyDown(KEY_RIGHT) ? SPEED : -SPEED);
        entity.direction = IsKeyDown(KEY_RIGHT) ? RIGHT : LEFT; // Update direction
        std::cout << "Current MarioState: Jumping while walking to the " << (entity.direction == RIGHT ? "right" : "left") << std::endl;

        return std::make_unique<WalkingState>();
    }
    else if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP))
    {
        // Already jumping, no change
        return nullptr;
    }
    // No explicit landing transition (handled elsewhere)
    return nullptr;
}

std::unique_ptr<MarioState> JumpingState::Update(Entity &entity)
{
    std::cout << "Current MarioState: Jumping" << std::endl;
    return nullptr;
}

std::unique_ptr<MarioState> JumpingState::Draw(Entity &entity, Sprite &sprite)
{
    sprite.SwitchAnimation(STATE_JUMPING);
    sprite.Draw(entity);
    return nullptr;
}
