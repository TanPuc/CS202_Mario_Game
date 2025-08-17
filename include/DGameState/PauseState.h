#pragma once
#include "DCore/GameState.h"
#include "DGameState/GameStateManager.h"

class GUIManager;

class PauseState : public GameState
{
private:
    GameStateManager* gsm;
    GUIManager& guiManager;

    int currentWorld;
    int currentLevel;

public:
    PauseState(GameStateManager* manager, int world, int level);
    ~PauseState();

    void enter() override;
    void exit() override;
    void update() override;
    void draw() override;
};