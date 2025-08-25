#ifndef THROWINGSTATE_H
#define THROWINGSTATE_H

#include "CharacterState.h"

class ThrowingState : public CharacterState
{
public:
    std::unique_ptr<CharacterState> HandleInput(Character &entity, Sprite &sprite) override;
    std::unique_ptr<CharacterState> Update(Character &entity, Sprite &sprite) override;
    void Draw(Character &entity, Sprite &sprite) override;
    STATE GetType() const override { return STATE_THROWING; }
};

#endif
