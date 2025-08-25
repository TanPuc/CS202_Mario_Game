#include "DCore/GUIElement.h"

class CoinDisplay : public GUIElement
{
    private:
        int currentCoins;
        Texture2D coinTexture; // Texture for coin icon
    
    public:
        CoinDisplay(Texture2D coinTexture);

        void updateCoins(int newCount);
        void draw() override;
};