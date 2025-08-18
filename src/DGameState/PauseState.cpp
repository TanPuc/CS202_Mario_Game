#include "DGameState/PauseState.h"
#include "DGUI/GUIManager.h"
#include "DGUI/Button.h"
#include "DGUI/ImageButton.h"
#include "DCore/ResourceManager.h"
#include "DGameState/MenuState.h"
#include "DGameState/GetReadyState.h"
#include "DGameState/SettingState.h"
#include "DCore/SaveManager.h"
#include "DGameState/PlayingState.h"
#include <iostream>
#include <vector>
#include <string>

PauseState::PauseState(GameStateManager* manager, int world, int level)
    : gsm(manager), currentWorld(world), currentLevel(level), guiManager(GUIManager::getInstance()){}

PauseState::~PauseState() {}

void PauseState::buildGUI()
{
    guiManager.clearElements();

    
    Font font = ResourceManager::GetInstance().GetGameFont();
    const std::vector<std::string> buttonLabels =
    {
        "RESUME",
        "RESTART",
        "SETTINGS",
        "SAVE GAME",
        "MAIN MENU"
    };

    // const float fontSize = 20.0f;
    // const Vector2 padding = {20, 15};
    // float maxTextWidth = 0.0f; 

    // for (const auto& label : buttonLabels)
    // {
    //     float currentTextWidth = MeasureTextEx(font, label.c_str(), fontSize, 1.0f).x;
    //     if (currentTextWidth > maxTextWidth)
    //         maxTextWidth = currentTextWidth;
    // }
    float aspectRatio = (float)buttonTexture.width / (float)buttonTexture.height;
    float buttonWidth = 170.0f;
    float buttonHeight = buttonWidth / aspectRatio;
    Vector2 buttonSize = { buttonWidth, buttonHeight };

    // Vector2 buttonSize = { maxTextWidth + padding.x * 2, 50.0f };
    float startX = (GetScreenWidth() - buttonSize.x) / 2.0f;
    float gapY = 60.0f;
    float startY = 180.0f;

    guiManager.addElement(new ImageButton({startX, startY}, buttonSize, buttonTexture, buttonLabels[0],
        [this]() 
        { 
            this->gsm->popState(); 
        }
    ));

    guiManager.addElement(new ImageButton({startX, startY + gapY}, buttonSize, buttonTexture, buttonLabels[1],
        [this]() 
        { 
            this->gsm->getContext().lives = 3; 
            this->gsm->changeState(new GetReadyState(this->gsm, this->currentWorld, this->currentLevel, GetReadyReason::NEW_GAME)); 
        }
    ));

    guiManager.addElement(new ImageButton({startX, startY + gapY * 2}, buttonSize, buttonTexture, buttonLabels[2],
        [this]() 
        { 
            this->gsm->pushState(new SettingState(this->gsm)); 
        }
    ));

    guiManager.addElement(new ImageButton({startX, startY + gapY * 3}, buttonSize, buttonTexture, buttonLabels[3],
        [this]() 
        { 
            if (auto playingState = gsm->findState<PlayingState>()) 
            { 
                playingState->saveGameData();
                std::cout << "Game saved successfully.\n";
            }
        }
    ));

    guiManager.addElement(new ImageButton({startX, startY + gapY * 4}, buttonSize, buttonTexture, buttonLabels[4],
        [this]() 
        { 
            this->gsm->changeState(new MenuState(this->gsm)); 
        }
    ));
}

void PauseState::enter()
{
    std::cout<<"Entering Pause State\n";
    buttonTexture = LoadTexture("assets/button.png");
    pauseTexture = LoadTexture("assets/levelBoard.png");
    buildGUI();
}

void PauseState::exit()
{
    std::cout << "Exiting Pause State\n";
    guiManager.clearElements();
    UnloadTexture(buttonTexture);
    UnloadTexture(pauseTexture);
}

void PauseState::update()
{
    guiManager.handleInput();
}

void PauseState::draw()
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.5f));

    float aspectRatio = (float)pauseTexture.width / (float)pauseTexture.height;
    float pauseWidth = 250.0f;
    float pauseHeight = pauseWidth / aspectRatio;
    Vector2 pauseSize = { pauseWidth, pauseHeight };
    Rectangle sourceRec = { 0.0f, 0.0f, (float)pauseTexture.width, (float)pauseTexture.height };
    Rectangle destRec = { (GetScreenWidth() - pauseSize.x) / 2, (GetScreenHeight() - pauseSize.y) / 2, pauseSize.x, pauseSize.y };
    Vector2 origin = { 0, 0 };
    DrawTexturePro(pauseTexture, sourceRec, destRec, origin, 0.0f, WHITE);

    Font font = ResourceManager::GetInstance().GetGameFont();
    const char* title = "PAUSED";
    Vector2 titleSize = MeasureTextEx(font, title, 40, 4.0f);
    DrawTextEx(font, title, {(GetScreenWidth() - titleSize.x) / 2 + 3, 103}, 40, 4.0f, Fade(BLACK, 0.5f));
    DrawTextEx(font, title, {(GetScreenWidth() - titleSize.x) / 2, 100}, 40, 4.0f, WHITE);
    guiManager.draw();
}

void PauseState::resume()
{
    std::cout << "Resuming Pause State\n";
    buildGUI();
}
