#pragma once
#include "DCore/GameState.h"
#include "DGameState/GameStateManager.h"
#include "DGUI/GUIManager.h"

class WinState : public GameState 
{
private:
    GameStateManager* gsm;
    GUIManager& guiManager;
    float timer; 

public:
    WinState(GameStateManager* manager);

    void enter() override;
    void exit() override;
    void update() override;
    void draw() override;
};
