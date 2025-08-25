#ifndef ENTITY_H
#define ENTITY_H

#include <raylib.h>
#include "GlobalVariables.h"
#include "Collision.h"

// Forward declaration
class Level;

class Entity
{
public:
    Rectangle rect = {};
    Vector2 position = {};
    Vector2 velocity = {};
    Collision collision = {};
    DIRECTION direction = RIGHT; // Default direction
    bool isActive;

    Entity() {}
    Entity(Vector2 position, Vector2 size)
        : position(position), velocity({0.0f, 0.0f}), isActive(true)
    {
        rect = {position.x, position.y, size.x, size.y};
    }
    Entity(Vector2 position, Vector2 size, Vector2 velocity, DIRECTION direction)
        : position(position), velocity(velocity), direction(direction), isActive(true)
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