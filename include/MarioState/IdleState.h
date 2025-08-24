#ifndef IDLESTATE_H
#define IDLESTATE_H

#include "MarioState.h"

// ---------------- Idle MarioState ----------------
class IdleState : public MarioState
{
public:
    std::unique_ptr<MarioState> HandleInput(Mario &entity, Sprite &sprite) override;
    std::unique_ptr<MarioState> Update(Mario &entity, Sprite &sprite) override;
    void Draw(Mario &entity, Sprite &sprite) override;
    STATE GetType() const override { return STATE_IDLE; } // Return the current state type
};

#endif