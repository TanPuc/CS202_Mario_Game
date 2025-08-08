#include "DGameState/GameOverState.h"
#include "DGUI/Button.h"
#include "DGameState/MenuState.h"
#include <iostream>

GameOverState::GameOverState(GameStateManager* manager): gsm(manager), guiManager(GUIManager::getInstance()){}

void GameOverState::enter()
{
    std::cout<<"Entering Game Over State\n";

    gsm->getContext().lives = 3;

    guiManager.addElement(new Button({300, 350}, {200, 50}, "MAIN MENU",
        [this] ()
        {
            this->gsm->changeState(new MenuState(this->gsm));
        }
    ));
}

void GameOverState::exit()
{
    std::cout<<"Exiting Game Over State";
    guiManager.clearElements();
}

void GameOverState::update()
{
    guiManager.handleInput();
}

void GameOverState::draw()
{
    ClearBackground(BLACK);
    const char* text = "GAME OVER";
    float textWidth  =MeasureText(text, 80);
    DrawText(text, GetScreenWidth()/2 - textWidth/2, 200, 80, WHITE);
    guiManager.draw();
}