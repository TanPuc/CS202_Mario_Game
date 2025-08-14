#ifndef COINSPRITE_H
#define COINSPRITE_H

#include "Sprite.h"

class CoinSprite : public Sprite
{
private:
    Animation coinAnimation;

public:
    Texture2D spriteSheet;
    Animation *currentAnimation;
    STATE prevState;
    int frameSpeed = 6; // 6fps

    CoinSprite()
        : coinAnimation({{180, 36, 8, 16},
                             {180 + 8 + FRAME_PADDING, 36, 8, 16},
                             {180 + (8 + FRAME_PADDING) * 2, 36, 8, 16},
                             {180 + (8 + FRAME_PADDING) * 3, 36, 8, 16}}),
          prevState(STATE_IDLE)
    {
        spriteSheet = LoadTexture("assets/SMB_Items_And_Objects.png");
        currentAnimation = &coinAnimation;
    }

    ~CoinSprite()
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

        static int animationTimer = 0;
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

            // Handle direction flipping
            if (entity.direction == LEFT)
            {
                frameRec.width = abs(frameRec.width);
            }
            else
            {
                frameRec.width = -abs(frameRec.width);
            }
            DrawTexturePro(spriteSheet, frameRec,
                           {entity.position.x, entity.position.y, frameRec.width * 1.5f, frameRec.height * 1.5f},
                           {0, 0}, 0.0f, WHITE);
        }
        else
        {
            currentAnimation->frameCounter = 0;
        }
    }
};

#endif // COINSPRITE_H