#ifndef FIREFLOWER_H
#define FIREFLOWER_H

#include <raylib.h>
#include <iostream>
#include "Item.h"
#include "Collision.h"
#include "GlobalVariables.h"
#include "GameSprite/FireFlowerSprite.h"

#define FIREFLOWER_SIZE 16

class FireFlower : public Item
{
public:
    FireFlowerSprite fireFlowerSprite;
    Collision collision;

    FireFlower(Vector2 pos) : Item(pos, {FIREFLOWER_SIZE * SCALE, FIREFLOWER_SIZE * SCALE}) {}
    FireFlower(Vector2 pos, Vector2 vel, DIRECTION dir) : Item(pos, {FIREFLOWER_SIZE * SCALE, FIREFLOWER_SIZE * SCALE}, vel, dir) {}

    void Draw() override
    {
        fireFlowerSprite.Draw(*this);
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

    void ResolveCollision(Level &level)
    {
        collision.CheckCollision(position, rect, velocity, level);
        collision.ResolveCollision(position, rect, velocity, level);
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