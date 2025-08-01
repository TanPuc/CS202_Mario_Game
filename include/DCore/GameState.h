#pragma once

class GameState
{
    public:
    virtual ~GameState() = default;

    virtual void enter() = 0;
    virtual void exit() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
};