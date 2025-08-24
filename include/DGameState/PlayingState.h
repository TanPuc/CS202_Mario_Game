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
#include "FireBallManager.h"
#include "DGUI/ImageButton.h"
#include "DCore/GameData.h"
#include "Tile.h"

#include "raylib.h"
#include <vector>
#include <memory>
#include <DGameObjects/FloatingScore.h>


enum class PlaySubState
{
    PLAYING,
    LEVEL_CLEAR_ANIMATION,
    SCORE_TALLY
};
class Mario;
class Level;
class PlayerAdapter;
class HUDManager;
class ImageButton;
class ItemManager;

class PlayingState : public GameState
{
private:
    GameStateManager *gsm;
    std::unique_ptr<ItemManager> itemManager;
    FireBallManager fireBallManager;
    std::unique_ptr<Mario> player;
    std::unique_ptr<Level> level;
    std::unique_ptr<PlayerAdapter> playerAdapter;
    std::unique_ptr<HUDManager> hudManager;
    std::weak_ptr<GoalpoleInstance> goalpole;
    std::vector<FloatingScore> floatingScores;
    // std::vector<std::unique_ptr<Entity>> entities; // This counts for items and enemies

    int worldNum;
    int levelNum;
    Texture2D marioTexture, heartTexture, coinIcon;

    Vector2 cameraPos;

    // PAUSE BUTTON
    std::unique_ptr<ImageButton> pauseButton;
    Texture2D pauseIconTexture;

    GameData currentData;

    PlaySubState subState = PlaySubState::PLAYING;
    float scoreTallyTimer = 0.0f;
    int timeToConvert = 0;

public:
    PlayingState(GameStateManager *manager, const GameData &initialData);
    void enter() override;
    void exit() override;
    void update() override;
    void draw() override;
    void saveGameData();
    void setGoalpole(std::shared_ptr<GoalpoleInstance> gp);
    void addFloatingScore(Vector2 position, const std::string &text);
    void updatePlaying();
    void updateLevelClearAnimation();
    void updateScoreTally();
};
