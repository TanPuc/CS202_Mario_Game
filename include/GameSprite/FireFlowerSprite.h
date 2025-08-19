#ifndef FIREFLOWERSPRITE_H
#define FIREFLOWERSPRITE_H

#include "Sprite.h"

class FireFlowerSprite : public Sprite
{
private:
    Animation fireflowerAnimation;

public:
    Texture2D spriteSheet;
    Animation *currentAnimation;
    STATE prevState;
    int frameSpeed = 6; // 6fps

    FireFlowerSprite()
        : fireflowerAnimation({{68, 8, 16, 16}}),
          prevState(STATE_IDLE)
    {
        spriteSheet = LoadTexture("assets/SMB_Items_And_Objects.png");
        currentAnimation = &fireflowerAnimation;
    }

    ~FireFlowerSprite()
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
                           {entity.position.x, entity.position.y, frameRec.width * SCALE, frameRec.height * SCALE},
                           {0, 0}, 0.0f, WHITE);
        }
        else
        {
            currentAnimation->frameCounter = 0;
        }
    }
};

#endif // FIREBALLSPRITE_H