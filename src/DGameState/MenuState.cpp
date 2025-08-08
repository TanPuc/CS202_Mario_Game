#include "DGameState/MenuState.h"
#include "DGUI/Button.h" 
#include "DGUI/UIImage.h"  
#include "DGameState/PlayingState.h"
#include "DGameState/CharacterState.h"
#include "DGameState/LevelState.h"
#include "DGameState/GetReadyState.h"
#include <iostream>

MenuState::MenuState(GameStateManager* gameStateManager) : gsm(gameStateManager), guiManager(GUIManager::getInstance()) {}

void MenuState::enter() 
{
    std::cout << "Entering Menu State\n";
    background = LoadTexture("assets/menu_background.png"); 
    guiManager.addElement(new Button({300, 200}, {200, 50}, "PLAY", 
        [this]() 
        { 
            this->gsm->changeState(new GetReadyState(gsm, 1, 1)); 
        }
    ));

    guiManager.addElement(new Button({300, 270}, {200, 50}, "LEVEL SELECT", 
        [this]() 
        { 
            this->gsm->changeState(new LevelState(gsm)); 
        }
    ));

    guiManager.addElement(new Button({300, 340}, {200, 50}, "CHARACTERS", 
        [this]() 
        { 
            this->gsm->changeState(new CharacterState(gsm)); 
        }
    ));

    guiManager.addElement(new Button({300, 410}, {200, 50}, "QUIT", 
        [this]() 
        { 
            gsm->requestExit();
        }
    ));
}

void MenuState::exit() {
    std::cout << "Exiting Menu State\n";
    guiManager.clearElements(); 
    UnloadTexture(background);
}

void MenuState::update() {
    guiManager.handleInput();
}

void MenuState::draw() {
    DrawTexture(background, 0, 0, WHITE);
    guiManager.draw();
}