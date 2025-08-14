#ifndef MARIO_H
#define MARIO_H

#include <iostream>
#include <raylib.h>
#include "GlobalVariables.h"
#include "Entity.h"
#include "Level.h"
#include "MarioState.h"
#include "sprite/MarioSprite.h"
#include "FireBall.h"
#include "Physics.h"
class Mario : public Entity
{
public:
    std::unique_ptr<MarioState> currentState = std::make_unique<IdleState>();
    MarioSprite *sprite;
    MARIO_FORM form;
    std::vector<std::shared_ptr<FireBall>> fireballs;

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
        if (IsKeyDown(KEY_LEFT))
            velocity.x = -speed;
        else if (IsKeyDown(KEY_RIGHT))
            velocity.x = speed;
        else
            velocity.x = 0;

        if (IsKeyPressed(KEY_SPACE) && state != JUMPING && state != FALLING)
        {
            velocity.y = -jumpForce;
            state = JUMPING;
        }
    }

    void Update() override
    {
        // float gravity = 98.1f; // Gravity effect
        float dt = GetFrameTime();
        HandleInput();
        ApplyGravity(velocity, 800.0f); // Gravity
        position.x += velocity.x * dt;
        position.y += velocity.y * dt;
        rect.x = position.x;
        rect.y = position.y;

        // Update state
        if (velocity.y > 0)
            state = FALLING;
        else if (velocity.y < 0)
            state = JUMPING;
        else if (velocity.x != 0)
            state = RUNNING;
        else
            state = IDLE;
    }

    void CheckCollision(Level &level)
    {
        Rectangle playerRect = rect;

        // Check ground/platform collision
        if (level.CheckCollision(playerRect))
        {
            position.y = (int)(position.y / 32) * 32; // Snap to tile grid
            velocity.y = 0;
            if (state == FALLING || state == JUMPING)
                state = IDLE;
        }
    };

    void Animate()
    {
        // Choose frame based on state
    }

    void OnCollision(Entity &other) override
    {
        // Example: stomp enemy or collect coin
    }
};

#endif