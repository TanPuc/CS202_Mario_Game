#ifndef DEADSTATE_H
#define DEADSTATE_H

#include "CharacterState.h"

class DeadState : public CharacterState
{
public:
    std::unique_ptr<CharacterState> HandleInput(Character &entity, Sprite &sprite) override;
    std::unique_ptr<CharacterState> Update(Character &entity, Sprite &sprite) override;
    void Draw(Character &entity, Sprite &sprite) override;
    STATE GetType() const override { return STATE_DEAD; }
};

#endif
