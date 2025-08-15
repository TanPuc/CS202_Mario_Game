#include "DGameState/MenuState.h"
#include "DGUI/Button.h" 
#include "DGUI/UIImage.h"  
#include "DGameState/PlayingState.h"
#include "DGameState/CharacterState.h"
#include "DGameState/LevelState.h"
#include "DGameState/GetReadyState.h"
#include "DCore/ResourceManager.h"
#include "DGameState/SettingState.h"
#include <iostream>
#include <string>
#include <vector>

MenuState::MenuState(GameStateManager* gameStateManager) : gsm(gameStateManager), guiManager(GUIManager::getInstance()) {}

void MenuState::enter() 
{
    std::cout << "Entering Menu State\n";
    guiManager.clearElements();
    
    Font font = ResourceManager::GetInstance().GetGameFont();
    const std::vector<std::string> buttonLabels =
    {
        "PLAY",
        "LEVEL SELECT",
        "CHARACTERS",
        "SETTINGS",
        "QUIT"
    };

    const float fontSize = 20.0f;
    const float spacing = 1.0f;
    const Vector2 padding = {20, 15};
    float maxTextWidth = 0;

    for (const auto& label : buttonLabels) 
    {
        float currentTextWidth = MeasureTextEx(font, label.c_str(), fontSize, spacing).x;
        if (currentTextWidth > maxTextWidth) 
        {
            maxTextWidth = currentTextWidth;
        }
    }

    Vector2 buttonSize =
    {
        maxTextWidth + padding.x * 2,
        MeasureTextEx(font, "A", fontSize, spacing).y + padding.y * 2
    };

    background = LoadTexture("assets/menu_background.png"); 

    //Button
    float startY = 120.0f;
    float gapY = 60.0f;
    float startX = GetScreenHeight() / 2.0f - buttonSize.x / 2.0f;

    guiManager.addElement(new Button({startX, startY}, buttonSize, buttonLabels[0],
        [this]() 
        { 
            this->gsm->changeState(new GetReadyState(this->gsm, 1, 1)); 
        }
    ));

    guiManager.addElement(new Button({startX, startY + gapY}, buttonSize, buttonLabels[1],
        [this]()
        {
            this->gsm->changeState(new LevelState(this->gsm));
        }
    ));

    guiManager.addElement(new Button({startX, startY + gapY * 2}, buttonSize, buttonLabels[2],
        [this]()
        { 
            this->gsm->changeState(new CharacterState(this->gsm)); 
        }
    ));

    guiManager.addElement(new Button({startX, startY + gapY * 3}, buttonSize, buttonLabels[3],
        [this]()
        {
            this->gsm->pushState(new SettingState(this->gsm));
        }
    ));

    guiManager.addElement(new Button({startX, startY + gapY * 4}, buttonSize, buttonLabels[4],
        [this]()
        {
            this->gsm->requestExit();
        }
    ));
}

void MenuState::exit() 
{
    std::cout << "Exiting Menu State\n";
    guiManager.clearElements(); 
    UnloadTexture(background);
}

void MenuState::update() 
{
    guiManager.handleInput();
}

void MenuState::draw() 
{
    DrawTexture(background, 0, 0, WHITE);
    guiManager.draw();
}