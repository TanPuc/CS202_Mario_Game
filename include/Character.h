#ifndef CHARACTER_H
#define CHARACTER_H

#include "CharacterState/CharacterState.h"
#include "GameSprite/CharacterSprite.h"
#include "GameSprite/MarioSprite.h"
#include "GameSprite/LuigiSprite.h"
#include "GameSprite/ThrowingSprite.h"
#include "Entity.h"
#include "GlobalVariables.h"
#include <raylib.h>

#define HURT_BUFFER_THRESHOLD 1.0f
#define FRAME_INDEX_THRESHOLD 6

class CharacterState;
class MarioSprite;
class LuigiSprite;

class Character : public Entity
{
public:
    std::function<void()> onDeath;

    std::unique_ptr<CharacterState> currentState;
    std::unique_ptr<CharacterSprite> sprite;
    std::unique_ptr<ThrowingSprite> throwingSprite;
    CHARACTER_FORM form;
    CHARACTER character;
    float hurtBuffer; // > 0 means invisibility frame, = 0 means can be damaged
    bool isThrowing;
    int lives;
    int coins;
    int throwTimer;
    long long score;

    // Transformation
    CHARACTER_FORM previousForm; // For transformation back
    CHARACTER_FORM targetForm;   // For transformation forward
    bool isTransforming = false;
    bool showingTarget = false;
    float transformTimer;
    int frameIndex;
    void ChangeToTargetForm(CHARACTER_FORM form);

    Character(Vector2 position);
    Character(Vector2 position, std::function<void()> onDeathAction);
    Character(CHARACTER character, Vector2 position, std::function<void()> onDeathAction);

    void Die();
    void Hurt();
    bool IsHurt() const;

    // Forms
    void Grow();
    void ChangeToFire();
    void ChangeToSuper();
    void Shrink();
    void ChangeForm(CHARACTER_FORM newForm);
    void ChangeForm(); // Debug

    void Slide(Vector2 contactPoint);

    void ShootFireBall();

    void HandleInput();
    void Draw() override;
    void Update(Level &level) override;
    void ResolveCollision(Level &level);

    // Helper
    DIRECTION GetDirection() const;
    CHARACTER_FORM GetForm() const;
    Vector2 GetPosition() const;
    void SetPosition(Vector2 newPosition);
    void SetOnDeathAction(std::function<void()> action);
};

#endif
