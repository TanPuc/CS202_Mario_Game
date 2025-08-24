#ifndef JUMPINGSTATE_H
#define JUMPINGSTATE_H

#include "CharacterState.h"

class JumpingState : public CharacterState
{
public:
    std::unique_ptr<CharacterState> HandleInput(Character &entity, Sprite &sprite) override;
    std::unique_ptr<CharacterState> Update(Character &entity, Sprite &sprite) override;
    void Draw(Character &entity, Sprite &sprite) override;
    STATE GetType() const override { return STATE_JUMPING; }
};

#endif
