#include "DGameState/GameOverState.h"
#include "DGUI/Button.h"
#include "DGameState/MenuState.h"
#include "DCore/ResourceManager.h"
#include "DCore/SoundManager.h"
#include "DGUI/ImageButton.h"
#include <iostream>

GameOverState::GameOverState(GameStateManager* manager): gsm(manager), guiManager(GUIManager::getInstance()){}

void GameOverState::buildGUI()
{
    guiManager.clearElements();

    float aspectRatio = (float)buttonTexture.width / (float)buttonTexture.height;
    float buttonWidth = 250.0f;
    float buttonHeight = buttonWidth / aspectRatio;
    Vector2 buttonSize = { buttonWidth, buttonHeight };

    guiManager.addElement(new ImageButton({300, 350}, buttonSize, buttonTexture, "MAIN MENU",
        [this] ()
        {
            this->gsm->changeState(new MenuState(this->gsm));
        }
    ));
}

void GameOverState::enter()
{
    std::cout<<"Entering Game Over State\n";
    buttonTexture = LoadTexture("assets/button.png");
    SoundManager::getInstance().stopMusic();
    SoundManager::getInstance().playSound(SoundEffect::GAME_OVER);
    gsm->getContext().lives = 3;
    buildGUI();
}

void GameOverState::exit()
{
    std::cout<<"Exiting Game Over State";
    guiManager.clearElements();
    UnloadTexture(buttonTexture);
}

void GameOverState::update()
{
    guiManager.handleInput();
}

void GameOverState::draw()
{
    ClearBackground(BLACK);
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
    Font font = ResourceManager::GetInstance().GetGameFont();
    const char* text = "GAME OVER";
    float fontSize = 80.0f;
    float spacing = 5.0f;

    Vector2 textSize = MeasureTextEx(font, text, fontSize, spacing);
    DrawTextEx(font, text, {GetScreenWidth() / 2.0f - textSize.x / 2, 200}, fontSize, spacing, WHITE);
    
    // float textWidth  =MeasureText(text, 80);
    // DrawText(text, GetScreenWidth()/2 - textWidth/2, 200, 80, WHITE);
    guiManager.draw();
}

void GameOverState::resume()
{
    std::cout << "Resuming Game Over State\n";
    buildGUI();
}