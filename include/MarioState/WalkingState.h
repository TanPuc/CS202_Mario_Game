#ifndef WALKINGSTATE_H
#define WALKINGSTATE_H

#include "MarioState.h"

class WalkingState : public MarioState
{
public:
    std::unique_ptr<MarioState> HandleInput(Mario &entity, Sprite &sprite) override;
    std::unique_ptr<MarioState> Update(Mario &entity, Sprite &sprite) override;
    void Draw(Mario &entity, Sprite &sprite) override;
    STATE GetType() const override { return STATE_WALKING; }
};

#endif
