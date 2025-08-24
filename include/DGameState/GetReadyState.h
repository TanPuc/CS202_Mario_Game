#pragma once
#include "DCore/GameState.h"
#include "DGameState/GameStateManager.h"
#include "DHUD/HUDManager.h"


enum class GetReadyReason
{
    NEW_GAME,
    RESPAWN
};
class GetReadyState: public GameState
{
    private:
        GameStateManager* gsm;
        float timer = 5.2f;
        int targetWorld;
        int targetLevel;
        GetReadyReason reason;
        std::unique_ptr<HUDManager> hudManager;
        Texture2D lifeIcon, coinIcon;
        GameData dataForNextLevel;
    public:
        GetReadyState(GameStateManager* manager, int world, int level, GetReadyReason reason);

        void enter() override;
        void exit() override;
        void update() override;
        void draw() override;
};