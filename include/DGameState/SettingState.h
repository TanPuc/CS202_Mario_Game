#pragma once
#include "DCore/GameState.h"
#include "DGameState/GameStateManager.h"
#include "DGUI/GUIManager.h"

class SettingState : public GameState
{
private:
    GameStateManager *gsm;
    GUIManager& guiManager;

    Rectangle musicSliderBar;
    Rectangle sfxSliderBar;
    Rectangle musicSliderHandle;
    Rectangle sfxSliderHandle;

    bool isDraggingMusic = false;
    bool isDraggingSFX = false;

public:
    SettingState(GameStateManager *manager);
    
    void enter() override;
    void exit() override;
    void update() override;
    void draw() override;
};
