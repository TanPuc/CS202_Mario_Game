#ifndef PHYSICS_H
#define PHYSICS_H

#include <raylib.h>

// Forward declarations
class Entity;
class Level;

#define GRAVITY 900.0f //dm tan phuc, GRAVITY chung con` trong mario thi` rieng
#define JUMP_FORCE 460.0f
#define SPEED 200.0f
#define FRICTION 0.1f
#define MAX_VELOCITY 300.0f
#define ACCELERATION 1.5f
#define DECELERATION 2.5f
#define JUMP_BUFFER_TIME 6 // 6 frames
#define JUMP_TIME_THRESHOLD 10 // 10 frames
#define FULL 1.0f
#define HALF 0.5f

inline int active_buffer = 0; // Buffer for jump input
inline int jump_time = 0; // Time the jump button is held
void SetJumpBuffer();
void ResetJumpBuffer();
bool ConsumeJumpBuffer();

// Function declarations only
void ApplyGravity(Vector2 &velocity, float gravity);
void ClampVelocity(Vector2 &velocity);
bool CheckCollision(const Entity &a, const Entity &b);
bool CheckCollision(const Entity &a, const Level &level);
bool CheckCollision(const Rectangle &a, const Level &level);
bool CheckCollision(const Entity &a, const Level &level, Vector2 &collisionPoint);

bool CheckOverlapX(const Rectangle& A, const Rectangle& B);
bool CheckOverlapY(const Rectangle& A, const Rectangle& B);
bool CheckOverlap(const Rectangle& A, const Rectangle& B);

#endif // PHYSICS_H