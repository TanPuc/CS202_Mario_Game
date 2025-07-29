#ifndef MARIO_H
#define MARIO_H

#include <raylib.h>
#include "Entity.h"
#include "Physics.h"
#include "Level.h"
#include "MarioState.h"
#include <iostream>
#include "Sprite.h"

class Mario : public Entity
{
public:
    std::unique_ptr<MarioState> currentState = std::make_unique<IdleState>();
    Sprite MarioSprite;

    Mario(Texture texture, Vector2 position) : Entity(texture, position) {}

    void HandleInput()
    {
        std::unique_ptr<MarioState> newState = currentState->HandleInput(*this);
        if (newState != nullptr)
            currentState = std::move(newState);
    }

    void Draw() override
    {
        DrawRectangleLines(rect.x, rect.y, rect.width, rect.height, RED); // Draw hitbox for debugging
        std::unique_ptr<MarioState> newState = currentState->Draw(*this, MarioSprite);
        if (newState != nullptr)
            currentState = std::move(newState);
    }

    void Update() override
    {
        std::unique_ptr<MarioState> newState = currentState->Update(*this);
        if (newState != nullptr)
            currentState = std::move(newState);

        // Update the entity's position and rectangle
        float dt = GetFrameTime();
        position.x += velocity.x * dt;
        position.y += velocity.y * dt;
        // Round the position to avoid sub-pixel rendering issues
        position.x = roundf(position.x);
        position.y = roundf(position.y);
        rect.x = position.x;
        rect.y = position.y;
    }

    void Update(Level &level)
    {
    //     std::unique_ptr<MarioState> newState = currentState->Update(*this);
    //     if (newState != nullptr)
    //         currentState = std::move(newState);

        // Update the entity's position and rectangle
        float gravity = 800.0f;
        float dt = GetFrameTime();
        // ApplyGravity(velocity, gravity);
        position.x += velocity.x * dt;
        position.y += velocity.y * dt;
        // Round the position to avoid sub-pixel rendering issues
        position.x = roundf(position.x);
        position.y = roundf(position.y);

        if (CheckCollision(*this, level)) // Resolve collision
        {
            ResolveCollision(level);
        }

        rect.x = position.x;
        rect.y = position.y;
    }

    void ResolveCollision(Level &level) override
    {
        float overlapX = 0;
        float overlapY = 0;
        if (rect.x + rect.width > rect.x && rect.x < rect.x + rect.width)
            overlapX = std::min(rect.x + rect.width - rect.x, rect.x + rect.width - rect.x);

        if (rect.y + rect.height > rect.y && rect.y < rect.y + rect.height)
            overlapY = std::min(rect.y + rect.height - rect.y, rect.y + rect.height - rect.y);

        if (overlapX <= overlapY)
        {
            if (rect.x < rect.x)
            {
                position.x -= overlapX;
                velocity.x = 0;
            }
            else
            {
                position.x += overlapX;
                velocity.x = 0;
            }
        }
        else
        {
            velocity.y = 0;
            position.y = int((position.y / 32) * 32);
        }
    };
    void ResolveCollision(Entity &other) override
    {
        // Handle collision with other entities if needed
        std::cout << "Collision with another entity detected!" << std::endl;
    }
};

#endif