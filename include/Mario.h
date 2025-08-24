#ifndef MARIO_H
#define MARIO_H

#include "MarioState/MarioState.h"
#include "GameSprite/MarioSprite.h"
#include "GameSprite/ThrowingSprite.h"
#include "Entity.h"
#include "GlobalVariables.h"
#include <raylib.h>

#define HURT_BUFFER_THRESHOLD 1.0f

class MarioState;
class MarioSprite;

class Mario : public Entity
{
public:
    std::function<void()> onDeath;

    std::unique_ptr<MarioState> currentState;
    std::unique_ptr<MarioSprite> sprite;
    std::unique_ptr<ThrowingSprite> throwingSprite;
    MARIO_FORM form;
    float hurtBuffer; // > 0 means invisibility frame, = 0 means can be damaged
    bool isGrounded;
    bool isThrowing;
    int lives;
    int coins;
    int throwTimer;
    long long score;

    Mario(Vector2 position);
    Mario(Vector2 position, std::function<void()> onDeathAction);

    void Die();
    void Hurt();
    bool IsHurt() const;

    // Forms
    void Grow();
    void ChangeToFire();
    void ChangeToSuper();
    void Shrink();
    void ChangeForm(); // Debug

    void Slide(Vector2 contactPoint);

    void ShootFireBall();

    void HandleInput();
    void Draw() override;
    void Update(Level &level) override;
    void ResolveCollision(Level &level);

    // Helper
    DIRECTION GetDirection() const;
    MARIO_FORM GetForm() const;
    Vector2 GetPosition() const;
    void SetPosition(Vector2 newPosition);
    void SetOnDeathAction(std::function<void()> action);
};

#endif
