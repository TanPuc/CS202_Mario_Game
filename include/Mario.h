#ifndef MARIO_H
#define MARIO_H

#include <iostream>
#include <raylib.h>
#include "GlobalVariables.h"
#include "Entity.h"
#include "Level.h"
#include "MarioState.h"
#include "GameSprite/MarioSprite.h"
#include "DGameObjects/FireBall.h"
#include "Physics.h"
class Mario : public Entity
{
public:
    std::unique_ptr<MarioState> currentState = std::make_unique<IdleState>();
    MarioSprite *sprite;
    MARIO_FORM form;
    std::vector<std::shared_ptr<FireBall>> fireballs;
    int lives;
    int coins;
    long long score;

    Mario(Vector2 position) : Entity(position, Vector2({MARIO_WIDTH, MARIO_HEIGHT})), form(SMALL)
    {
        rect = {position.x, position.y, MARIO_WIDTH, MARIO_HEIGHT};
        sprite = new MarioSprite();
    }
    ~Mario()
    {
        delete sprite;
    }

    void ShootFireBall()
    {
        if (fireballs.size() < FIREBALL_THRESHOLD)
        {
            FireBall *fireball = new FireBall({position.x + rect.width, position.y + rect.height / 2}, direction);
            fireball->velocity.x = (direction == RIGHT) ? FIREBALL_SPEED : -FIREBALL_SPEED;
            fireballs.push_back(std::shared_ptr<FireBall>(fireball));
        }
    }

    void Grow()
    {
        if (form == SMALL)
        {
            form = BIG;
            rect.height = MARIO_HEIGHT * 2.0f; // Increase height for big Mario
        }
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
            sprite->SwitchAnimation(currentState->GetType());
        }

        if (IsKeyPressed(KEY_LEFT_SHIFT))
        {
            ShootFireBall();
        }

        ChangeForm();
    }

    void Draw() override
    {
        DrawRectangleLines(rect.x, rect.y, rect.width, rect.height, RED); // Draw hitbox for debugging
        currentState->Draw(*this, *sprite);
        if (!fireballs.empty())
        {
            for (auto &fireball : fireballs)
            {
                fireball->Draw();
            }
        }
        // Draw fireballs
    }

    void Update(Level &level) override
    {
        std::unique_ptr<MarioState> newState = currentState->Update(*this, *sprite);
        if (newState != nullptr)
        {
            currentState = std::move(newState);
            sprite->SwitchAnimation(currentState->GetType());
        }

        float gravity = 900.0f;
        float dt = GetFrameTime();
        ApplyGravity(velocity, gravity);
        position.x += velocity.x * dt;
        position.y += velocity.y * dt;

        if (CheckCollision(*this, level)) // Resolve collision
        {
            ResolveCollision(level);
        }
        rect.x = position.x;
        rect.y = position.y;

        // Update fireballs
        for (auto it = fireballs.begin(); it != fireballs.end();)
        {
            if ((*it)->isOverLifeTime())
            {
                std::cout << "Fireball expired!" << std::endl;
                it = fireballs.erase(it); // Remove expired fireball
                continue;
            }
            (*it)->Update(level);
            if ((*it)->GetPosition().y < 0 || (*it)->GetPosition().y > GetScreenHeight())
            {
                it = fireballs.erase(it); // Remove fireball if it goes out of bounds
            }
            else
            {
                ++it; // Move to the next fireball
            }
        }
    }

    void ResolveCollision(Level &level) override
    {
        position.y = (int)(position.y / MARIO_HEIGHT) * MARIO_HEIGHT; // Snap to tile grid
        velocity.y = 0;
    };

    void ResolveCollision(Entity &other) override
    {
        // Handle collision with other entities if needed
        std::cout << "Collision with another entity detected!" << std::endl;
    }
};

#endif