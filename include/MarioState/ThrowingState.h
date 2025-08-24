#ifndef THROWINGSTATE_H
#define THROWINGSTATE_H

#include "MarioState.h"

class ThrowingState : public MarioState
{
public:
    std::unique_ptr<MarioState> HandleInput(Mario &entity, Sprite &sprite) override;
    std::unique_ptr<MarioState> Update(Mario &entity, Sprite &sprite) override;
    void Draw(Mario &entity, Sprite &sprite) override;
    STATE GetType() const override { return STATE_THROWING; }
};

#endif
