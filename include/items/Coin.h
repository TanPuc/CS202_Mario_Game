#ifndef COIN_H
#define COIN_H

#include <raylib.h>
#include <iostream>
#include "Entity.h"
#include "GlobalVariables.h"
#include "sprite/CoinSprite.h"
#include "Item.h"

class Coin : public Item
{
public:
    CoinSprite coinSprite;

    Coin(Vector2 pos) : Item(pos, {16, 16}) {}

    void OnCollect(Mario &mario) override
    {
        std::cout << "Coin collected!" << std::endl;
    }
    void Draw() override
    {
        coinSprite.Draw(*this);
    }

    void Update(Level &level) override
    {
        float gravity = 900.0f;
        float dt = GetFrameTime();
        ApplyGravity(velocity, gravity);
        position.x += velocity.x * dt;
        position.y += velocity.y * dt;

        if (CheckCollision(*this, level))
        {
            ResolveCollision(level);
        }
        rect.x = position.x;
        rect.y = position.y;
    }

    void Update(Level &level, Mario &mario)
    {
        float gravity = 900.0f;
        float dt = GetFrameTime();
        ApplyGravity(velocity, gravity);
        position.x += velocity.x * dt;
        position.y += velocity.y * dt;

        if (CheckCollision(*this, mario))
        {
            OnCollect(mario);
            // Reset coin position or remove it from the level
            position = {0, 0}; // Example: move coin off-screen
            rect.x = position.x;
            rect.y = position.y;
        }

        if (CheckCollision(*this, level))
        {
            ResolveCollision(level);
        }
        rect.x = position.x;
        rect.y = position.y;
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

#endif // COIN_H