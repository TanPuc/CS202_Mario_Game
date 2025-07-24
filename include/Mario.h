#ifndef MARIO_H
#define MARIO_H

#include <raylib.h>
#include "Entity.h"
#include "Physics.h"
#include <iostream>

enum State
{
    IDLE,
    RUNNING,
    JUMPING,
    FALLING
};

class Mario : public Entity
{
public:
    bool moveLeft;
    bool moveRight;
    float speed;
    float jumpForce;
    State state;

    Mario(Texture texture, Vector2 position) : Entity(texture, position), state(IDLE), speed(200.0f), jumpForce(300.0f), moveLeft(false), moveRight(false) {}

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