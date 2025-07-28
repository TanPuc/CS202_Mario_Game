#ifndef PHYSICS_H
#define PHYSICS_H

#include <raylib.h>

#define GRAVITY 9.81f        // Gravity constant
#define JUMP_FORCE 600.0f    // Force applied when jumping
#define SPEED 200.0f         // Speed of movement
#define FRICTION 0.1f        // Friction applied to the player
#define MAX_VELOCITY 1000.0f // Maximum velocity to prevent excessive speed

void ApplyGravity(Vector2 &velocity, float gravity)
{
    float dt = GetFrameTime();
    velocity.y += gravity * dt;
}

void ClampVelocity(Vector2 &velocity)
{ // Clamp the velocity to prevent excessive speed
    if (velocity.x > MAX_VELOCITY)
        velocity.x = MAX_VELOCITY;
    if (velocity.x < -MAX_VELOCITY)
        velocity.x = -MAX_VELOCITY;
}

bool CheckCollision(const Entity &a, const Entity &b)
{
    return CheckCollisionRecs(a.GetBounds(), b.GetBounds());
}

bool CheckCollision(const Entity &a, const Level &level)
{
    int minX = floor(a.GetBounds().x / TILE_SIZE);
    int maxX = floor((a.GetBounds().x + a.GetBounds().width) / TILE_SIZE);
    int minY = floor(a.GetBounds().y / TILE_SIZE);
    int maxY = floor((a.GetBounds().y + a.GetBounds().height) / TILE_SIZE);

    for (int x = minX; x <= maxX; x++)
    {
        for (int y = minY; y <= maxY; y++)
        {
            if (x < 0 || y < 0 || y >= level.tiles.size() || x >= level.tiles[y].size())
                continue; // Out of bounds

            if (level.tiles[y][x] > 0) // Assuming non-zero tiles are solid
            {
                Rectangle tileRect = {float(x * TILE_SIZE), float(y * TILE_SIZE), float(TILE_SIZE), float(TILE_SIZE)};
                if (CheckCollisionRecs(a.GetBounds(), tileRect))
                    return true;
            }
        }
    }
    return false;
}

bool CheckCollision(const Entity &a, const Level &level, Vector2 &collisionPoint)
{
    int minX = floor(a.GetBounds().x / TILE_SIZE);
    int maxX = floor((a.GetBounds().x + a.GetBounds().width) / TILE_SIZE);
    int minY = floor(a.GetBounds().y / TILE_SIZE);
    int maxY = floor((a.GetBounds().y + a.GetBounds().height) / TILE_SIZE);

    for (int x = minX; x <= maxX; x++)
    {
        for (int y = minY; y <= maxY; y++)
        {
            if (x < 0 || y < 0 || y >= level.tiles.size() || x >= level.tiles[y].size())
                continue; // Out of bounds

            if (level.tiles[y][x] > 0) // Assuming non-zero tiles are solid
            {
                Rectangle tileRect = {float(x * TILE_SIZE), float(y * TILE_SIZE), float(TILE_SIZE), float(TILE_SIZE)};
                if (CheckCollisionRecs(a.GetBounds(), tileRect))
                {
                    collisionPoint = {tileRect.x, tileRect.y};
                    return true;
                }
            }
        }
    }
    return false;
}
#endif // PHYSICS_H