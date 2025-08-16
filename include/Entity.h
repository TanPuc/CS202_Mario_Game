#ifndef ENTITUY_H
#define ENTITUY_H

#include <raylib.h>
#include "Level.h"
#include "GlobalVariables.h"

class Entity
{
public:
    Rectangle rect;
    Vector2 position;
    Vector2 velocity;
    DIRECTION direction = RIGHT; // Default direction
    bool isActive;

    Entity(Vector2 position, Vector2 size)
        : position(position), velocity({0.0f, 0.0f}), isActive(true)
    {
        rect = {position.x, position.y, size.x, size.y};
    }
    virtual ~Entity() = default;

    virtual void Update(Level &level) = 0;
    virtual void Draw() = 0;

    Rectangle GetBounds() const
    {
        return rect;
    }

    Vector2 GetPosition() const
    {
        return position;
    }
};

#endif // ENTITY_H