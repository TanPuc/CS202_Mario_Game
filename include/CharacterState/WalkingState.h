#ifndef WALKINGSTATE_H
#define WALKINGSTATE_H

#include "CharacterState.h"

class WalkingState : public CharacterState
{
public:
    std::unique_ptr<CharacterState> HandleInput(Character &entity, Sprite &sprite) override;
    std::unique_ptr<CharacterState> Update(Character &entity, Sprite &sprite) override;
    void Draw(Character &entity, Sprite &sprite) override;
    STATE GetType() const override { return STATE_WALKING; }
};

#endif
