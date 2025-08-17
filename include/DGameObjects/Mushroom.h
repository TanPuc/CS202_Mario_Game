#ifndef MUSHROOM_H
#define MUSHROOM_H

#include <raylib.h>
#include <iostream>
#include "Item.h"
#include "GlobalVariables.h"
#include "GameSprite/MushroomSprite.h"

class Mushroom : public Item
{
public:
    MushroomSprite mushroomSprite;

    Mushroom(Vector2 pos) : Item(pos, {16, 16}) {}

    void Draw() override
    {
        mushroomSprite.Draw(*this);
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
        std::cout << "Mushroom collected!" << std::endl;
        if (isCollected || mario.form != MARIO_FORM::SMALL)
            return;
        mario.Grow();
        isCollected = true;
        // Handle collision with other entities if needed
    }
};

#endif // Mushroom_H