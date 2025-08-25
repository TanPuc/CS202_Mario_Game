#pragma once
#include "DCore/GameState.h"
#include "DGameState/GameStateManager.h"
#include "DGUI/GUIManager.h"
#include "raylib.h"

class SaveSlotState: public GameState
{
    private:
        GameStateManager *gsm;
        GUIManager& guiManager;
        Texture2D buttonTexture;

        bool canLoadGame;

        void buildGUI();
    
    public:
        SaveSlotState(GameStateManager *manager);
        void enter() override;
        void exit() override;
        void update() override;
        void draw() override;
        void resume() override;
};
