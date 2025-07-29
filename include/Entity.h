#ifndef ENTITUY_H
#define ENTITUY_H

#include <raylib.h>
#include "Level.h"
#include "GlobalVariables.h"

class Entity
{
public:
    Texture2D texture;
    Rectangle rect;
    Vector2 position;
    Vector2 velocity;
    DIRECTION direction = RIGHT; // Default direction

    Entity(Texture texture, Vector2 position)
        : texture(texture), position(position), velocity({0.0f, 0.0f})
    {
        rect = {position.x, position.y, (float)texture.width, (float)texture.height};
    }
    virtual ~Entity()
    {
        UnloadTexture(texture);
    }

    virtual void Update() = 0;
    virtual void Draw()
    {
        DrawTextureEx(texture, position, 0.0f, 2.0f, WHITE);
    }

    virtual void ResolveCollision(Entity &other) = 0;
    virtual void ResolveCollision(Level &level) = 0;

    Rectangle GetBounds() const {
        return rect;
    }
};

#endif // ENTITY_H