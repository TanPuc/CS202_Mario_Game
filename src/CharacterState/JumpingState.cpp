#include "CharacterState/JumpingState.h"
#include "CharacterState/IdleState.h"
#include "CharacterState/WalkingState.h"
#include "CharacterState/ThrowingState.h"

std::unique_ptr<CharacterState> JumpingState::HandleInput(Character &player, Sprite &sprite)
{
    float deltaTime = GetFrameTime();
    // // Shoot fire ball
    // if (player.GetForm() == CHARACTER_FORM::FIRE)
    // {
    //     if (IsKeyPressed(KEY_LEFT_SHIFT) || IsKeyPressed(KEY_RIGHT_SHIFT))
    //     {
    //         player.ShootFireBall();
    //         sprite.SwitchAnimation(STATE_THROWING);
    //         return std::make_unique<ThrowingState>();
    //     }
    // }
    // Horizontal movement in air
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
    {
        player.velocity.x += (-MAX_VELOCITY * ACCELERATION * deltaTime);
        player.direction = LEFT;
        ClampVelocity(player.velocity);
        return std::make_unique<WalkingState>();
    }
    else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
    {
        player.velocity.x += (MAX_VELOCITY * ACCELERATION * deltaTime);
        player.direction = RIGHT;
        ClampVelocity(player.velocity);
        return std::make_unique<WalkingState>();
    }
    else
    {
        if (player.velocity.x < 0)
        {
            player.velocity.x += (MAX_VELOCITY * DECELERATION * deltaTime);
            if (player.velocity.x > 0)
                player.velocity.x = 0;
        }
        else if (player.velocity.x > 0)
        {
            player.velocity.x -= (MAX_VELOCITY * DECELERATION * deltaTime);
            if (player.velocity.x < 0)
                player.velocity.x = 0;
        }
        ClampVelocity(player.velocity);
    }

    return nullptr;
}

std::unique_ptr<CharacterState> JumpingState::Update(Character &player, Sprite &sprite)
{
    if (player.velocity.y == 0)
    {
        sprite.SwitchAnimation(STATE_IDLE);
        return std::make_unique<IdleState>();
    }
    sprite.SwitchAnimation(STATE_JUMPING);
    return nullptr;
}

void JumpingState::Draw(Character &player, Sprite &sprite)
{
    sprite.Draw(player);
}
