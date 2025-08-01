#include "DGameState/MenuState.h"
#include "DGUI/Button.h" 
#include "DGUI/UIImage.h"  
#include "DGameState/PlayingState.h"
#include <iostream>

MenuState::MenuState(GameStateManager* gameStateManager) : gsm(gameStateManager), guiManager(GUIManager::getInstance()) {}

void MenuState::enter() 
{
    std::cout << "Entering Menu State\n";
    background = LoadTexture("assets/menu_background.png"); 
    guiManager.addElement(new Button({300, 250}, {200, 50}, "PLAY GAME", 
        [this]() 
        { 
            this->gsm->changeState(new PlayingState(this->gsm)); 
        }
    ));
    guiManager.addElement(new Button({300, 320}, {200, 50}, "QUIT", 
        []() 
        { 
            std::cout << "Quit button pressed!\n";
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