#include "MarioState/ThrowingState.h"
#include "MarioState/IdleState.h"
#include "MarioState/WalkingState.h"
#include "MarioState/JumpingState.h"
#include "MarioState/DuckingState.h"
#include "DCore/SoundManager.h"

std::unique_ptr<MarioState> ThrowingState::HandleInput(Mario &player, Sprite &sprite)
{
    float deltaTime = GetFrameTime();

    // Jumping
    if (IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
    {
        jump_time++;
        if (jump_time >= JUMP_TIME_THRESHOLD)
        {
            player.velocity.y = -JUMP_FORCE;
            SoundManager::getInstance().playSound(SoundEffect::JUMP);
            jump_time = 0;
            sprite.SwitchAnimation(STATE_JUMPING);
            return std::make_unique<JumpingState>();
        }
        return nullptr;
    }

    if (jump_time > 1 && (IsKeyUp(KEY_SPACE) || IsKeyUp(KEY_UP) || IsKeyUp(KEY_W)))
    {
        player.velocity.y = -JUMP_FORCE * (HALF + float(0.05f * jump_time));
        SoundManager::getInstance().playSound(SoundEffect::JUMP);
        jump_time = 0;
        sprite.SwitchAnimation(STATE_JUMPING);
        return std::make_unique<JumpingState>();
    }

    // Walking
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
    {
        player.velocity.x += (-MAX_VELOCITY * ACCELERATION * deltaTime);
        player.direction = LEFT;
        ClampVelocity(player.velocity);
        sprite.SwitchAnimation(STATE_WALKING);
        return std::make_unique<WalkingState>();
    }
    else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
    {
        player.velocity.x += (MAX_VELOCITY * ACCELERATION * deltaTime);
        player.direction = RIGHT;
        ClampVelocity(player.velocity);
        sprite.SwitchAnimation(STATE_WALKING);
        return std::make_unique<WalkingState>();
    }
    else
    {
        if (player.velocity.x < 0)
        {
            player.velocity.x += (MAX_VELOCITY * DECELERATION * deltaTime);
            if (player.velocity.x > 0)
            {
                player.velocity.x = 0;
                return std::make_unique<IdleState>();
            }
        }
        else if (player.velocity.x > 0)
        {
            player.velocity.x -= (MAX_VELOCITY * DECELERATION * deltaTime);
            if (player.velocity.x < 0)
            {
                player.velocity.x = 0;
                return std::make_unique<IdleState>();
            }
        }
        ClampVelocity(player.velocity);
    }

    // Ducking
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
    {
        sprite.SwitchAnimation(STATE_DUCKING);
        return std::make_unique<DuckingState>();
    }

    return nullptr;
}

std::unique_ptr<MarioState> ThrowingState::Update(Mario &player, Sprite &sprite)
{
    sprite.SwitchAnimation(STATE_THROWING);
    return nullptr;
}

void ThrowingState::Draw(Mario &player, Sprite &sprite)
{
    sprite.Draw(player);
}
