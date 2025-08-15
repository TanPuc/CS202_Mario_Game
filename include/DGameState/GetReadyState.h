#pragma once
#include "DCore/GameState.h"
#include "DGameState/GameStateManager.h"
#include "DHUD/HUDManager.h"

class GetReadyState: public GameState
{
    private:
        GameStateManager* gsm;
        float timer = 5.2f;
        int targetWorld;
        int targetLevel;
        std::unique_ptr<HUDManager> hudManager;
        Texture2D lifeIcon, coinIcon;
    public:
        GetReadyState(GameStateManager* manager, int world, int level);

        void enter() override;
        void exit() override;
        void update() override;
        void draw() override;
};