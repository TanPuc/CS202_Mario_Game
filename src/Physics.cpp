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

bool CheckCollision(const Rectangle &a, const Level &level)
{
    int minX = floor(a.x / TILE_SIZE);
    int maxX = floor((a.x + a.width) / TILE_SIZE);
    int minY = floor(a.y / TILE_SIZE);
    int maxY = floor((a.y + a.height) / TILE_SIZE);

    for (int y = minY; y <= maxY; y++)
    {
        for (int x = minX; x <= maxX; x++)
        {
            if (y >= 0 && y < (int)level.tiles.size() &&
                x >= 0 && x < (int)level.tiles[y].size() &&
                level.tiles[y][x] > 0)
            {
                Rectangle tileRect = {float(x * TILE_SIZE), float(y * TILE_SIZE), float(TILE_SIZE), float(TILE_SIZE)};
                if (CheckCollisionRecs(a, tileRect))
                {
                    return true;
                }
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

bool CheckOverlapX(const Rectangle& A, const Rectangle& B)
{
    if ((A.x < B.x + B.width) && (B.x < A.x + A.width))
    {
        return true;
    }

    return false;
}
bool CheckOverlapY(const Rectangle& A, const Rectangle& B)
{
    if ((A.y < B.y + B.height) && (B.y < A.y + A.height))
    {
        return true;
    }

    return false;
}
bool CheckOverlap(const Rectangle& A, const Rectangle& B)
{
    return CheckOverlapX(A, B) && CheckOverlapY(A, B);
}

