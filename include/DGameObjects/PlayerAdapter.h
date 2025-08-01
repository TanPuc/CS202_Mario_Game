#pragma once
#include "DCore/ObserverSubject.h"
#include "Mario.h"

class PlayerAdapter : public Subject
{
    private: 
        Mario* mario_target;

        int last_lives;
        long long last_score;
        int last_coins;
    public:
        PlayerAdapter(Mario* target);

        void update();
        int getLives() const;
        int getCoins() const;
        long long getScore() const;
};