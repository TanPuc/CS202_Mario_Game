#ifndef MARIO_H
#define MARIO_H

#include <raylib.h>
#include "Entity.h"
#include "Level.h"
#include "MarioState.h"
#include <iostream>
#include "Sprite.h"
#include "GlobalVariables.h"

#define FIREBALL_SPEED 300.0f // Speed of the fireball
#define FIREBALL_THRESHOLD 3  // Number of maximum fireballs
#define FIREBALL_LIFETIME 120 // Fireball lifetime in frames

class FireBall : public Entity
{
public:
    Rectangle boundBox = {0, 0, 4, 4}; // Fireball bounding for bouncing
    Rectangle hitBox = {0, 0, 4, 4};   // Fireball hitbox for enemy collision
    Texture2D texture;                 // Fireball texture
    int timer = 0;

    FireBall(Vector2 position) : Entity(position, Vector2({4.0f, 4.0f}))
    {
        velocity = {100.0f, -200.0f};
        texture = LoadTexture("assets/brick.png"); // Temporary
        boundBox.x = position.x;
        boundBox.y = position.y;
        hitBox.x = position.x;
        hitBox.y = position.y;
    }

    void Update(Level &level) override
    {
        float dt = GetFrameTime();

        timer++;
        position.x += velocity.x * dt;
        position.y += velocity.y * dt;
        ApplyGravity(velocity, 800.0f);

        if (CheckCollision(*this, level)) // Resolve collision
        {
            velocity.y = -500.0f; // Stop vertical movement
            ResolveCollision(level);
            position.y = (int)(position.y / 32) * 32; // Snap to tile grid
            velocity.y = 0;
        }

        rect.x = position.x;
        rect.y = position.y;
    }

    bool isOverLifeTime() const
    {
        return timer > FIREBALL_LIFETIME;
    }

    void Draw() override
    {
        DrawRectangleLines(rect.x, rect.y, rect.width, rect.height, RED); // Draw hitbox for debugging
        DrawTexture(texture, position.x, position.y, WHITE);              // Draw fireball texture
    }

    void ResolveCollision(Entity &other) override
    {
        // Handle collision with other entities if needed
        std::cout << "Fireball collided with another entity!" << std::endl;
    }

    void ResolveCollision(Level &level) override
    {
        // Handle collision with level tiles if needed
        std::cout << "Fireball collided with level!" << std::endl;
    }
};

class Mario : public Entity
{
public:
    std::unique_ptr<MarioState> currentState = std::make_unique<IdleState>();
    MarioSprite *sprite;
    std::vector<std::unique_ptr<FireBall>> fireballs;

    Mario(Vector2 position) : Entity(position, Vector2({32.0f, 32.0f}))
    {
        rect = {position.x, position.y, 32.0f, 32.0f};
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
            FireBall *fireball = new FireBall({position.x + rect.width, position.y + rect.height / 2});
            fireball->velocity.x = (direction == RIGHT) ? FIREBALL_SPEED : -FIREBALL_SPEED;
            fireballs.push_back(std::unique_ptr<FireBall>(fireball));
        }
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

    void ResolveCollision(Level &level) override {
    };

    void ResolveCollision(Entity &other) override
    {
        // Handle collision with other entities if needed
        std::cout << "Collision with another entity detected!" << std::endl;
    }
};

#endif