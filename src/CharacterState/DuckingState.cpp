#include "CharacterState/DuckingState.h"
#include "CharacterState/IdleState.h"
#include "CharacterState/WalkingState.h"

std::unique_ptr<CharacterState> DuckingState::HandleInput(Character &player, Sprite &sprite)
{
    float deltaTime = GetFrameTime();

    // Move while ducking
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

    // Stand up
    if (IsKeyReleased(KEY_DOWN) || IsKeyReleased(KEY_S))
    {
        player.velocity.y = 0;
        return std::make_unique<IdleState>();
    }

    return nullptr;
}

std::unique_ptr<CharacterState> DuckingState::Update(Character &player, Sprite &sprite)
{
    sprite.SwitchAnimation(STATE_DUCKING);
    return nullptr;
}

void DuckingState::Draw(Character &player, Sprite &sprite)
{
    sprite.Draw(player);
}
