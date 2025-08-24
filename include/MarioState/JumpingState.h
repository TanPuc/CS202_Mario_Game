#ifndef JUMPINGSTATE_H
#define JUMPINGSTATE_H

#include "MarioState.h"

class JumpingState : public MarioState
{
public:
    std::unique_ptr<MarioState> HandleInput(Mario &entity, Sprite &sprite) override;
    std::unique_ptr<MarioState> Update(Mario &entity, Sprite &sprite) override;
    void Draw(Mario &entity, Sprite &sprite) override;
    STATE GetType() const override { return STATE_JUMPING; }
};

#endif
