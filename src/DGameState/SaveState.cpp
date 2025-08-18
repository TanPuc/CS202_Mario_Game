#include "DGameState/SaveState.h"
#include "DGUI/ImageButton.h"
#include "DCore/SaveManager.h"
#include "DGameState/GetReadyState.h"
#include "DGameState/PlayingState.h"
#include "DGameState/MenuState.h"
#include "DCore/GameData.h"
#include "DCore/ResourceManager.h"
#include <iostream>

SaveSlotState::SaveSlotState(GameStateManager *manager)
    : gsm(manager), guiManager(GUIManager::getInstance()), canLoadGame(false){}

void SaveSlotState::buildGUI()
{
    guiManager.clearElements();

    float aspectRatio = (float)buttonTexture.width / (float)buttonTexture.height;
    float buttonWidth = 170.0f;
    float buttonHeight = buttonWidth / aspectRatio;
    Vector2 buttonSize = { buttonWidth, buttonHeight };
    
    float screenCenterX = GetScreenWidth() / 2.0f;
    float startY = 150.0f;
    float gapY = buttonHeight + 20.0f;

    guiManager.addElement(new ImageButton({ screenCenterX - buttonWidth / 2, startY }, buttonSize, buttonTexture, "NEW GAME",
        [this]() {
            GameData newData;
            this->gsm->changeState(new GetReadyState(this->gsm, newData.worldNum, newData.levelNum, GetReadyReason::NEW_GAME));
        }
    ));

    // Load game
    auto loadButton = new ImageButton({ screenCenterX - buttonWidth / 2, startY + gapY }, buttonSize, buttonTexture, "LOAD GAME",
        [this]() 
        {
            GameData loadedData;
            
            if (SaveManager::loadGame(loadedData, "savegame.dat"))
            {
                this->gsm->changeState(new PlayingState(this->gsm, loadedData));
            } else 
            {
                std::cout << "Failed to load save file!" << std::endl;
            }
        }
    );

    if (!canLoadGame) 
    {
        loadButton->disable(); 
    }
    guiManager.addElement(loadButton);

    guiManager.addElement(new ImageButton({ screenCenterX - buttonWidth / 2, startY + gapY * 2 }, buttonSize, buttonTexture, "BACK",
        [this]() 
        {
            this->gsm->changeState(new MenuState(this->gsm));
        }
    ));

}

void SaveSlotState::enter()
{
    std::cout << "Entering Save Slot State\n";
    buttonTexture = LoadTexture("assets/button.png");
    canLoadGame = SaveManager::saveFileExists("savegame.dat");
    buildGUI();
}

void SaveSlotState::exit()
{
    std::cout << "Exiting Save Slot State\n";
    guiManager.clearElements();
    UnloadTexture(buttonTexture);
}

void SaveSlotState::update()
{
    guiManager.handleInput();
}

void SaveSlotState::draw()
{
    Font font = ResourceManager::GetInstance().GetGameFont();
    const char* title = "SELECT SLOT";
    Vector2 titleSize = MeasureTextEx(font, title, 50, 3.0f);
    DrawTextEx(font, title, {(GetScreenWidth() - titleSize.x) / 2.0f, 60}, 50, 3.0f, WHITE);

    guiManager.draw();
}

void SaveSlotState::resume()
{
    std::cout << "Resuming Save Slot State\n";
    buildGUI();
}
