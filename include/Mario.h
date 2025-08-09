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
    Rectangle boundBox = {0, 0, 8, 8}; // Fireball bounding for bouncing
    Rectangle hitBox = {0, 0, 8, 8};   // Fireball hitbox for enemy collision
    Texture2D texture;                 // Fireball texture
    int timer = 0;

    FireBall(Vector2 position, DIRECTION direction) : Entity(position, Vector2({16.0f, 16.0f}))
    {
        // velocity = {FIREBALL_SPEED, 100.0f};
        velocity = {0.0f, 0.0f};
        this->direction = direction;
        texture = LoadTexture("assets/brick.png"); // Temporary
        boundBox.x = position.x + rect.width / 2 - boundBox.width / 2;
        boundBox.y = position.y + rect.height;
        hitBox.x = direction == RIGHT? position.x + rect.width : position.x - hitBox.width;
        hitBox.y = position.y + rect.height / 2 - hitBox.height / 2;
    }

    void Update(Level &level) override
    {
        timer++;
        float dt = GetFrameTime();
        ApplyGravity(velocity, 800.0f);

        position.x += velocity.x * dt;
        position.y += velocity.y * dt;

        if (CheckCollision(boundBox, level)) // Resolve collision
        {
            // ResolveCollision(level);
            velocity.y = -150.0f;
            position.y = (int)(position.y / 32) * 32; // Snap to tile grid
        }

        rect.x = position.x;
        rect.y = position.y;
        boundBox.x = position.x + rect.width / 2 - boundBox.width / 2;
        boundBox.y = position.y + rect.height;
        hitBox.x = direction == RIGHT? position.x + rect.width : position.x - hitBox.width;
        hitBox.y = position.y + rect.height / 2 - hitBox.height / 2;
    }

    bool isOverLifeTime() const
    {
        return timer > FIREBALL_LIFETIME;
    }

    void Draw() override
    {
        DrawRectangleLines(boundBox.x, boundBox.y, boundBox.width, boundBox.height, RED); // Draw bounding box for debugging
        DrawRectangleLines(hitBox.x, hitBox.y, hitBox.width, hitBox.height, RED);         // Draw hitbox for debugging
        DrawRectangleLines(rect.x, rect.y, rect.width, rect.height, RED);                 // Draw hitbox for debugging
        DrawTexture(texture, position.x, position.y, WHITE); // Draw fireball texture
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
            FireBall *fireball = new FireBall({position.x + rect.width, position.y + rect.height / 2}, direction);
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
        float gravity = 900.0f;
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