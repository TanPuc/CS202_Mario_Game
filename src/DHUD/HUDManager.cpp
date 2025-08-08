#include "DHUD/HUDManager.h"
#include "DGameObjects/PlayerAdapter.h"

HUDManager::HUDManager(Texture2D heartTexture, Texture2D coinTexture)
    : lifePoint(heartTexture), scoreDisplay(), coinDisplay(coinTexture), worldDisplay(), timeDisplay()
{
    // Initialize the position of the HUD elements
    scoreDisplay.position = {80, 20};
    coinDisplay.position = {240, 45};
    worldDisplay.position = {400, 20};
    timeDisplay.position = {550, 20};
    lifePoint.position = {680, 20};

    // Set visibility and enable state
    lifePoint.isVisible = true;
    lifePoint.isEnabled = true;
    scoreDisplay.isVisible = true;
    scoreDisplay.isEnabled = true;
    coinDisplay.isVisible = true;
    coinDisplay.isEnabled = true;
    worldDisplay.isVisible = true;
    worldDisplay.isEnabled= true;
    timeDisplay.isVisible = true;
    timeDisplay.isEnabled = true;
}

void HUDManager::update(Subject* subject)
{
    if (PlayerAdapter* adapter = dynamic_cast<PlayerAdapter*>(subject))
    {
        scoreDisplay.updateScore(adapter->getScore());
        coinDisplay.updateCoins(adapter->getCoins());
        lifePoint.updateLifePoint(adapter->getLives());
    }

}

void HUDManager::updateTime()
{
    timeDisplay.update();
}

void HUDManager::updateWorld(int w, int l) 
{
    worldDisplay.updateWorld(w,l);
}

void HUDManager::draw()
{
    if (lifePoint.isVisible) 
    {
        lifePoint.draw();
    }
    if (scoreDisplay.isVisible) 
    {
        scoreDisplay.draw();
    }
    if (coinDisplay.isVisible) 
    {
        coinDisplay.draw();
    }
    if (worldDisplay.isVisible)
    {
        worldDisplay.draw();
    }
    if (timeDisplay.isVisible)
    {
        timeDisplay.draw();
    }
}