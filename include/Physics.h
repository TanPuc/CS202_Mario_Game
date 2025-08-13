#ifndef PHYSICS_H
#define PHYSICS_H

#include <raylib.h>

#define GRAVITY 9.81f        // Gravity constant
#define JUMP_FORCE 600.0f    // Force applied when jumping
#define MOVE_SPEED 200.0f    // Speed of movement
#define FRICTION 0.1f        // Friction applied to the player
#define MAX_VELOCITY 1000.0f // Maximum velocity to prevent excessive speed

#include <raylib.h>

void ApplyGravity(Vector2 &velocity, float gravity) {
    float dt = GetFrameTime();
    velocity.y += gravity * dt;
}

void ClampVelocity(Vector2 &velocity) { // Clamp the velocity to prevent excessive speed
    if (velocity.x > MAX_VELOCITY) velocity.x = MAX_VELOCITY;
    if (velocity.x < -MAX_VELOCITY) velocity.x = -MAX_VELOCITY;
}

#endif // PHYSICS_H