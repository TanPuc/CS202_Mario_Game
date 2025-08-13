#ifndef ITEM_H
#define ITEM_H

#include <raylib.h>
#include "Entity.h"
#include "GlobalVariables.h"
#include "sprite/CoinSprite.h"

class Item : public Entity
{
public:
    Item(Vector2 pos, Vector2 size) : Entity(pos, size) {}
    virtual void OnCollect(Mario &mario) = 0;
};

#endif // ITEM_H