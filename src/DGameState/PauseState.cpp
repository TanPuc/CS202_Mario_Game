#include "DGameState/PauseState.h"
#include "DGUI/GUIManager.h"
#include "DGUI/Button.h"
#include "DCore/ResourceManager.h"
#include "DGameState/MenuState.h"
#include "DGameState/GetReadyState.h"
#include <iostream>
#include <vector>
#include <string>

PauseState::PauseState(GameStateManager* manager, int world, int level)
    : gsm(manager), currentWorld(world), currentLevel(level), guiManager(GUIManager::getInstance()){}

PauseState::~PauseState() {}

void PauseState::enter()
{
    std::cout<<"Entering Pause State\n";
    guiManager.clearElements();

    Font font = ResourceManager::GetInstance().GetGameFont();
    const std::vector<std::string> buttonLabels =
    {
        "RESUME",
        "RESTART",
        "MAIN MENU"
    };

    const float fontSize = 20.0f;
    const Vector2 padding = {20, 15};
    float maxTextWidth = 0.0f; 

    for (const auto& label : buttonLabels)
    {
        float currentTextWidth = MeasureTextEx(font, label.c_str(), fontSize, 1.0f).x;
        if (currentTextWidth > maxTextWidth)
            maxTextWidth = currentTextWidth;
    }

    Vector2 buttonSize = { maxTextWidth + padding.x * 2, 50.0f };
    float startX = (GetScreenWidth() - buttonSize.x) / 2.0f;\
    float gapY = 70.0f;
    float startY = 200.0f;

    guiManager.addElement(new Button({startX, startY}, buttonSize, buttonLabels[0],
        [this]() 
        { 
            this->gsm->popState(); 
        }
    ));

    guiManager.addElement(new Button({startX, startY + gapY}, buttonSize, buttonLabels[1],
        [this]() 
        { 
            this->gsm->changeState(new GetReadyState(this->gsm, currentWorld, currentLevel)); 
        }
    ));

    guiManager.addElement(new Button({startX, startY + gapY * 2}, buttonSize, buttonLabels[2],
        [this]() 
        { 
            this->gsm->changeState(new MenuState(this->gsm)); 
        }
    ));
}

void PauseState::exit()
{
    std::cout << "Exiting Pause State\n";
    guiManager.clearElements();
}

void PauseState::update()
{
    guiManager.handleInput();
}

void PauseState::draw()
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.5f));
    
    Font font = ResourceManager::GetInstance().GetGameFont();
    const char* title = "PAUSED";
    Vector2 titleSize = MeasureTextEx(font, title, 60, 4.0f);
    DrawTextEx(font, title, {(GetScreenWidth() - titleSize.x) / 2, 100}, 60, 4.0f, WHITE);
    guiManager.draw();
}


