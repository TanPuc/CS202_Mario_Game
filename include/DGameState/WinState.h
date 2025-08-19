#pragma once
#include "DCore/GameState.h"
#include "DGameState/GameStateManager.h"
#include "DGUI/GUIManager.h"
#include "raylib.h"

class WinState : public GameState 
{
private:
    GameStateManager* gsm;
    GUIManager& guiManager;
    float timer; 

    Texture2D buttonTexture;

    void buildGUI();

public:
    WinState(GameStateManager* manager);

    void enter() override;
    void exit() override;
    void update() override;
    void draw() override;
    void resume() override;
};
