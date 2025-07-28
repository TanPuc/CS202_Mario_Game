#ifndef MARIO_H
#define MARIO_H

#include <raylib.h>
#include "Entity.h"
#include "Physics.h"
#include "Level.h"
#include "State.h"
#include <iostream>
#include "Sprite.h"

class Mario : public Entity
{
public:
    std::unique_ptr<State> currentState = std::make_unique<IdleState>();
    Sprite MarioSprite;

    Mario(Texture texture, Vector2 position) : Entity(texture, position) {}

    void HandleInput()
    {
    std::unique_ptr<State> newState = currentState->HandleInput(*this);
        if (newState != nullptr)
            currentState = std::move(newState);
    }

    void Draw() override
    {
        std::unique_ptr<State> newState = currentState->Draw(*this, MarioSprite);
        if (newState != nullptr)
            currentState = std::move(newState);
    }

    void Update() override
    {}

    void Update(Level &level)
    {
        float dt = GetFrameTime();
        float gravity = GRAVITY;
        ApplyGravity(velocity, gravity);
        position.x += velocity.x * dt;
        position.y += velocity.y * dt;
        rect.x = position.x;
        rect.y = position.y;

        // Check for collisions with the level
        Vector2 collisionPoint;
        if (CheckCollision(*this, level, collisionPoint))
        {
            OnCollision(level, collisionPoint);
        }
    }

    void OnCollision(Level &level, Vector2 collisionPoint)
    {
        float overlapX = 0;
        float overlapY = 0;
        if (rect.x + rect.width > rect.x && rect.x < rect.x + rect.width)
            overlapX = std::min(rect.x + rect.width - rect.x, rect.x + rect.width - rect.x);

        if (rect.y + rect.height > rect.y && rect.y < rect.y + rect.height)
            overlapY = std::min(rect.y + rect.height - rect.y, rect.y + rect.height - rect.y);

        std::cout << "Collision detected at tile (" << collisionPoint.x << ", " << collisionPoint.y << ")" << std::endl;
        std::cout << overlapX << " " << overlapY << std::endl;

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
    void OnCollision(Entity &other) override
    {
        // Handle collision with other entities if needed
        std::cout << "Collision with another entity detected!" << std::endl;
    }
    void OnCollision(Level &level) override
    {
        // Handle collision with the level
        std::cout << "Collision with level detected!" << std::endl;
    }

};

#endif