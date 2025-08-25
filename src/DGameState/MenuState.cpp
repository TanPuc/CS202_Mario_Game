#include "DGameState/MenuState.h"
#include "DGUI/ImageButton.h"
#include "DGUI/UIImage.h"
#include "DGameState/PlayingState.h"
#include "DGameState/CharacterChooseState.h"
#include "DGameState/LevelState.h"
#include "DGameState/GetReadyState.h"
#include "DCore/ResourceManager.h"
#include "DGameState/SettingState.h"
#include "DCore/SoundManager.h"
#include "DGameState/SaveState.h"
#include <iostream>
#include <string>
#include <vector>

MenuState::MenuState(GameStateManager *gameStateManager) : gsm(gameStateManager), guiManager(GUIManager::getInstance()) {}

void MenuState::buildGUI()
{
    guiManager.clearElements();

    Font font = ResourceManager::GetInstance().GetGameFont();
    const std::vector<std::string> buttonLabels =
        {
            "LEVEL",
            "CHARACTERS",
            "SETTINGS",
            "QUIT",
            "PLAY"};

    // const float fontSize = 20.0f;
    // const float spacing = 1.0f;
    // const Vector2 padding = {20, 15};
    // float maxTextWidth = 0;

    // for (const auto& label : buttonLabels)
    // {
    //     float currentTextWidth = MeasureTextEx(font, label.c_str(), fontSize, spacing).x;
    //     if (currentTextWidth > maxTextWidth)
    //     {
    //         maxTextWidth = currentTextWidth;
    //     }
    // }

    // Vector2 buttonSize =
    // {
    //     maxTextWidth + padding.x * 2,
    //     MeasureTextEx(font, "A", fontSize, spacing).y + padding.y * 2
    // };

    // Button
    float aspectRatio = (float)buttonTexture.width / (float)buttonTexture.height;
    float buttonWidth = 170.0f;
    float buttonHeight = buttonWidth / aspectRatio;
    Vector2 buttonSize = {buttonWidth, buttonHeight};

    float startY = 300.0f;
    float gapY = 50.0f;
    float startX = 35.0f;

    guiManager.addElement(new ImageButton({startX, startY}, buttonSize, buttonTexture, buttonLabels[0],
                                          [this]()
                                          {
                                              this->gsm->changeState(new LevelState(this->gsm));
                                          }));

    guiManager.addElement(new ImageButton({startX, startY + gapY}, buttonSize, buttonTexture, buttonLabels[1],
                                          [this]()
                                          {
                                              this->gsm->changeState(new CharacterChooseState(this->gsm));
                                          }));

    guiManager.addElement(new ImageButton({startX + buttonWidth + 10, startY}, buttonSize, buttonTexture, buttonLabels[2],
                                          [this]()
                                          {
                                              this->gsm->pushState(new SettingState(this->gsm));
                                          }));

    guiManager.addElement(new ImageButton({startX + buttonWidth + 10, startY + gapY}, buttonSize, buttonTexture, buttonLabels[3],
                                          [this]()
                                          {
                                              this->gsm->requestExit();
                                          }));
    auto playButton = new ImageButton({startX + buttonWidth + 5 - (buttonSize.x * 1.3f) / 2, startY + gapY * 2}, {buttonSize.x * 1.3f, buttonSize.y * 1.3f}, buttonTexture, buttonLabels[4],
                                      [this]()
                                      {
                                          this->gsm->changeState(new SaveSlotState(this->gsm));
                                      });
    playButton->setFontSize(20.0f);
    guiManager.addElement(playButton);
}

void MenuState::playMenuMusic()
{
    if (!SoundManager::getInstance().isMusicCurrentlyPlaying())
    {
        SoundManager::getInstance().playMusic(MusicTrack::MAIN_THEME);
    }
}

void MenuState::enter()
{
    std::cout << "Entering Menu State\n";
    boardTexture = LoadTexture("assets/board.png");
    marioTitle = LoadTexture("assets/mario_title.png");
    buttonTexture = LoadTexture("assets/button.png");
    playMenuMusic();
    buildGUI();
}

void MenuState::exit()
{
    std::cout << "Exiting Menu State\n";
    guiManager.clearElements();
    UnloadTexture(heartTexture);
    UnloadTexture(buttonTexture);
    UnloadTexture(marioTitle);
    UnloadTexture(boardTexture);
}

void MenuState::update()
{
    guiManager.handleInput();
}

void MenuState::draw()
{
    // DrawTexture(background, 0, 0, WHITE);
    // float aspectRatio = (float)background.width / (float)background.height;
    // float backgroundWidth = 815.0f;
    // float backgroundHeight = backgroundWidth / aspectRatio;
    // Vector2 backgroundSize = { backgroundWidth, backgroundHeight };
    // Rectangle sourceRec = { 0.0f, 0.0f, (float)background.width, (float)background.height };
    // Rectangle destRec = { 0, 0, backgroundSize.x, backgroundSize.y };
    // Vector2 origin = { 0, 0 };
    // DrawTexturePro(background, sourceRec, destRec, origin, 0.0f, WHITE);

    float aspectRatio1 = (float)boardTexture.width / (float)boardTexture.height;
    float boardWidth1 = 350.0f;
    float boardHeight1 = boardWidth1 / aspectRatio1;
    Vector2 boardSize1 = {boardWidth1, boardHeight1};
    Rectangle sourceRec1 = {0.0f, 0.0f, (float)boardTexture.width, (float)boardTexture.height};
    Rectangle destRec1 = {30, 30, boardSize1.x, boardSize1.y};
    Vector2 origin1 = {0, 0};
    DrawTexturePro(boardTexture, sourceRec1, destRec1, origin1, 0.0f, WHITE);

    float aspectRatio2 = (float)marioTitle.width / (float)marioTitle.height;
    float titleWidth = 300.0f;
    float titleHeight = titleWidth / aspectRatio2;
    Vector2 titleSize = {titleWidth, titleHeight};
    Rectangle sourceRec2 = {0.0f, 0.0f, (float)marioTitle.width, (float)marioTitle.height};
    Rectangle destRec2 = {60, 80, titleSize.x, titleSize.y};
    Vector2 origin2 = {0, 0};
    DrawTexturePro(marioTitle, sourceRec2, destRec2, origin2, 0.0f, WHITE);

    guiManager.draw();
}

void MenuState::resume()
{
    std::cout << "Resuming Menu State\n";
    playMenuMusic();
    buildGUI();
}