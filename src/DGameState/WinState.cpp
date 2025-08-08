#include "DGameState/WinState.h"
#include "DGUI/Button.h"
#include "DGameState/MenuState.h"
#include <iostream>
#include <cmath> 

WinState::WinState(GameStateManager* manager): gsm(manager), guiManager(GUIManager::getInstance()), timer(0.0f) {}

void WinState::enter() {
    std::cout << "Entering Win State\n";
    gsm->getContext().lives = 3;

    guiManager.addElement(new Button({300, 300}, {200, 50}, "PLAY AGAIN",
        [this]() {
            this->gsm->changeState(new MenuState(this->gsm));
        }
    ));

    guiManager.addElement(new Button({300, 370}, {200, 50}, "QUIT",
        [this]() {
            this->gsm->requestExit();
        }
    ));
}

void WinState::exit() 
{
    std::cout << "Exiting Win State\n";
    guiManager.clearElements();
}

void WinState::update() {
    timer += GetFrameTime();
    guiManager.handleInput();
}

void WinState::draw() {
    ClearBackground(DARKBLUE);

    //BLING BLING
    float alpha = (sinf(timer * 4.0f) + 1.0f) / 2.0f;
    Color textColor = Fade(YELLOW, alpha);

    const char* text1 = "CONGRATULATIONS!";
    const char* text2 = "YOU ARE A SUPER PLAYER!";
    float textWidth1 = MeasureText(text1, 50);
    float textWidth2 = MeasureText(text2, 30);

    DrawText(text1, GetScreenWidth() / 2 - textWidth1 / 2, 150, 50, textColor);
    DrawText(text2, GetScreenWidth() / 2 - textWidth2 / 2, 220, 30, WHITE);
    
    guiManager.draw();
}