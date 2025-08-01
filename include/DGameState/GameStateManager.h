#pragma once
#include "DCore/GameState.h"
#include <memory>

class GameStateManager
{
    private:
        std::unique_ptr<GameState> currentState;
    public:
        GameStateManager() = default;
        ~GameStateManager() = default;

        void changeState(GameState* newState);
        void update();
        void draw();   
};