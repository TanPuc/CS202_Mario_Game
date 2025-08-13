#ifndef MUSHROOM_H
#define MUSHROOM_H

#include <raylib.h>
#include <iostream>
#include "Entity.h"
#include "GlobalVariables.h"
#include "sprite/MushroomSprite.h"
#include "Item.h"

class Mushroom : public Item
{
public:
    MushroomSprite MushroomSprite;

    Mushroom(Vector2 pos) : Item(pos, {16, 16}) {}

    void OnCollect(Mario &mario) override
    {
        std::cout << "Mushroom collected!" << std::endl;
        mario.Grow();
    }
    void Draw() override
    {
        MushroomSprite.Draw(*this);
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
            // Reset Mushroom position or remove it from the level
            position = {0, 0}; // Example: move Mushroom off-screen
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

#endif // Mushroom_H