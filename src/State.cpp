#include "State.h"
#define SPEED 200.0f

// ---------------- IdleState ----------------
std::unique_ptr<State> IdleState::HandleInput(Entity &entity)
{
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT))
    {
        std::cout << "Switching to Walking State" << std::endl;
        return std::make_unique<WalkingState>(IsKeyDown(KEY_RIGHT) ? RIGHT : LEFT);
    }
    else if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP))
    {
        std::cout << "Switching to Jumping State" << std::endl;
        return std::make_unique<JumpingState>();
    }
    return nullptr; // Stay in Idle
}

std::unique_ptr<State> IdleState::Update(Entity &entity)
{
    std::cout << "Current State: Idle" << std::endl;
    return nullptr;
}

std::unique_ptr<State> IdleState::Draw(Entity &entity, Sprite &sprite)
{
    sprite.Draw(entity, STATE_IDLE);
    return nullptr;
}

// ---------------- WalkingState ----------------
std::unique_ptr<State> WalkingState::HandleInput(Entity &entity)
{
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT))
    {
        entity.velocity.x = (IsKeyDown(KEY_RIGHT) ? SPEED : -SPEED);
        return nullptr; // Keep walking
    }
    else if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP))
    {
        std::cout << "Switching to Jumping State" << std::endl;
        return std::make_unique<JumpingState>();
    }
    entity.velocity.x = 0;
    std::cout << "Switching to Idle State" << std::endl;
    return std::make_unique<IdleState>();
}

std::unique_ptr<State> WalkingState::Update(Entity &entity)
{
    std::cout << "Current State: Walking" << std::endl;
    return nullptr;
}

std::unique_ptr<State> WalkingState::Draw(Entity &entity, Sprite &sprite)
{
    sprite.Draw(entity, STATE_WALKING);
    return nullptr;
}

// ---------------- JumpingState ----------------
std::unique_ptr<State> JumpingState::HandleInput(Entity &entity)
{
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT))
    {
        entity.velocity.x = (IsKeyDown(KEY_RIGHT) ? SPEED : -SPEED);
        std::cout << "Switching to Walking State" << std::endl;
        return std::make_unique<WalkingState>(IsKeyDown(KEY_RIGHT) ? RIGHT : LEFT);
    }
    else if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP))
    {
        // Already jumping, no change
        return nullptr;
    }
    // No explicit landing transition (handled elsewhere)
    return nullptr;
}

std::unique_ptr<State> JumpingState::Update(Entity &entity)
{
    std::cout << "Current State: Jumping" << std::endl;
    return nullptr;
}

std::unique_ptr<State> JumpingState::Draw(Entity &entity, Sprite &sprite)
{
    sprite.Draw(entity, STATE_JUMPING);
    return nullptr;
}
