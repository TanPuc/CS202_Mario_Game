#include "DGameState/LevelState.h"
#include "DGUI/Button.h"
#include "DGameState/MenuState.h"
#include "DGameState/GetReadyState.h"
#include <iostream>

LevelState::LevelState(GameStateManager* manager): gsm(manager), guiManager(GUIManager::getInstance()) {}

void LevelState::enter()
{
    std::cout<<"Entering Choose Level State\n";

    //1-1
    guiManager.addElement(new Button({300, 150}, {200, 50}, "WORLD 1-1",
        [this] ()
        {
            this->gsm->changeState(new GetReadyState(this->gsm, 1, 1));
        }
    ));

    //1-2
    guiManager.addElement(new Button({300, 220}, {200, 50}, "WORLD 1-2",
        [this] ()
        {
            this->gsm->changeState(new GetReadyState(this->gsm, 1, 2));
        }
    ));

    //1-3
    guiManager.addElement(new Button({300, 290}, {200, 50}, "WORLD 1-3",
        [this] ()
        {
            this->gsm->changeState(new GetReadyState(this->gsm, 1, 3));
        }
    ));

    //BACK
    guiManager.addElement(new Button({300, 400}, {200, 50}, "BACK",
        [this] ()
        {
            this->gsm->changeState(new MenuState(this->gsm));
        }
    ));
}

void LevelState::exit()
{
    std::cout<<"Exiting Choose Level State\n";
    guiManager.clearElements();
}

void LevelState::update()
{
    guiManager.handleInput();
}

void LevelState::draw()
{
    ClearBackground(BLACK);
    DrawText("LEVEL SELECT", 250, 50, 50, WHITE);
    guiManager.draw();
}