#pragma once
#include "DCore/GameState.h"
#include "DGameState/GameStateManager.h"
#include "DGUI/GUIManager.h"

class GameOverState: public GameState
{
    private:
        GameStateManager* gsm;
        GUIManager& guiManager;
    
    public:
        GameOverState(GameStateManager* manager);

        void enter() override;
        void exit() override;
        void update() override;
        void draw() override;
};