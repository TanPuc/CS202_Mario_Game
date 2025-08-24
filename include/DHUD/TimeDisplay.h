#pragma once
#include "DCore/GUIElement.h"

class TimeDisplay : public GUIElement
{
    private:
        int timeRemaining = 400;
        float timer = 0.0f;

    public:
        TimeDisplay();

        void reset(int startTime = 400);
        void update();
        void draw() override;
        int getTimeRemaining() const
        {
            return timeRemaining;
        }
        void setTime(int newTime)
        {
            timeRemaining = newTime;
        }
};