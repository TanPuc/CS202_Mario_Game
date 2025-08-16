#ifndef FIREFLOWER_H
#define FIREFLOWER_H

#include <raylib.h>
#include <iostream>
#include "Item.h"
#include "GlobalVariables.h"
#include "GameSprite/FireFlowerSprite.h"

class FireFlower : public Item
{
public:
    FireFlowerSprite fireFlowerSprite;

    FireFlower(Vector2 pos) : Item(pos, {16, 16}) {}

    void Draw() override
    {
        fireFlowerSprite.Draw(*this);
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

    void ResolveCollision(Level &level)
    {
        position.y = (int)(position.y / MARIO_HEIGHT) * MARIO_HEIGHT; // Snap to tile grid
        velocity.y = 0;
    };

    void Collect(Mario &mario) override
    {
        if (isCollected || mario.form != MARIO_FORM::BIG)
            return;
        mario.ChangeToFire();
        mario.position.y = position.y - 32.0f;
        mario.rect.y = mario.position.y;
        isCollected = true;
        // Handle collision with other entities if needed
    }
};

#endif // Mushroom_H