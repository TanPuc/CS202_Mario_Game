#include "DGameState/GetReadyState.h"
#include "DGameState/PlayingState.h"
#include "DCore/ResourceManager.h"
#include "DCore/SoundManager.h"
#include "DCore/GameData.h"
#include "DHUD/HUDManager.h"

GetReadyState::GetReadyState(GameStateManager* manager, int world, int level, GetReadyReason reason)
    :gsm(manager), targetWorld(world), targetLevel(level), reason(reason) {}

void GetReadyState::enter()
{
    SoundManager::getInstance().stopMusic();
    if(reason == GetReadyReason::NEW_GAME)
        SoundManager::getInstance().playSound(SoundEffect::LEVEL_START);
    else if(reason == GetReadyReason::RESPAWN)
        SoundManager::getInstance().playSound(SoundEffect::PLAYER_DOWN);

    dataForNextLevel = GameData();

    if (reason == GetReadyReason::RESPAWN) 
    {
        if (gsm->getContext().checkpointIsSet) {
            dataForNextLevel = gsm->getContext().checkpointData;
        } else {
            dataForNextLevel.worldNum = this->targetWorld;
            dataForNextLevel.levelNum = this->targetLevel;
            dataForNextLevel.score = gsm->getContext().scoreBeforeRespawn;
            dataForNextLevel.coins = 0;
        }
    } 
    else // NEW_GAME
    {
        if (gsm->getContext().checkpointIsSet)
        { 
            dataForNextLevel = gsm->getContext().checkpointData;
        } else {
            dataForNextLevel.worldNum = this->targetWorld;
            dataForNextLevel.levelNum = this->targetLevel;
        }
    }
    dataForNextLevel.lives = gsm->getContext().lives;

    lifeIcon = LoadTexture("assets/marioHead.png");
    coinIcon = LoadTexture("assets/coinHUD.png");
    hudManager = std::make_unique<HUDManager>(lifeIcon, coinIcon);
    // hudManager->syncWithContext(gsm->getContext());
    hudManager->updateWorld(dataForNextLevel.worldNum, dataForNextLevel.levelNum);
    hudManager->lifePoint.updateLifePoint(dataForNextLevel.lives);
    hudManager->coinDisplay.updateCoins(dataForNextLevel.coins);
    hudManager->scoreDisplay.updateScore(dataForNextLevel.score);
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

        if (reason == GetReadyReason::RESPAWN) 
        {
            if (gsm->getContext().checkpointIsSet)
            {
                dataToLoad = gsm->getContext().checkpointData;
            }
            else
            {
                std::cout << "Respawning in current level (no checkpoint). Resetting score and coins." << std::endl;
                dataToLoad.worldNum = this->targetWorld;
                dataToLoad.levelNum = this->targetLevel;
                
                dataToLoad.score = 0; 
                dataToLoad.coins = 0; 
            }
        } 
        else 
        {
            if (gsm->getContext().checkpointIsSet)
            {
                dataToLoad = gsm->getContext().checkpointData;
            } else {
                dataToLoad.worldNum = this->targetWorld;
                dataToLoad.levelNum = this->targetLevel;
            }
        }

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

    DrawTextureEx(lifeIcon, {GetScreenWidth()/2.0f - 70, GetScreenHeight()/2.0f - 12}, 0.0, 2.0, WHITE);
    std::string livesText = "x " + std::to_string(gsm->getContext().lives);
    DrawTextEx(font, livesText.c_str(), {GetScreenWidth()/2.0f, GetScreenHeight()/2.0f - 10}, fontSize, spacing, WHITE);
    //DrawText(livesText.c_str(), GetScreenWidth()/2.0f + 10, GetScreenHeight()/2.0f - 10, 30, WHITE);
}
