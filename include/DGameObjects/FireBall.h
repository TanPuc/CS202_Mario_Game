#ifndef FIREBALL_H
#define FIREBALL_H

#include <raylib.h>
#include <iostream>
#include "Entity.h"
#include "Tile.h"
#include "Physics.h"
#include "GlobalVariables.h"
#include "GameSprite/FireBallSprite.h"

#define FIREBALL_SPEED 300.0f // Speed of the fireball
#define FIREBALL_THRESHOLD 3  // Number of maximum fireballs
#define FIREBALL_LIFETIME 120 // Fireball lifetime in frames

class FireBall : public Entity
{
public:
    Rectangle boundBox = {0, 0, 8, 8}; // Fireball bounding for bouncing
    Rectangle hitBox = {0, 0, 8, 8};   // Fireball hitbox for enemy collision
    Sprite *sprite;
    int timer = 0;

    FireBall(Vector2 position, DIRECTION direction) : Entity(position, Vector2({16.0f, 16.0f}))
    {
        // velocity = {FIREBALL_SPEED, 100.0f};
        velocity = {0.0f, 0.0f};
        this->direction = direction;
        // texture = LoadTexture("assets/brick.png"); // Temporary
        boundBox.x = position.x + rect.width / 2 - boundBox.width / 2;
        boundBox.y = position.y + rect.height;
        hitBox.x = direction == RIGHT ? position.x + rect.width : position.x - hitBox.width;
        hitBox.y = position.y + rect.height / 2 - hitBox.height / 2;

        sprite = new FireBallSprite();
    }

    ~FireBall()
    {
        delete sprite;
    }

    void Update(Level &level) override
    {
        timer++;
        float dt = GetFrameTime();
        ApplyGravity(velocity, 800.0f);

        position.x += velocity.x * dt;
        position.y += velocity.y * dt;

        // if (CheckCollision(boundBox, level)) // Resolve collision
        // {
        //     // ResolveCollision(level);
        //     velocity.y = -150.0f;
        //     position.y = (int)(position.y / 32) * 32; // Snap to tile grid
        // }

        rect.x = position.x;
        rect.y = position.y;
        boundBox.x = position.x + rect.width / 2 - boundBox.width / 2;
        boundBox.y = position.y + rect.height;
        hitBox.x = direction == RIGHT ? position.x + rect.width : position.x - hitBox.width;
        hitBox.y = position.y + rect.height / 2 - hitBox.height / 2;
    }

    bool isOverLifeTime() const
    {
        return timer > FIREBALL_LIFETIME;
    }

    void Draw() override
    {
        // DrawRectangleLines(boundBox.x, boundBox.y, boundBox.width, boundBox.height, RED); // Draw bounding box for debugging
        // DrawRectangleLines(hitBox.x, hitBox.y, hitBox.width, hitBox.height, RED);         // Draw hitbox for debugging
        // DrawRectangleLines(rect.x, rect.y, rect.width, rect.height, RED);                 // Draw hitbox for debugging
        // DrawTexture(texture, position.x, position.y, WHITE); // Draw fireball texture
        sprite->Draw(*this);
    }
};

#endif // FIREBALL_H