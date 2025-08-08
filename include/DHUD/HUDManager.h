#pragma once
#include "DCore/ObserverSubject.h"
#include "DHUD/LifePoint.h"
#include "DHUD/ScoreDisplay.h"
#include "DHUD/CoinDisplay.h"
#include "DHUD/WorldDisplay.h"
#include "DHUD/TimeDisplay.h"
#include "raylib.h"

class HUDManager : public Observer
{
    LifePoint lifePoint;
    ScoreDisplay scoreDisplay;
    CoinDisplay coinDisplay;
    WorldDisplay worldDisplay;
    TimeDisplay timeDisplay;

public:
    HUDManager(Texture2D heartTexture, Texture2D coinTexture);
    void update(Subject* subject) override;
    void updateTime();
    void updateWorld(int w, int l);
    void draw();
};