#ifndef FIREBALLSPRITE_H
#define FIREBALLSPRITE_H

#include "Sprite.h"

class FireBallSprite : public Sprite
{
private:
    Animation fireballAnimation;
    Animation explosionAnimation;

public:
    Texture2D spriteSheet;
    Animation *currentAnimation;
    STATE prevState;
    int frameSpeed = 6; // 6fps
    int animationTimer = 0;
    
    FireBallSprite()
        : fireballAnimation({{180, 54, 8, 8},
                             {180 + 8 + FRAME_PADDING, 54, 8, 8},
                             {180 + (8 + FRAME_PADDING) * 2, 54, 8, 8},
                             {180 + (8 + FRAME_PADDING) * 3, 54, 8, 8}}),
          explosionAnimation({{180, 64, 16, 16},
                              {180 + 16 + FRAME_PADDING, 64, 16, 16},
                              {180 + (16 + FRAME_PADDING) * 2, 64, 16, 16}}),
          prevState(STATE_IDLE)
    {
        spriteSheet = LoadTexture("assets/SMB_Items_And_Objects.png");
        currentAnimation = &fireballAnimation;
    }

    ~FireBallSprite()
    {
        UnloadTexture(spriteSheet);
    }

    void SwitchAnimation(STATE state_) override
    {
        switch (state_)
        {
        case STATE_IDLE:
            currentAnimation = &fireballAnimation;
            break;
        case STATE_DEAD:
            currentAnimation = &explosionAnimation;
            break;
        default:
            break;
        }
    }

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

#endif // FIREBALLSPRITE_H