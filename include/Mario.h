#ifndef MARIO_H
#define MARIO_H

#include <iostream>
#include <raylib.h>
#include <array>
#include <cmath>
#include <memory>
#include "GlobalVariables.h"
#include "Entity.h"
#include "MarioState.h"
#include "GameSprite/MarioSprite.h"
#include "DCore/SoundManager.h"
#include <functional>

#define HURT_BUFFER_THRESHOLD 1.0f

class Mario : public Entity
{
public:
    std::function<void()> onDeath;

    std::unique_ptr<MarioState> currentState;
    std::unique_ptr<MarioSprite> sprite;
    MARIO_FORM form;
    float hurtBuffer; // > 0 means invisibility frame, = 0 means can be damaged
    int lives;
    int coins;
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
