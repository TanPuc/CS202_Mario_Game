#ifndef PHYSICS_H
#define PHYSICS_H

#include <raylib.h>

// Forward declarations
class Entity;
class Level;

#define GRAVITY 9.81f
#define JUMP_FORCE 400.0f
#define SPEED 200.0f
#define FRICTION 0.1f
#define MAX_VELOCITY 300.0f
#define ACCELERATION 1.5f
#define DECELERATION 2.5f
#define JUMP_BUFFER_TIME 6 // 6 frames

inline int active_buffer = 0; // Buffer for jump input
void SetJumpBuffer();
void ResetJumpBuffer();
bool ConsumeJumpBuffer();

// Function declarations only
void ApplyGravity(Vector2 &velocity, float gravity);
void ClampVelocity(Vector2 &velocity);
bool CheckCollision(const Entity &a, const Entity &b);
bool CheckCollision(const Entity &a, const Level &level);
bool CheckCollision(const Entity &a, const Level &level, Vector2 &collisionPoint);

#endif // PHYSICS_H