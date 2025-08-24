#include "CharacterState/DeadState.h"

std::unique_ptr<CharacterState> DeadState::HandleInput(Character &player, Sprite &sprite)
{
    return nullptr;
}

std::unique_ptr<CharacterState> DeadState::Update(Character &player, Sprite &sprite)
{
    sprite.SwitchAnimation(STATE_DEAD);
    return nullptr;
}

void DeadState::Draw(Character &player, Sprite &sprite)
{
    sprite.Draw(player);
}
