#pragma once
#include "DCore/ObserverSubject.h"
#include "Character.h"

class PlayerAdapter : public Subject
{
private:
    Character *character_target;

    int last_lives;
    long long last_score;
    int last_coins;

public:
    PlayerAdapter(Character *target);
    ~PlayerAdapter();

    void init();
    void update();
    int getLives() const;
    int getCoins() const;
    long long getScore() const;
};