#pragma once
#include "DCore/GameState.h"
#include "DGameState/GameStateManager.h"
#include "DGUI/GUIManager.h"

class CharacterState : public GameState
{
    private:
        GameStateManager* gsm;
        GUIManager& guiManager;

        Texture2D marioChoice;
        Texture2D luigiChoice;

    public:
        CharacterState (GameStateManager* manager);

        void enter() override;
        void exit() override;
        void update() override;
        void draw() override;

};