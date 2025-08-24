#include "MarioState/SlidingState.h"

std::unique_ptr<MarioState> SlidingState::HandleInput(Mario &player, Sprite &sprite)
{
    return nullptr;
}

std::unique_ptr<MarioState> SlidingState::Update(Mario &player, Sprite &sprite)
{
    sprite.SwitchAnimation(STATE_SLIDING);
    return nullptr;
}

void SlidingState::Draw(Mario &player, Sprite &sprite)
{
    sprite.Draw(player);
}
