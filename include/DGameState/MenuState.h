#include "DGUI/GUIManager.h"
#include "DCore/GameState.h"
#include "DGameState/GameStateManager.h"
#include "raylib.h"

class MenuState : public GameState
{
    private:
        GameStateManager* gsm;
        GUIManager& guiManager;
        Texture2D boardTexture;
        Texture2D marioTitle;
        Texture2D heartTexture;
        Texture2D buttonTexture;
        
        void buildGUI();
    public:
        MenuState(GameStateManager* gameStateManager);

        void enter() override;
        void exit() override;
        void update() override;
        void draw() override;
        void resume() override;
        void playMenuMusic();
};