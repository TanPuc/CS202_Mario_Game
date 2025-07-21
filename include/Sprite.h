#ifndef SPRITE_H
#define SPRITE_H

#include <raylib.h>

class Sprite
{
public:
    Texture2D marioTexture = LoadTexture("./assets/mario.png");
    Texture2D brickTexture = LoadTexture("./assets/brick.png");

    Sprite() {};
    ~Sprite()
    {
        UnloadTexture(marioTexture);
        UnloadTexture(brickTexture);
    }
};

#endif // SPRITE_H