#ifndef FORTRESS_FLAG_H
#define FORTRESS_FLAG_H

#include <raylib.h>
#include "Entity.h"

class FortressFlag : public Entity
{
private:
    float velY = -200.0f;
    Vector2 destPos;
    Texture2D texture;

public:
    FortressFlag(Vector2 position) : Entity(position, {32, 32}), destPos({position.x, position.y - 76.0f})
    {
        texture = LoadTexture("./assets/Tiles/Overworld/fortressflag.png");
    }
    ~FortressFlag()
    {
        UnloadTexture(texture);
    }

    void Update()
    {
        // If GAMESTATE == WON
        float ft = GetFrameTime();
        position.y += velY * ft;
        if (position.y <= destPos.y)
        {
            position.y = destPos.y;
            velY = 0;
            // Change GAMESTATE
        }
    }
    void Draw() override
    {
        DrawTextureEx(texture, position, 0.0f, SCALE, WHITE);
    }

    void Update(Level &level) override {}
};

#endif // FORTRESS_FLAG_H