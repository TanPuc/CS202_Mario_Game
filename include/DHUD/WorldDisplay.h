#pragma once
#include "DCore/GUIElement.h"

class WorldDisplay : public GUIElement
{
    private:
        int world = 1;
        int level = 1;
    public:
        WorldDisplay();

        void updateWorld(int world, int level);
        void draw() override;
};