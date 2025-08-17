#ifndef FIREBALLSPRITE_H
#define FIREBALLSPRITE_H

#include "Sprite.h"

class FireBallSprite : public Sprite
{
private:
    Animation fireballAnimation;

public:
    Texture2D spriteSheet;
    Animation *currentAnimation;
    STATE prevState;
    int frameSpeed = 6; // 6fps

    FireBallSprite()
        : fireballAnimation({{247, 302, 8, 16},
                             {247 + 8 + FRAME_PADDING, 302, 8, 16},
                             {247 + (8 + FRAME_PADDING) * 2, 302, 8, 16},
                             {247 + (8 + FRAME_PADDING) * 3, 302, 8, 16}}),
          prevState(STATE_IDLE)
    {
        spriteSheet = LoadTexture("assets/SMB3_Mario_Luigi_SpriteSheet.png");
        currentAnimation = &fireballAnimation;
    }

    ~FireBallSprite()
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

#endif // FIREBALLSPRITE_H