#ifndef MUSHROOM_H
#define MUSHROOM_H

#include <raylib.h>
#include <iostream>
#include "Item.h"
#include "Collision.h"
#include "GlobalVariables.h"
#include "GameSprite/MushroomSprite.h"

#define MUSHROOM_SIZE 16

class Mushroom : public Item
{
public:
    MushroomSprite mushroomSprite;
    Collision collision;

    Mushroom(Vector2 pos) : Item(pos, {MUSHROOM_SIZE * SCALE, MUSHROOM_SIZE * SCALE}) {}
    Mushroom(Vector2 pos, Vector2 vel, DIRECTION dir) : Item(pos, {MUSHROOM_SIZE * SCALE, MUSHROOM_SIZE * SCALE}, vel, dir) {}

    void Draw() override
    {
        DrawRectangleLines(rect.x, rect.y, rect.width, rect.height, RED);
        mushroomSprite.Draw(*this);
    }

    void Update(Level &level) override
    {
        float gravity = 900.0f;
        float dt = GetFrameTime();
        ApplyGravity(velocity, gravity);
        ResolveCollision(level);

        position.x += velocity.x * dt;
        position.y += velocity.y * dt;
        rect.x = position.x;
        rect.y = position.y;
    }

    void Collect(Mario &mario) override
    {
        std::cout << "Mushroom collected!" << std::endl;
        if (isCollected || mario.form != MARIO_FORM::SMALL)
            return;
        mario.Grow();
        isCollected = true;
        // Handle collision with other entities if needed
    }

    void ResolveCollision(Level &level)
    {
        collision.CheckCollision(position, rect, velocity, level);
        collision.ResolveCollision(position, rect, velocity, level);
    }
};

#endif // Mushroom_H