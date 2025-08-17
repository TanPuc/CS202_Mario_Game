#ifndef ITEM_H
#define ITEM_H

#include "Entity.h"
#include "Mario.h"

class Item : public Entity
{
public:
    bool isCollected;
    Item(Vector2 position, Vector2 size) : Entity(position, size), isCollected(false) {}
    virtual void Collect(Mario &mario) = 0;
};

#endif // ITEM_H