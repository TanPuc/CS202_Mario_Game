#ifndef ENTITY_H
#define ENTITY_H

#include <raylib.h>
#include "GlobalVariables.h"

// Forward declaration
class Level;

class Entity
{
public:
    Rectangle rect;
    Vector2 position;
    Vector2 velocity;
    DIRECTION direction = RIGHT; // Default direction

    Entity(Vector2 position, Vector2 size)
        : position(position), velocity({0.0f, 0.0f})
    {
        rect = {position.x, position.y, size.x, size.y};
    }

    virtual void Update(Level &level) = 0;
    virtual void Draw() = 0;

    virtual void ResolveCollision(Entity &other) = 0;
    virtual void ResolveCollision(Level &level) = 0;

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