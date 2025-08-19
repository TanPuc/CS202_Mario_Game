#ifndef MARIO_H
#define MARIO_H

#include <iostream>
#include <raylib.h>
#include <array>
#include <cmath>
#include "GlobalVariables.h"
#include "Entity.h"
#include "MarioState.h"
#include "GameSprite/MarioSprite.h"

class Mario : public Entity
{
public:
    std::unique_ptr<MarioState> currentState = std::make_unique<IdleState>();
    std::unique_ptr<MarioSprite> sprite;
    MARIO_FORM form;
    // std::vector<std::shared_ptr<FireBall>> fireballs;
    int lives;
    int coins;
    long long score;

    Mario(Vector2 position) : Entity(position, Vector2({MARIO_WIDTH, MARIO_HEIGHT})), form(SMALL)
    {
        rect = {position.x, position.y, MARIO_WIDTH, MARIO_HEIGHT};
        sprite = std::make_unique<MarioSprite>();
    }

    void Die()
    {
        lives--;
    }

    void Grow()
    {
        if (form != SMALL)
            return;
        form = BIG;
        rect.height = MARIO_HEIGHT * 2.0f;

        sprite->SwitchForm(form);
    }

    void ChangeToFire()
    {
        if (form != BIG)
            return;
        form = FIRE;
        rect.height = MARIO_HEIGHT * 2.0f;

        sprite->SwitchForm(form);
    }

    void ChangeToSuper()
    {
        if (form != BIG)
            return;
        form = SUPER;
        rect.height = MARIO_HEIGHT * 2.0f;

        sprite->SwitchForm(form);
    }

    void Shrink()
    {
        if (form == SMALL)
            return;
        form = SMALL;
        rect.height = MARIO_HEIGHT;

        sprite->SwitchForm(form);
    }

    void ChangeForm()
    {
        if (IsKeyPressed(KEY_F))
        {
            if (form == SMALL)
            {
                form = BIG;
                rect.height = MARIO_HEIGHT * 2.0f; // Increase height for big Mario
            }
            else if (form == BIG)
            {
                form = FIRE;
                rect.height = MARIO_HEIGHT * 2.0f; // Keep the same size for fire Mario
            }
            else if (form == FIRE)
            {
                form = SMALL;               // Reset to small Mario
                rect.width = MARIO_WIDTH;   // Reset width
                rect.height = MARIO_HEIGHT; // Reset height
            }
            std::cout << "Mario changed form to: " << form << std::endl;
        }
        if (IsKeyPressed(KEY_R))
        {
            // Reset Mario's form
            form = SMALL;
            rect.width = MARIO_WIDTH;
            rect.height = MARIO_HEIGHT;
        }

        sprite->SwitchForm(form);
    }

    void HandleInput()
    {
        std::unique_ptr<MarioState> newState = currentState->HandleInput(*this, *sprite);
        if (newState != nullptr)
        {
            currentState = std::move(newState);
            // sprite->SwitchAnimation(currentState->GetType());
        }
    }

    void Draw() override
    {
        DrawRectangleLines(rect.x, rect.y, rect.width, rect.height, RED); // Draw hitbox for debugging
        currentState->Draw(*this, *sprite);
    }

    void Update(Level &level) override
    {
        std::unique_ptr<MarioState> newState = currentState->Update(*this, *sprite);
        if (newState != nullptr)
        {
            currentState = std::move(newState);
            // sprite->SwitchAnimation(currentState->GetType());
        }

        float gravity = 900.0f;
        float dt = GetFrameTime();
        ApplyGravity(velocity, gravity);

        // Left wall
        if (position.x < 0)
        {
            position.x = 0;
            velocity.x = 0;
        }

        ResolveCollision(level);

        position.x += velocity.x * dt;
        position.y += velocity.y * dt;
        rect.x = position.x;
        rect.y = position.y;
    }

    void ResolveCollision(Level &level)
    {
        collision.CheckCollision(position, rect, velocity, level);
        collision.ResolveCollision(position, rect, velocity, level);
    };

    // Helper
    DIRECTION GetDirection() const
    {
        return direction;
    }

    MARIO_FORM GetForm() const
    {
        return form;
    }

    Vector2 GetPosition() const
    {
        return position;
    }
};

#endif