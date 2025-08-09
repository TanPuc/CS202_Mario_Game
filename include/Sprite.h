#ifndef SPRITE_H
#define SPRITE_H

#include <raylib.h>
#include "GlobalVariables.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>

#define FRAME_PADDING 2 

struct Animation
{
    std::vector<Rectangle> frames;
    int totalFrames;
    int frameCounter;
    Animation() : totalFrames(0), frameCounter(0) {}

    Animation(std::vector<Rectangle> frames_)
        : frames(std::move(frames_)), frameCounter(0)
    {
        totalFrames = static_cast<int>(frames.size());
    }

    Animation(const Animation &other)
        : frames(other.frames), totalFrames(other.totalFrames), frameCounter(other.frameCounter) {}
    Animation &operator=(const Animation &other)
    {
        if (this != &other)
        {
            frames = other.frames;
            totalFrames = other.totalFrames;
            frameCounter = other.frameCounter;
        }
        return *this;
    }
};

class Sprite
{
public:
    virtual void SwitchAnimation(STATE state_) = 0;
    virtual void Draw(Entity &entity) = 0;
    virtual ~Sprite() = default;
};

class MarioSprite : public Sprite
{
private:
    Animation idleAnimation;
    Animation walkAnimation;
    Animation jumpAnimation;

public:
    Texture2D spriteSheet;
    Animation *currentAnimation;
    STATE prevState;
    int frameSpeed = 6; // 6fps

    MarioSprite()
        : idleAnimation({{0, 16, 16, 16}}),
          walkAnimation({{16 + FRAME_PADDING, 16, 16, 16}, {0, 16, 16, 16}}),
          jumpAnimation({{32 + FRAME_PADDING * 2, 16, 16, 16}}),
          prevState(STATE_IDLE)
    {
        spriteSheet = LoadTexture("assets/SMB3_Mario_Luigi_SpriteSheet.png");
        currentAnimation = &idleAnimation;
    }

    ~MarioSprite()
    {
        UnloadTexture(spriteSheet);
    }

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
        case STATE_JUMPING:
            currentAnimation = &jumpAnimation;
            break;
        case STATE_DUCKING:
            // Handle ducking state if needed
            currentAnimation = &idleAnimation; // Fallback to idle
            break;
        case STATE_SWIMMING:
            // Handle swimming state if needed
            currentAnimation = &idleAnimation; // Fallback to idle
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
            // DrawTextureRec(spriteSheet, frameRec, entity.position, WHITE);
            DrawTexturePro(spriteSheet, frameRec,
                           {entity.position.x, entity.position.y, frameRec.width * 2, frameRec.height * 2},
                           {0, 0}, 0.0f, WHITE);
        }
        else
        {
            currentAnimation->frameCounter = 0;
        }
        // DrawTexture(spriteSheet, entity.position.x, entity.position.y, WHITE);
    }
};

#endif // SPRITE_H