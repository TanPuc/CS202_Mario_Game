#pragma once
#include "DCore/GameState.h"
#include "DGameState/GameStateManager.h"
#include "raylib.h"

class GUIManager;

class PauseState : public GameState
{
private:
    GameStateManager* gsm;
    GUIManager& guiManager;

    int currentWorld;
    int currentLevel;

    Texture2D buttonTexture;
    Texture2D pauseTexture;

    void buildGUI();

public:
    PauseState(GameStateManager* manager, int world, int level);
    ~PauseState();

    void enter() override;
    void exit() override;
    void update() override;
    void draw() override;
    void resume() override;
    bool isOpaque() const override { return false; }
};