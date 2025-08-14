#ifndef COIN_H
#define COIN_H

#include <raylib.h>
#include <iostream>
#include "Entity.h"
#include "GlobalVariables.h"
#include "GameSprite/CoinSprite.h"

#define COIN_SIZE 16

class Coin : public Entity
{
public:
    CoinSprite coinSprite;
    bool isCollected;
    float timer = 0.0f; // Timer for coin animation
    const float lifeTime = 1.0f;

    Coin(Vector2 pos) : Entity(pos, {COIN_SIZE, COIN_SIZE}), isCollected(false)
    {
        velocity.y = -100.0f; // Initial upward velocity
    }
    void Draw() override
    {
        coinSprite.Draw(*this);
    }

    void Update(Level &level) override
    {
        float gravity = 900.0f;
        float dt = GetFrameTime();
        timer += dt;
        position.y += velocity.y * dt;
        rect.y = position.y;

        if (timer >= lifeTime)
        {
            isActive = false;
        }
    }

    void ResolveCollision(Level &level) override {};
    void ResolveCollision(Entity &other) override {};
};

#endif // COIN_H