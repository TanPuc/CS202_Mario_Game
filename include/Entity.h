#ifndef ENTITUY_H
#define ENTITUY_H

#include <raylib.h>
#include "Level.h"

class Entity
{
public:
    Texture2D texture;
    Rectangle rect;
    Vector2 position;
    Vector2 velocity;

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
    virtual void Draw() const
    {
        DrawTexturePro(texture, {0, 0, (float)texture.width, (float)texture.height}, rect, {0, 0}, 0.0f, WHITE);
    }

    virtual void OnCollision(Entity &other) = 0;

    Rectangle GetBounds() const {
        return rect;
    }
};

#endif // ENTITY_H