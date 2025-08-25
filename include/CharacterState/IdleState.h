#ifndef IDLESTATE_H
#define IDLESTATE_H

#include "CharacterState.h"

// ---------------- Idle CharacterState ----------------
class IdleState : public CharacterState
{
public:
    std::unique_ptr<CharacterState> HandleInput(Character &entity, Sprite &sprite) override;
    std::unique_ptr<CharacterState> Update(Character &entity, Sprite &sprite) override;
    void Draw(Character &entity, Sprite &sprite) override;
    STATE GetType() const override { return STATE_IDLE; } // Return the current state type
};

#endif