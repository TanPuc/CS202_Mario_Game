#ifndef DUCKINGSTATE_H
#define DUCKINGSTATE_H

#include "MarioState.h"

class DuckingState : public MarioState
{
public:
    std::unique_ptr<MarioState> HandleInput(Mario &entity, Sprite &sprite) override;
    std::unique_ptr<MarioState> Update(Mario &entity, Sprite &sprite) override;
    void Draw(Mario &entity, Sprite &sprite) override;
    STATE GetType() const override { return STATE_DUCKING; }
};

#endif
