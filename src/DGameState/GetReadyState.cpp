#include "DGameState/GetReadyState.h"
#include "DGameState/PlayingState.h"
#include "DCore/ResourceManager.h"
#include "DCore/SoundManager.h"
#include "DCore/GameData.h"

GetReadyState::GetReadyState(GameStateManager* manager, int world, int level, GetReadyReason reason)
    :gsm(manager), targetWorld(world), targetLevel(level), reason(reason) {}

void GetReadyState::enter()
{
    SoundManager::getInstance().stopMusic();
    if(reason == GetReadyReason::NEW_GAME)
        SoundManager::getInstance().playSound(SoundEffect::LEVEL_START);
    else if(reason == GetReadyReason::RESPAWN)
        SoundManager::getInstance().playSound(SoundEffect::PLAYER_DOWN);

    lifeIcon = LoadTexture("assets/mario.png");
    coinIcon = LoadTexture("assets/mario.png");
    hudManager = std::make_unique<HUDManager>(lifeIcon, coinIcon);
    hudManager->syncWithContext(gsm->getContext());
    hudManager->updateWorld(targetWorld, targetLevel);
}

void GetReadyState::exit() 
{
    UnloadTexture(lifeIcon);
    UnloadTexture(coinIcon);
}

void GetReadyState::update() 
{
    timer -= GetFrameTime();
    if (timer <= 0.0f) 
    {
        GameData dataToLoad;
        
        dataToLoad.worldNum = this->targetWorld;
        dataToLoad.levelNum = this->targetLevel;
        dataToLoad.lives = gsm->getContext().lives;

        gsm->changeState(new PlayingState(gsm, dataToLoad));
    }
}

void GetReadyState::draw() 
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
    hudManager->draw();

    Font font = ResourceManager::GetInstance().GetGameFont();
    float fontSize = 30.0f;
    float spacing = 2.0f;

    DrawTextureEx(lifeIcon, {GetScreenWidth()/2.0f - 50, GetScreenHeight()/2.0f - 16}, 0.0, 2.0, WHITE);
    std::string livesText = "x" + std::to_string(gsm->getContext().lives);
    DrawTextEx(font, livesText.c_str(), {GetScreenWidth()/2.0f + 10, GetScreenHeight()/2.0f - 10}, fontSize, spacing, WHITE);
    //DrawText(livesText.c_str(), GetScreenWidth()/2.0f + 10, GetScreenHeight()/2.0f - 10, 30, WHITE);
}
