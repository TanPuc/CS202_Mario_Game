#pragma once
#include "DCore/GUIElement.h"

class TimeDisplay : public GUIElement
{
    private:
        int timeRemaining = 400;
        float timer = 0.0f;

    public:
        TimeDisplay();

        void update();
        void draw() override;
};