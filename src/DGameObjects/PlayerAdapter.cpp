#include "DGameObjects/PlayerAdapter.h"

PlayerAdapter::PlayerAdapter(Mario* target) : mario_target(target)
{
    if (mario_target) {
        last_lives = mario_target->lives;
        last_score = mario_target->score;
        last_coins = mario_target->coins;
    } else {
        last_lives = 0;
        last_score = 0;
        last_coins = 0;
    }
}

PlayerAdapter::~PlayerAdapter(){}

void PlayerAdapter::init()
{
    notifyObservers();
}

void PlayerAdapter::update()
{
    if (!mario_target) return;

    bool hasChanged =(mario_target->lives != last_lives ||
                      mario_target->score != last_score ||
                      mario_target->coins != last_coins);
    if (hasChanged) 
    {
        last_lives = mario_target->lives;
        last_score = mario_target->score;
        last_coins = mario_target->coins;
        notifyObservers();
    }
}

int PlayerAdapter::getLives() const
{
    return mario_target ? mario_target->lives : 0;
}

int PlayerAdapter::getCoins() const
{
    return mario_target ? mario_target->coins : 0;
}

long long PlayerAdapter::getScore() const
{
    return mario_target ? mario_target->score : 0;
}