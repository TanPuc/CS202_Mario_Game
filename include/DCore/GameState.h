#pragma once

#include "GlobalVariables.h"

class GameState
{
public:
    virtual ~GameState() = default;

    virtual void enter() = 0;
    virtual void exit() = 0;
    virtual void resume() {};
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual bool isOpaque() const { return true; }
};