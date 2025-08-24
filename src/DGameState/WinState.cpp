#include "DGameState/WinState.h"
#include "DGUI/Button.h"
#include "DGUI/ImageButton.h"
#include "DGameState/MenuState.h"
#include "DCore/ResourceManager.h"
#include <iostream>
#include <cmath> 

WinState::WinState(GameStateManager* manager): gsm(manager), guiManager(GUIManager::getInstance()), timer(0.0f) {}

void WinState::buildGUI()
{
    float aspectRatio = (float)buttonTexture.width / (float)buttonTexture.height;
    float buttonWidth = 250.0f;
    float buttonHeight = buttonWidth / aspectRatio;
    Vector2 buttonSize = { buttonWidth, buttonHeight };
    guiManager.addElement(new ImageButton({300, 300}, buttonSize, buttonTexture, "PLAY AGAIN",
        [this]() {
            this->gsm->changeState(new MenuState(this->gsm));
        }
    ));

    guiManager.addElement(new ImageButton({300, 370}, buttonSize, buttonTexture, "QUIT",
        [this]() {
            this->gsm->requestExit();
        }
    ));
}
void WinState::enter() {
    std::cout << "Entering Win State\n";
    buttonTexture = LoadTexture("assets/button.png");
    gsm->getContext().lives = 3;
    timer = 0.0f;
    buildGUI();
}

void WinState::exit() 
{
    std::cout << "Exiting Win State\n";
    guiManager.clearElements();
    UnloadTexture(buttonTexture);
}

void WinState::update() {
    timer += GetFrameTime();
    guiManager.handleInput();
}

void WinState::draw() {
    ClearBackground(DARKBLUE);
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), DARKBLUE);

    //BLING BLING
    Font font = ResourceManager::GetInstance().GetGameFont();
    float alpha = (sinf(timer * 4.0f) + 1.0f) / 2.0f;
    Color textColor = Fade(YELLOW, alpha);

    const char* text1 = "CONGRATULATIONS!";
    const char* text2 = "YOU ARE A SUPER PLAYER!";

    // float textWidth1 = MeasureText(text1, 50);
    // float textWidth2 = MeasureText(text2, 30);

    // DrawText(text1, GetScreenWidth() / 2 - textWidth1 / 2, 150, 50, textColor);
    // DrawText(text2, GetScreenWidth() / 2 - textWidth2 / 2, 220, 30, WHITE);
    
    Vector2 size1 = MeasureTextEx(font, text1, 50, 3.0f);
    Vector2 size2 = MeasureTextEx(font, text2, 30, 2.0f);

    DrawTextEx(font, text1, {GetScreenWidth()/2.0f - size1.x/2, 150}, 50, 3.0f, textColor);
    DrawTextEx(font, text2, {GetScreenWidth()/2.0f - size2.x/2, 220}, 30, 2.0f, GOLD);

    guiManager.draw();
}
void WinState::resume() 
{
    std::cout << "Resuming Win State\n";
    buildGUI();
}