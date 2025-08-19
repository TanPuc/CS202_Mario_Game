#include "DGameState/LevelState.h"
#include "DGUI/Button.h"
#include "DGUI/ImageButton.h"
#include "DGameState/MenuState.h"
#include "DGameState/GetReadyState.h"
#include "DCore/ResourceManager.h"
#include <iostream>

LevelState::LevelState(GameStateManager* manager): gsm(manager), guiManager(GUIManager::getInstance()) {}

void LevelState::buildGUI()
{
    guiManager.clearElements();
    float aspectRatio = (float)buttonTexture.width / (float)buttonTexture.height;
    float buttonWidth = 170.0f;
    float buttonHeight = buttonWidth / aspectRatio;
    Vector2 buttonSize = { buttonWidth, buttonHeight };
    float startX = 90.0f;
    float startY = 150.0f;
    float gapY = 60.0f;

    //1-1
    guiManager.addElement(new ImageButton({startX, startY}, buttonSize, buttonTexture, "WORLD 1-1",
        [this] ()
        {
            this->gsm->changeState(new GetReadyState(this->gsm, 1, 1, GetReadyReason::NEW_GAME));
        }
    ));

    //1-2
    guiManager.addElement(new ImageButton({startX, startY + gapY}, buttonSize, buttonTexture, "WORLD 1-2",
        [this] ()
        {
            this->gsm->changeState(new GetReadyState(this->gsm, 1, 2, GetReadyReason::NEW_GAME));
        }
    ));

    //1-3
    guiManager.addElement(new ImageButton({startX, startY + gapY * 2}, buttonSize, buttonTexture, "WORLD 1-3",
        [this] ()
        {
            this->gsm->changeState(new GetReadyState(this->gsm, 1, 3, GetReadyReason::NEW_GAME));
        }
    ));

    //BACK
    guiManager.addElement(new ImageButton({startX, startY + gapY * 3.5f}, buttonSize, buttonTexture, "BACK",
        [this] ()
        {
            this->gsm->changeState(new MenuState(this->gsm));
        }
    ));
}
void LevelState::enter()
{
    std::cout<<"Entering Choose Level State\n";
    buttonTexture = LoadTexture("assets/button.png");
    levelTexture = LoadTexture("assets/levelBoard.png");
    titleTexture = LoadTexture("assets/titleBg.png");
    buildGUI();
}

void LevelState::exit()
{
    std::cout<<"Exiting Choose Level State\n";
    guiManager.clearElements();
    UnloadTexture(buttonTexture);
    UnloadTexture(levelTexture);
    UnloadTexture(titleTexture);
}

void LevelState::update()
{
    guiManager.handleInput();
}

void LevelState::draw()
{
    float aspectRatio = (float)levelTexture.width / (float)levelTexture.height;
    float backgroundWidth = 210.0f;
    float backgroundHeight = backgroundWidth / aspectRatio;
    Vector2 backgroundSize = { backgroundWidth, backgroundHeight };
    Rectangle sourceRec = { 0.0f, 0.0f, (float)levelTexture.width, (float)levelTexture.height };
    Rectangle destRec = { 70, 120, backgroundSize.x, backgroundSize.y };
    Vector2 origin = { 0, 0 };
    DrawTexturePro(levelTexture, sourceRec, destRec, origin, 0.0f, WHITE);

    float titleAspectRatio = (float)titleTexture.width / (float)titleTexture.height;
    float titleWidth = 210.0f;
    float titleHeight = titleWidth / titleAspectRatio;
    Vector2 titleBgSize = { titleWidth, titleHeight };
    Rectangle titleSourceRec = { 0.0f, 0.0f, (float)titleTexture.width, (float)titleTexture.height };
    Rectangle titleDestRec = { 75, 80, titleBgSize.x, titleBgSize.y };
    Vector2 titleOrigin = { 0, 0 };
    DrawTexturePro(titleTexture, titleSourceRec, titleDestRec, titleOrigin, 0.0f, WHITE);

    Font font = ResourceManager::GetInstance().GetGameFont();
    float fontSize = 30.0f;
    float spacing = 3.0f;

    const char* title = "LEVEL";
    Vector2 titleSize = MeasureTextEx(font, title, fontSize, spacing);

    float titleX = 75.0f + (titleBgSize.x - titleSize.x) / 2.0f;
    float titleY = 80.0f + (titleBgSize.y - titleSize.y) / 2.0f;

    DrawTextEx(font, title, {titleX + 3, titleY + 3}, fontSize, spacing, Fade(BLACK, 0.5f));
    DrawTextEx(font, title, {titleX, titleY}, fontSize, spacing, WHITE);
    guiManager.draw();
}

void LevelState::resume()
{
    std::cout << "Resuming Level State\n";
    buildGUI();
}