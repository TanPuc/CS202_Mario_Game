#include "DGameState/CharacterChooseState.h"
#include "DGUI/Button.h"
#include "DGUI/ImageButton.h"
#include "DGameState/MenuState.h"
#include "DGameState/GetReadyState.h"
#include "DCore/ResourceManager.h"
#include "DCore/SoundManager.h"
#include "Physics.h"
#include <iostream>

CharacterChooseState::CharacterChooseState(GameStateManager *manager) : gsm(manager), guiManager(GUIManager::getInstance()) {}

void CharacterChooseState::buildGUI()
{
    guiManager.clearElements();
    //  //Button to choose MARIO
    // guiManager.addElement(new Button({150,200}, {150, 200}, "MARIO",
    //     [this] ()
    //     {
    //         std::cout<<"Selected Mario\n";
    //         this->gsm->getContext().selectedCharacter = "mario";
    //     }
    // ));

    // //Button to choose Luigi
    // guiManager.addElement(new Button({500,200}, {150, 200}, "LUIGI",
    //     [this] ()
    //     {
    //         std::cout<<"Selected Luigi\n";
    //         this->gsm->getContext().selectedCharacter = "luigi";
    //     }
    // ));

    // Back
    float aspectRatio = (float)buttonTexture.width / (float)buttonTexture.height;
    float buttonWidth = 170.0f;
    float buttonHeight = buttonWidth / aspectRatio;
    Vector2 buttonSize = {buttonWidth, buttonHeight};
    guiManager.addElement(new ImageButton({165, 250}, buttonSize, buttonTexture, "BACK",
                                          [this]()
                                          {
                                              this->gsm->changeState(new MenuState(this->gsm));
                                          }));
}

void CharacterChooseState::enter()
{
    std::cout << "Entering CHARACTER State\n";
    marioChoice = LoadTexture("assets/mario.png");
    luigiChoice = LoadTexture("assets/mario.png");
    buttonTexture = LoadTexture("assets/button.png");
    onButtonTexture = LoadTexture("assets/brightButton.png");
    characterTexture = LoadTexture("assets/characterBoard.png");

    if (gsm->getContext().selectedCharacter == "luigi")
    {
        selectedCharacter = CHARACTER::LUIGI;
        MAX_VELOCITY = MAX_VELOCITY_LUIGI;
        JUMP_FORCE = JUMP_FORCE_LUIGI;
    }
    else
    {
        selectedCharacter = CHARACTER::MARIO;
        MAX_VELOCITY = MAX_VELOCITY_MARIO;
        JUMP_FORCE = JUMP_FORCE_MARIO;
    }

    marioHotspot = {533, 150, 127, 220};
    luigiHotspot = {430, 140, 100, 240};

    buildGUI();
}

void CharacterChooseState::exit()
{
    std::cout << "Exiting Choose CHARACTER State\n";
    guiManager.clearElements();
    UnloadTexture(marioChoice);
    UnloadTexture(luigiChoice);
    UnloadTexture(buttonTexture);
    UnloadTexture(onButtonTexture);
    UnloadTexture(characterTexture);
    SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}

void CharacterChooseState::update()
{
    Vector2 mousePos = GetMousePosition();
    hoveredCharacter = CHARACTER::NONE;

    if (CheckCollisionPointRec(mousePos, marioHotspot))
    {
        hoveredCharacter = CHARACTER::MARIO;
    }
    if (CheckCollisionPointRec(mousePos, luigiHotspot))
    {
        hoveredCharacter = CHARACTER::LUIGI;
    }

    if (hoveredCharacter != CHARACTER::NONE)
    {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    }
    else
    {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (hoveredCharacter == CHARACTER::MARIO && selectedCharacter != CHARACTER::MARIO)
        {
            selectedCharacter = CHARACTER::MARIO;
            gsm->getContext().selectedCharacter = "mario";
            SoundManager::getInstance().playSound(SoundEffect::COIN);
        }
        if (hoveredCharacter == CHARACTER::LUIGI && selectedCharacter != CHARACTER::LUIGI)
        {
            selectedCharacter = CHARACTER::LUIGI;
            gsm->getContext().selectedCharacter = "luigi";
            SoundManager::getInstance().playSound(SoundEffect::COIN);
        }
    }
    guiManager.handleInput();
}

void CharacterChooseState::draw()
{
    Font font = ResourceManager::GetInstance().GetGameFont();

    float ratio = (float)characterTexture.width / (float)characterTexture.height;
    float boardWidth = 350.0f;
    float boardHeight = boardWidth / ratio;
    Vector2 boardSize = {boardWidth, boardHeight};
    Rectangle sourceRec = {0.0f, 0.0f, (float)characterTexture.width, (float)characterTexture.height};
    Rectangle destRec = {80, -15, boardSize.x, boardSize.y};
    Vector2 origin = {0, 0};
    DrawTexturePro(characterTexture, sourceRec, destRec, origin, 0.0f, WHITE);

    float fontSize = 25.0f;
    float spacing = 1.0f;

    const char *title = "CHARACTER";
    Vector2 titleSize = MeasureTextEx(font, title, fontSize, spacing);

    DrawTextEx(font, title, {80 + boardWidth / 2 - titleSize.x / 2 + 3, 123.0f}, fontSize, spacing, Fade(BLACK, 0.5f));
    DrawTextEx(font, title, {80 + boardWidth / 2 - titleSize.x / 2, 120.0f}, fontSize, spacing, WHITE);

    const char *descriptionText = "";
    Color textColor = GOLD;
    float descriptionFontSize = 20.0f;

    if (selectedCharacter == CHARACTER::MARIO)
    {
        descriptionText = "MARIO: \nRUN FASTER!";
    }
    else if (selectedCharacter == CHARACTER::LUIGI)
    {
        descriptionText = "LUIGI: \nJUMP HIGHER!";
    }

    Vector2 descriptionSize = MeasureTextEx(font, descriptionText, descriptionFontSize, spacing);
    DrawTextEx(font, descriptionText, {80 + boardWidth / 2 - descriptionSize.x / 2 + 3, 173.0f}, descriptionFontSize, 0.7, Fade(BLACK, 0.5f));
    DrawTextEx(font, descriptionText, {80 + boardWidth / 2 - descriptionSize.x / 2, 170.0f}, descriptionFontSize, 0.7, textColor);

    Texture2D marioIndicatorToDraw = (selectedCharacter == CHARACTER::MARIO) ? onButtonTexture : buttonTexture;
    Texture2D luigiIndicatorToDraw = (selectedCharacter == CHARACTER::LUIGI) ? onButtonTexture : buttonTexture;
    float aspectRatio = (float)buttonTexture.width / (float)buttonTexture.height;
    float buttonWidth = 70.0f;
    float buttonHeight = buttonWidth / aspectRatio;
    Vector2 buttonSize = {buttonWidth, buttonHeight};
    Rectangle sourceRec1 = {0.0f, 0.0f, (float)marioIndicatorToDraw.width, (float)marioIndicatorToDraw.height};
    Rectangle sourceRec2 = {0.0f, 0.0f, (float)luigiIndicatorToDraw.width, (float)luigiIndicatorToDraw.height};
    Rectangle destRec1 = {570, 370, buttonSize.x, buttonSize.y};
    Rectangle destRec2 = {445, 390, buttonSize.x, buttonSize.y};
    Vector2 origin1 = {0, 0};
    DrawTexturePro(marioIndicatorToDraw, sourceRec1, destRec1, origin1, 0.0f, WHITE);
    DrawTexturePro(luigiIndicatorToDraw, sourceRec2, destRec2, origin1, 0.0f, WHITE);

    // if (hoveredCharacter == CHARACTER::MARIO) {
    //     DrawRectangleRec(marioHotspot, Fade(YELLOW, 0.2f));
    // }
    // if (hoveredCharacter == CHARACTER::LUIGI) {
    //     DrawRectangleRec(luigiHotspot, Fade(YELLOW, 0.2f));
    // }

    // DrawTexture(marioChoice, 150, 200, WHITE);
    // DrawTexture(luigiChoice, 150, 200, WHITE);

    // if(gsm->getContext().selectedCharacter == "mario")
    // {
    //     DrawRectangleLines(145,195,160,210,YELLOW);
    // }
    // else
    // {
    //     DrawRectangleLines(495,195,160,210,YELLOW);
    // }

    guiManager.draw();
}

void CharacterChooseState::resume()
{
    std::cout << "Resuming CHARACTER State\n";
    buildGUI();
}