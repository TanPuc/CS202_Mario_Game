#include "Physics.h"
#include "Entity.h"
#include "Level.h"
#include <cmath>

void SetJumpBuffer()
{
    active_buffer = JUMP_BUFFER_TIME;
}

void ResetJumpBuffer()
{
    active_buffer = 0; // Reset the jump buffer
}

bool ConsumeJumpBuffer()
{
    std::cout << "Active buffer: " << active_buffer << std::endl;
    if (active_buffer > 0)
    {
        active_buffer--;
        return true; // Jump available from buffer
    }
    return false; // No jump in buffer
}

void ApplyGravity(Vector2 &velocity, float gravity)
{
    float dt = GetFrameTime();
    velocity.y += gravity * dt;
}

void ClampVelocity(Vector2 &velocity)
{
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
    int minX = a.GetPosition().x / TILE_SIZE;
    int maxX = (a.GetPosition().x + a.GetBounds().width) / TILE_SIZE;
    int minY = a.GetPosition().y / TILE_SIZE;
    int maxY = (a.GetPosition().y + a.GetBounds().height) / TILE_SIZE;

    for (int y = minY; y <= maxY; y++)
    {
        for (int x = minX; x <= maxX; x++)
        {
            if (y >= 0 && y < (int)level.tiles.size() &&
                x >= 0 && x < (int)level.tiles[y].size() &&
                level.tiles[y][x] > 0)
            {
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
            if (x < 0 || y < 0 || y >= (int)level.tiles.size() || x >= (int)level.tiles[y].size())
                continue;

            if (level.tiles[y][x] > 0)
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