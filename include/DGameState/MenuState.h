#include "DGUI/GUIManager.h"
#include "DCore/GameState.h"
#include "DGameState/GameStateManager.h"

class MenuState : public GameState
{
    private:
        GameStateManager* gsm;
        GUIManager& guiManager;
        Texture2D background;
    public:
        MenuState(GameStateManager* gameStateManager);

        void enter() override;
        void exit() override;
        void update() override;
        void draw() override;
};