#include "MarioState/DeadState.h"

std::unique_ptr<MarioState> DeadState::HandleInput(Mario &player, Sprite &sprite)
{
    return nullptr;
}

std::unique_ptr<MarioState> DeadState::Update(Mario &player, Sprite &sprite)
{
    sprite.SwitchAnimation(STATE_DEAD);
    return nullptr;
}

void DeadState::Draw(Mario &player, Sprite &sprite)
{
    sprite.Draw(player);
}
