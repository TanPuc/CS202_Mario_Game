#include "DCore/GUIElement.h"

class LifePoint: public GUIElement
{
    private:
        int currentLifePoint;
        Texture2D heartTexture; // Texture for heart icon
        static const int maxLifePoint = 10;
    public: 
        LifePoint(Texture2D heartTexture);

        void updateLifePoint(int change);
        void draw() override;
};