#ifndef COINBLOCKSPRITE_H
#define COINBLOCKSPRITE_H

#include "Sprite.h"

class CoinBlockSprite : public Sprite
{
private:
    Animation coinBlockAnimation;

public:
    Texture2D spriteSheet;
    Animation *currentAnimation;
    STATE prevState;
    int frameSpeed = 12; // 12fps
    int animationTimer = 0;

    CoinBlockSprite()
        : coinBlockAnimation({{298, 95, 16, 16},
                              {298 + 16 + 1, 95, 16, 16},
                              {298 + (16 + 1) * 2, 95, 16, 16}}),
          prevState(STATE_IDLE)
    {
        spriteSheet = LoadTexture("assets/SMB_Tile_Set.png");
        currentAnimation = &coinBlockAnimation;
    }

    ~CoinBlockSprite()
    {
        UnloadTexture(spriteSheet);
    }

    void SwitchAnimation(STATE state_) override {}

    void Draw(Entity &entity) override
    {
        if (!currentAnimation)
        {
            std::cerr << "Current animation is not set!" << std::endl;
            return;
        }

        
        animationTimer++;

        if (animationTimer >= frameSpeed)
        {
            animationTimer = 0;
            currentAnimation->frameCounter++;
            if (currentAnimation->frameCounter >= currentAnimation->totalFrames)
            {
                currentAnimation->frameCounter = 0; // Reset frame index
            }
        }

        // Get current frame
        if (currentAnimation->frameCounter < currentAnimation->frames.size())
        {
            Rectangle frameRec = currentAnimation->frames[currentAnimation->frameCounter];

            DrawTexturePro(spriteSheet, frameRec,
                           {entity.position.x, entity.position.y, -frameRec.width * SCALE, frameRec.height * SCALE},
                           {0, 0}, 0.0f, WHITE);
        }
        else
        {
            currentAnimation->frameCounter = 0;
        }
    }
};

#endif // COINSPRITE_H