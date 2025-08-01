#pragma once

#include "DCore/GameState.h"
#include "DGameState/GameStateManager.h"
#include "Mario.h"
#include "Level.h"
#include "DHUD/HUDManager.h"
#include "DGameObjects/PlayerAdapter.h"
#include "DGameObjects/Coin.h"
#include <vector>
#include <memory>

class PlayingState : public GameState 
{
private:
    GameStateManager* gsm;
    std::unique_ptr<Mario> player;
    std::unique_ptr<Level> level;
    std::unique_ptr<PlayerAdapter> playerAdapter;
    std::unique_ptr<HUDManager> hudManager;
    std::vector<std::unique_ptr<Entity>> entities;

    Texture2D marioTexture, coinTexture, heartTexture, coinIcon;

public:
    PlayingState(GameStateManager* manager);
    void enter() override;
    void exit() override;
    void update() override;
    void draw() override;
};
