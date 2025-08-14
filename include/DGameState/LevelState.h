#pragma once
#include "DCore/GameState.h"
#include "DGameState/GameStateManager.h"
#include "DGUI/GUIManager.h"

class LevelState: public GameState
{
    private:
        GameStateManager* gsm;
        GUIManager& guiManager;
    public:
        LevelState(GameStateManager* manager);

        void enter() override;
        void exit() override;
        void update() override;
        void draw() override;
};