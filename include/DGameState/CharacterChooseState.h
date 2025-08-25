#pragma once
#include "DCore/GameState.h"
#include "DGameState/GameStateManager.h"
#include "DGUI/GUIManager.h"
#include <memory>
#include "raylib.h"

class ImageButton;

class CharacterChooseState : public GameState
{
private:
    GameStateManager *gsm;
    GUIManager &guiManager;

    Texture2D marioChoice;
    Texture2D luigiChoice;

    Texture2D onButtonTexture;

    Texture2D characterTexture;

    Rectangle marioHotspot;
    Rectangle luigiHotspot;

    CHARACTER hoveredCharacter = CHARACTER::NONE;
    CHARACTER selectedCharacter = CHARACTER::MARIO;

    Texture2D buttonTexture;

    void buildGUI();

public:
    CharacterChooseState(GameStateManager *manager);

    void enter() override;
    void exit() override;
    void update() override;
    void draw() override;
    void resume() override;
};