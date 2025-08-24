#ifndef CHARACTERSPRITE_H
#define CHARACTERSPRITE_H

#include "Sprite.h"
#include <iostream>

class CharacterSprite : public Sprite
{
protected:
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

    CharacterSprite(const std::string &spriteSheetPath, const std::vector<Rectangle> &idleFrames,
                    const std::vector<Rectangle> &walkFrames, const std::vector<Rectangle> &jumpFrames,
                    const std::vector<Rectangle> &decelerationFrames, const std::vector<Rectangle> &duckFrames,
                    const std::vector<Rectangle> &deadFrames, const std::vector<Rectangle> &slidingFrames)
        : idleAnimation(idleFrames),
          walkAnimation(walkFrames),
          jumpAnimation(jumpFrames),
          decelerationAnimation(decelerationFrames),
          duckAnimation(duckFrames),
          deadAnimation(deadFrames),
          slidingAnimation(slidingFrames),
          prevState(STATE_IDLE)
    {
        spriteSheet = LoadTexture(spriteSheetPath.c_str());
        currentAnimation = &idleAnimation;
        frameRec = currentAnimation->frames[0];
    }

    virtual ~CharacterSprite()
    {
        UnloadTexture(spriteSheet);
    }

    virtual void SwitchForm(CHARACTER_FORM newForm) = 0;

    void SwitchAnimation(STATE state_) override
    {
        if (state_ == prevState)
            return;

        switch (state_)
        {
        case STATE_IDLE:
            currentAnimation = &idleAnimation;
            break;
        case STATE_WALKING:
            currentAnimation = &walkAnimation;
            break;
        case STATE_DECELERATING:
            currentAnimation = &decelerationAnimation;
            break;
        case STATE_JUMPING:
            currentAnimation = &jumpAnimation;
            break;
        case STATE_DUCKING:
            currentAnimation = &duckAnimation;
            break;
        case STATE_DEAD:
            currentAnimation = &deadAnimation;
            break;
        case STATE_SLIDING:
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
            frameRec = currentAnimation->frames[0];
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

        std::cout << "Sprite Rec y: " << frameRec.y << std::endl;
        DrawTexturePro(spriteSheet, frameRec,
                       {entity.position.x, entity.position.y, entity.rect.width, entity.rect.height},
                       {0, 0}, 0.0f, WHITE);
    }
};

#endif // CHARACTERSPRITE_H