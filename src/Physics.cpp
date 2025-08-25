#include "Physics.h"
#include "Entity.h"
#include "Tile.h"
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