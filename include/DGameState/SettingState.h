#pragma once
#include "DCore/GameState.h"
#include "DGameState/GameStateManager.h"
#include "DGUI/GUIManager.h"
#include "DGUI/ImageButton.h"
#include "raylib.h"

class SettingState : public GameState
{
private:
    GameStateManager *gsm;
    GUIManager& guiManager;

    Rectangle musicBarRect;
    Rectangle sfxBarRect;

    std::vector<Texture2D> volumeBarTextures;
    // Rectangle musicSliderHandle;
    // Rectangle sfxSliderHandle;

    bool isDraggingMusic = false;
    bool isDraggingSFX = false;

    std::unique_ptr<ImageButton> musicMuteButton;
    std::unique_ptr<ImageButton> sfxMuteButton;

    Texture2D buttonTexture;
    Texture2D soundOnIcon;
    Texture2D soundOffIcon;
    Texture2D settingTexture;

    void buildGUI();

public:
    SettingState(GameStateManager *manager);
    
    void enter() override;
    void exit() override;
    void update() override;
    void draw() override;
    void resume() override;
};
