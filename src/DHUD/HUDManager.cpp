#include "DHUD/HUDManager.h"
// #include "Player.h"

HUDManager::HUDManager(Texture2D heartTexture, Texture2D coinTexture)
    : lifePoint(heartTexture), scoreDisplay(), coinDisplay(coinTexture)
{
    // Initialize the position of the HUD elements
    lifePoint.position = {50, 20};
    scoreDisplay.position = {250, 20};
    coinDisplay.position = {450, 20};

    // Set visibility and enable state
    lifePoint.isVisible = true;
    lifePoint.isEnabled = true;
    scoreDisplay.isVisible = true;
    scoreDisplay.isEnabled = true;
    coinDisplay.isVisible = true;
    coinDisplay.isEnabled = true;
}

void HUDManager::update(Subject* subject)
{
    //Player* player = dynamic_cast<Player*>(subject);
    //if (player)
    // {
    //     // Update life points, score, and coins based on player state
    //     // lifePoint.updateLifePoint(player->getLifeChange());
    //     // scoreDisplay.updateScore(player->getScoreChange());
    //     // coinDisplay.updateCoins(player->getCoinChange());
    // }
}

void HUDManager::draw()
{
    if (lifePoint.isVisible) {
        lifePoint.draw();
    }
    if (scoreDisplay.isVisible) {
        scoreDisplay.draw();
    }
    if (coinDisplay.isVisible) {
        coinDisplay.draw();
    }
}