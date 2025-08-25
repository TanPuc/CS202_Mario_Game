#include "DGameObjects/PlayerAdapter.h"

PlayerAdapter::PlayerAdapter(Character *target) : character_target(target)
{
    if (character_target)
    {
        last_lives = character_target->lives;
        last_score = character_target->score;
        last_coins = character_target->coins;
    }
    else
    {
        last_lives = 0;
        last_score = 0;
        last_coins = 0;
    }
}

PlayerAdapter::~PlayerAdapter() {}

void PlayerAdapter::init()
{
    notifyObservers();
}

void PlayerAdapter::update()
{
    if (!character_target)
        return;

    bool hasChanged = (character_target->lives != last_lives ||
                       character_target->score != last_score ||
                       character_target->coins != last_coins);
    if (hasChanged)
    {
        last_lives = character_target->lives;
        last_score = character_target->score;
        last_coins = character_target->coins;
        notifyObservers();
    }
}

int PlayerAdapter::getLives() const
{
    return character_target ? character_target->lives : 0;
}

int PlayerAdapter::getCoins() const
{
    return character_target ? character_target->coins : 0;
}

long long PlayerAdapter::getScore() const
{
    return character_target ? character_target->score : 0;
}