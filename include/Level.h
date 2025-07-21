#ifndef LEVEL_H
#define LEVEL_H

#include <raylib.h>
#include "Sprite.h"
#include <vector>

class Level : public Sprite
{
public:
    std::vector<Rectangle> ground;
    Level() {
        for (int i = 0; i < 1280 / 16; i++)
        {
            ground.push_back((Rectangle){static_cast<float>(i * 16), 720 - 16, 16, 16}); // Assuming each ground block is 64x64 pixels
        }
    };

    void Draw()
    {
        for (const auto &rect : ground)
        {
            DrawTexture(brickTexture,
                        rect.x, rect.y,
                        WHITE);
        }
    }
};

#endif // LEVEL_H