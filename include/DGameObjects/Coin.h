#ifndef COIN_H
#define COIN_H

#include <raylib.h>
#include <iostream>
#include "Item.h"
#include "GlobalVariables.h"
#include "GameSprite/CoinSprite.h"

#define COIN_SIZE 16

class Coin : public Item
{
public:
    CoinSprite coinSprite;
    float timer = 0.0f; // Timer for coin animation
    const float lifeTime = 1.0f;

    Coin(Vector2 pos) : Item(pos, {COIN_SIZE, COIN_SIZE}) {}

    void Draw() override
    {
        coinSprite.Draw(*this);
    }

    void Collect(Mario &mario) override
    {
        if (isCollected)
            return;
        isCollected = true;
        mario.coins++;
        mario.score += 100; // Increment score by 100 for collecting a coin
        std::cout << "Coin collected! Total coins: " << mario.coins << std::endl;
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
            position.y = (int)(position.y / MARIO_HEIGHT) * MARIO_HEIGHT; // Snap to tile grid
            velocity.y = 0;
        }

        rect.x = position.x;
        rect.y = position.y;

        // if (timer >= lifeTime)
        // {
        //     isActive = false;
        // }
    }
};

#endif // COIN_H