#include "DGameState/CharacterState.h"
#include "DGUI/Button.h"
#include "DGameState/MenuState.h" 
#include <iostream>

CharacterState::CharacterState(GameStateManager* manager): gsm(manager), guiManager(GUIManager::getInstance()){}

void CharacterState::enter()
{
    std::cout<<"Entering Character State\n";
    marioChoice = LoadTexture("assets/mario.png");
    luigiChoice = LoadTexture("assets/mario.png");
    
    //Button to choose MARIO
    guiManager.addElement(new Button({150,200}, {150, 200}, "MARIO",
        [this] ()
        {
            std::cout<<"Selected Mario\n";
            this->gsm->getContext().selectedCharacter = "mario";
            this->gsm->changeState(new MenuState(this->gsm));
        }
    ));

    //Button to choose Luigi
    guiManager.addElement(new Button({500,200}, {150, 200}, "LUIGI",
        [this] ()
        {
            std::cout<<"Selected Luigi\n";
            this->gsm->getContext().selectedCharacter = "luigi";
            this->gsm->changeState(new MenuState(this->gsm));
        }
    ));

    //Back
    guiManager.addElement(new Button({300, 420}, {200, 50}, "BACK",
        [this] ()
        {
            this->gsm->changeState(new MenuState(this->gsm));
        }
    ));
}

void CharacterState::exit()
{
    std::cout<<"Exiting Choose Character State\n";
    guiManager.clearElements();
    UnloadTexture(marioChoice);
    UnloadTexture(luigiChoice);
}

void CharacterState::update()
{
    guiManager.handleInput();
}

void CharacterState::draw()
{
    ClearBackground(BLACK);
    DrawText("CHOOSE YOUR CHARACTER", 150, 80, 40, WHITE);

    DrawTexture(marioChoice, 150, 200, WHITE);
    DrawTexture(luigiChoice, 150, 200, WHITE);

    if(gsm->getContext().selectedCharacter == "mario")
    {
        DrawRectangleLines(145,195,160,210,YELLOW);
    }
    else
    {
        DrawRectangleLines(495,195,160,210,YELLOW);
    }

    guiManager.draw();
}

