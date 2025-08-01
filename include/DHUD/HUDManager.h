#pragma once
#include "DCore/ObserverSubject.h"
#include "DHUD/LifePoint.h"
#include "DHUD/ScoreDisplay.h"
#include "DHUD/CoinDisplay.h"
#include "raylib.h"

class HUDManager : public Observer
{
    LifePoint lifePoint;
    ScoreDisplay scoreDisplay;
    CoinDisplay coinDisplay;

public:
    HUDManager(Texture2D heartTexture, Texture2D coinTexture);
    void update(Subject* subject) override;
    void draw();
};