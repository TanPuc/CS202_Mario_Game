#ifndef FIREBALL_H
#define FIREBALL_H

#include <raylib.h>
#include <iostream>
#include "Entity.h"
#include "Collision.h"
#include "Physics.h"
#include "GlobalVariables.h"
#include "GameSprite/FireBallSprite.h"

#define FIREBALL_SPEED 300.0f // Speed of the fireball
#define FIREBALL_THRESHOLD 3  // Number of maximum fireballs
#define FIREBALL_LIFETIME 120 // Fireball lifetime in frames

#define FIREBALL_SIZE 8 * SCALE

class FireBall : public Entity
{
public:
    Rectangle bounceBox = {0, 0, FIREBALL_SIZE / 2, FIREBALL_SIZE / 2}; // Fireball bounding for bouncing
    Rectangle hitBox = {0, 0, FIREBALL_SIZE / 2, FIREBALL_SIZE / 2};    // Fireball hitbox for enemy collision
    Sprite *sprite;
    int timer = 0;
    Collision collision;

    FireBall(Vector2 position, DIRECTION direction) : Entity(position, Vector2({FIREBALL_SIZE, FIREBALL_SIZE}))
    {
        // velocity = {FIREBALL_SPEED, 100.0f};
        velocity = {0.0f, 0.0f};
        this->direction = direction;
        // texture = LoadTexture("assets/brick.png"); // Temporary
        bounceBox.x = position.x + rect.width / 2 - bounceBox.width / 2;
        bounceBox.y = position.y + rect.height;
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
        ResolveCollision(level);

        position.x += velocity.x * dt;
        position.y += velocity.y * dt;
        rect.x = position.x;
        rect.y = position.y;

        bounceBox.x = position.x + rect.width / 2 - bounceBox.width / 2;
        bounceBox.y = position.y + rect.height;
        hitBox.x = direction == RIGHT ? position.x + rect.width : position.x - hitBox.width;
        hitBox.y = position.y + rect.height / 2 - hitBox.height / 2;
    }

    bool isOverLifeTime() const
    {
        return timer > FIREBALL_LIFETIME;
    }

    void Draw() override
    {
        //     DrawRectangleLines(bounceBox.x, bounceBox.y, bounceBox.width, bounceBox.height, RED); // Draw bounding box for debugging
        //     DrawRectangleLines(hitBox.x, hitBox.y, hitBox.width, hitBox.height, RED);             // Draw hitbox for debugging
        //     DrawRectangleLines(rect.x, rect.y, rect.width, rect.height, RED);                     // Draw hitbox for debugging                             // Draw fireball texture
        sprite->Draw(*this);
    }

    void ResolveCollision(Level &level)
    {
        // if (collision.IsCollideWithLevel(position, rect, velocity, level))
        // {
        //     velocity.y = -150.f;
        // }
        // collision.CheckCollision(position, rect, velocity, level);
        // collision.ResolveCollision(position, rect, velocity, level);
        collision.FireBallVsLevel(position, rect, velocity, level);
    }
};

#endif // FIREBALL_H