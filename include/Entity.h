#ifndef ENTITUY_H
#define ENTITUY_H

#include <raylib.h>

class Entity
{
public:
    Texture2D texture;
    Rectangle rect;
    Vector2 position;

    Entity(char const *filePath, Vector2 position, Vector2 size)
    {
        this->texture = LoadTexture(filePath);
        this->position = position;
        rect = {position.x, position.y, size.x, size.y};
    }

    virtual void Update() = 0;
    virtual void Draw() = 0;

    ~Entity()
    {
        UnloadTexture(texture);
    }
};

#endif // ENTITY_H