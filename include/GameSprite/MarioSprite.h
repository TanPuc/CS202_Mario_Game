#ifndef MARIOSPRITE_H
#define MARIOSPRITE_H

#include "Sprite.h"

class MarioSprite : public Sprite
{
private:
    Animation idleAnimation;
    Animation walkAnimation;
    Animation jumpAnimation;
    Animation decelerationAnimation;
    Animation duckAnimation;
    Animation deadAnimation;
    Animation slidingAnimation;

public:
    Texture2D spriteSheet;
    Animation *currentAnimation;
    STATE prevState;
    Rectangle frameRec;
    int animationTimer = 0;
    int frameCounter = 0;
    int frameSpeed = 12; // 12fps

    MarioSprite()
        : idleAnimation({{0, 16, 16, 16}}),
          walkAnimation({{16 + FRAME_PADDING, 16, 16, 16}, {0, 16, 16, 16}}),
          jumpAnimation({{32 + FRAME_PADDING * 2, 16, 16, 16}}),
          decelerationAnimation({{108, 16, 16, 16}}),
          duckAnimation({{0, 16, 16, 16}}),
          deadAnimation({{306, 16, 16, 16}}),
          slidingAnimation({{126, 16, 16, 16}}),
          prevState(STATE_IDLE)
    {
        spriteSheet = LoadTexture("assets/SMB3_Mario_Luigi_SpriteSheet.png");
        currentAnimation = &idleAnimation;
        frameRec = currentAnimation->frames[0];
    }

    ~MarioSprite()
    {
        UnloadTexture(spriteSheet);
    }

    void SwitchForm(MARIO_FORM newForm)
    {
        if (newForm == SMALL)
        {
            idleAnimation = {{0, 16, 16, 16}};
            walkAnimation = {{16 + FRAME_PADDING, 16, 16, 16}, {0, 16, 16, 16}};
            jumpAnimation = {{32 + FRAME_PADDING * 2, 16, 16, 16}};
            decelerationAnimation = {{108, 16, 16, 16}};
            duckAnimation = {{0, 16, 16, 16}};
            deadAnimation = {{306, 16, 16, 16}};
            slidingAnimation = {{126, 16, 16, 16}};
        }
        else if (newForm == BIG)
        {
            idleAnimation = {{0, 88, 16, 16 * 2}};
            walkAnimation = {{(16 + FRAME_PADDING) * 2, 88, 16, 16 * 2}, {16 + FRAME_PADDING, 88, 16, 16 * 2}, {0, 88, 16, 16 * 2}};
            jumpAnimation = {{(16 + FRAME_PADDING) * 4, 88, 16, 16 * 2}};
            decelerationAnimation = {{194, 88, 16, 16 * 2}};
            duckAnimation = {{54, 96, 16, 16 * 1.5f}};
            deadAnimation = {{306, 16, 16, 16}};
            slidingAnimation = {{212, 88, 16, 16 * 2}};
        }
        else if (newForm == FIRE)
        {
            idleAnimation = {{0, 260, 16, 16 * 2}};
            walkAnimation = {{(16 + FRAME_PADDING) * 2, 260, 16, 16 * 2}, {16 + FRAME_PADDING, 260, 16, 16 * 2}, {0, 260, 16, 16 * 2}};
            jumpAnimation = {{(16 + FRAME_PADDING) * 4, 260, 16, 16 * 2}};
            decelerationAnimation = {{194, 260, 16, 16 * 2}};
            duckAnimation = {{54, 268, 16, 16 * 1.5f}};
            deadAnimation = {{306, 16, 16, 16}};
            slidingAnimation = {{212, 260, 16, 16 * 2}};
        }
        else
        {
            std::cerr << "Unknown Mario form!" << std::endl;
        }
    }

    void SwitchAnimation(STATE state_) override
    {
        if (state_ == prevState)
            return;

        switch (state_)
        {
        case STATE_IDLE:
            // std::cout << "Switched to idle animation\n";
            currentAnimation = &idleAnimation;
            break;
        case STATE_WALKING:
            // std::cout << "Switched to walking animation\n";
            currentAnimation = &walkAnimation;
            break;
        case STATE_DECELERATING:
            currentAnimation = &decelerationAnimation;
            break;
        case STATE_JUMPING:
            // std::cout << "Switched to jumping animation\n";
            currentAnimation = &jumpAnimation;
            break;
        case STATE_DUCKING:
            // std::cout << "Switched to ducking animation\n";
            currentAnimation = &duckAnimation;
            break;
        case STATE_DEAD:
            // std::cout << "Switched to dead animation\n";
            currentAnimation = &deadAnimation;
            break;
        case STATE_SLIDING:
            // std::cout << "Switched to sliding animation\n";
            currentAnimation = &slidingAnimation;
            break;
        default:
            std::cerr << "Unknown state: " << state_ << std::endl;
            currentAnimation = &idleAnimation; // Fallback to idle
            break;
        }

        if (currentAnimation)
        {
            currentAnimation->frameCounter = 0;
        }
        prevState = state_;
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

            // Update Frame Rectangle
            frameCounter++;
            if (frameCounter >= currentAnimation->totalFrames)
            {
                frameCounter = 0; // Reset frame index
            }
            frameRec = currentAnimation->frames[frameCounter];
        }

        // Handle direction flipping
        if (entity.direction == LEFT)
        {
            frameRec.width = abs(frameRec.width);
        }
        else
        {
            frameRec.width = -abs(frameRec.width);
        }
        // DrawTextureRec(spriteSheet, frameRec, entity.position, WHITE);
        DrawTexturePro(spriteSheet, frameRec,
                       {entity.position.x, entity.position.y, entity.rect.width, entity.rect.height},
                       {0, 0}, 0.0f, WHITE);
    }
};

#endif // MARIOSPRITE_H