#ifndef THROWINGSPRITE_H
#define THROWINGSPRITE_H

#include "Sprite.h"

class ThrowingSprite : public Sprite
{
private:
    Animation throwingAnimation;

public:
    Texture2D spriteSheet;
    Animation *currentAnimation;
    Rectangle frameRec;
    int frameSpeed = 12; // 12fps
    int animationTimer = 0;

    ThrowingSprite()
        : throwingAnimation({{208 + 16 + FRAME_PADDING, 294, 16, 16 * 2}})
    {
        spriteSheet = LoadTexture("assets/SMB3_Mario_Luigi_SpriteSheet.png");
        currentAnimation = &throwingAnimation;
    }

    ~ThrowingSprite()
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
                           {entity.position.x, entity.position.y, frameRec.width * SCALE, frameRec.height * SCALE},
                           {0, 0}, 0.0f, WHITE);
        }
        else
        {
            currentAnimation->frameCounter = 0;
        }
    }
};

#endif // MARIOSPRITE_H