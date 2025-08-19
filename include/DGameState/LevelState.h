#pragma once
#include "DCore/GameState.h"
#include "DGameState/GameStateManager.h"
#include "DGUI/GUIManager.h"
#include "raylib.h"

class LevelState: public GameState
{
    private:
        GameStateManager* gsm;
        GUIManager& guiManager;

        Texture2D buttonTexture;
        Texture2D levelTexture;
        Texture2D titleTexture;

        void buildGUI();
    public:
        LevelState(GameStateManager* manager);

        void enter() override;
        void exit() override;
        void update() override;
        void draw() override;
        void resume() override;
};