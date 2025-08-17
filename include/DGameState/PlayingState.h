#pragma once

#include "DCore/GameState.h"
#include "DGameState/GameStateManager.h"
#include "Mario.h"
#include "Level.h"
#include "DHUD/HUDManager.h"
#include "DGameObjects/PlayerAdapter.h"
#include "DGameObjects/Coin.h"
#include "DGameObjects/Mushroom.h"
#include "DGameObjects/FireFlower.h"
#include "ItemManager.h"
#include <vector>
#include <memory>

class PlayingState : public GameState
{
private:
    GameStateManager *gsm;
    ItemManager itemManager;
    std::unique_ptr<Mario> player;
    std::unique_ptr<Level> level;
    std::unique_ptr<PlayerAdapter> playerAdapter;
    std::unique_ptr<HUDManager> hudManager;
    // std::vector<std::unique_ptr<Entity>> entities; // This counts for items and enemies

    int worldNum;
    int levelNum;
    Texture2D marioTexture, heartTexture, coinIcon;

    Vector2 cameraPos;

public:
    PlayingState(GameStateManager *manager, int world, int level);
    void enter() override;
    void exit() override;
    void update() override;
    void draw() override;
};
