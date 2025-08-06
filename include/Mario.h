#ifndef MARIO_H
#define MARIO_H

#include <raylib.h>
#include "Entity.h"
#include "Physics.h"
#include "Level.h"
#include "MarioState.h"
#include <iostream>
#include "Sprite.h"
#include "GlobalVariables.h"

class Mario : public Entity
{
public:
    std::unique_ptr<MarioState> currentState = std::make_unique<IdleState>();
    // STATE currentState = STATE_IDLE; // Current state of Mario
    Sprite MarioSprite;

    Mario(Texture texture, Vector2 position) : Entity(texture, position) {}

    void HandleInput()
    {
        std::unique_ptr<MarioState> newState = currentState->HandleInput(*this, MarioSprite);
        if (newState != nullptr)
        {
            currentState = std::move(newState);
            MarioSprite.SwitchAnimation(currentState->GetType());
        }
    }

    void Draw() override
    {
        DrawRectangleLines(rect.x, rect.y, rect.width, rect.height, RED); // Draw hitbox for debugging
        currentState->Draw(*this, MarioSprite);
    }

    void Update() override
    {
    }

    void Update(Level &level)
    {
        std::unique_ptr<MarioState> newState = currentState->Update(*this, MarioSprite);
        if (newState != nullptr)
        {
            currentState = std::move(newState);
            MarioSprite.SwitchAnimation(currentState->GetType());
        }
        float gravity = 800.0f;
        float dt = GetFrameTime();
        ApplyGravity(velocity, gravity);
        position.x += velocity.x * dt;
        position.y += velocity.y * dt;

        if (CheckCollision(*this, level)) // Resolve collision
        {
            // ResolveCollision(level);
            position.y = (int)(position.y / 32) * 32; // Snap to tile grid
            velocity.y = 0;
        }
        rect.x = position.x;
        rect.y = position.y;
    }

    void ResolveCollision(Level &level) override {
    };

    void ResolveCollision(Entity &other) override
    {
        // Handle collision with other entities if needed
        std::cout << "Collision with another entity detected!" << std::endl;
    }
};

#endif