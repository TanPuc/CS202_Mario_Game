#include "DGameState/LevelState.h"
#include "DGUI/Button.h"
#include "DGameState/MenuState.h"
#include "DGameState/GetReadyState.h"
#include "DCore/ResourceManager.h"
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
    Font font = ResourceManager::GetInstance().GetGameFont();
    float fontSize = 50.0f;
    float spacing = 3.0f;

    const char* title = "CHOOSE LEVEL";
    Vector2 titleSize = MeasureTextEx(font, title, fontSize, spacing);

    float titleX = (GetScreenWidth() - titleSize.x) / 2.0f;
    float titleY = 50.0f;

    DrawTextEx(font, title, {titleX, titleY}, fontSize, spacing, WHITE);
    guiManager.draw();
}