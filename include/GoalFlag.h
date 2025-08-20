#ifndef GOALFLAG_H
#define GOALFLAG_H

#include <iostream>
#include "Entity.h"
#include "GlobalVariables.h"

// Forward declaration
class Level;

class GoalFlag : public Entity
{
private:
    float velY = 0.0f;
    Vector2 destPos;
    Texture2D texture;

public:
    GoalFlag(Vector2 position) : Entity(position, {32, 32}), destPos(Vector2{position.x, position.y + 492.0f})
    {
        texture = LoadTexture("./assets/Tiles/Overworld/goalflag.png");
    }
    ~GoalFlag()
    {
        UnloadTexture(texture);
    }
    void iniVelY()
    {
        velY = 200.0f;
    }

    void Draw() override
    {
        DrawTextureEx(texture, position, 0.0f, SCALE, WHITE);
    }
    void Update(TileState &state)
    {
        if (state == STATE_ACTIVATED)
        {
            float ft = GetFrameTime();
            position.y += velY * ft;
            // Mario slides simultaneously with the flag
            if (position.y >= destPos.y)
            {
                position.y = destPos.y;
                velY = 0.0f;
                // Mario stops sliding, goes toward the fortress
                // The fortress's flag raises
            }
        }
    }

    void Update(Level &level) override {}
};

#endif // GOALFLAG_H