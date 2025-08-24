#ifndef SLIDINGSTATE_H
#define SLIDINGSTATE_H

#include "MarioState.h"

class SlidingState : public MarioState
{
public:
    std::unique_ptr<MarioState> HandleInput(Mario &entity, Sprite &sprite) override;
    std::unique_ptr<MarioState> Update(Mario &entity, Sprite &sprite) override;
    void Draw(Mario &entity, Sprite &sprite) override;
    STATE GetType() const override { return STATE_SLIDING; }
};

#endif
