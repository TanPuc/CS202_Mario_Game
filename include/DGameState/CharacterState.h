#pragma once
#include "DCore/GameState.h"
#include "DGameState/GameStateManager.h"
#include "DGUI/GUIManager.h"
#include <memory>
#include "raylib.h"

class ImageButton;

enum class Character
{
    NONE,
    MARIO,
    LUIGI
};

class CharacterState : public GameState
{
    private:
        GameStateManager* gsm;
        GUIManager& guiManager;

        Texture2D marioChoice;
        Texture2D luigiChoice;

        Texture2D onButtonTexture;

        Texture2D characterTexture;

        Rectangle marioHotspot;
        Rectangle luigiHotspot;

        Character hoveredCharacter = Character::NONE;
        Character selectedCharacter = Character::MARIO;

        Texture2D buttonTexture;

        void buildGUI();

    public:
        CharacterState (GameStateManager* manager);

        void enter() override;
        void exit() override;
        void update() override;
        void draw() override;
        void resume() override; 

};