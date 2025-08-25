#include "CharacterState/SlidingState.h"

std::unique_ptr<CharacterState> SlidingState::HandleInput(Character &player, Sprite &sprite)
{
    return nullptr;
}

std::unique_ptr<CharacterState> SlidingState::Update(Character &player, Sprite &sprite)
{
    sprite.SwitchAnimation(STATE_SLIDING);
    return nullptr;
}

void SlidingState::Draw(Character &player, Sprite &sprite)
{
    sprite.Draw(player);
}
