#ifndef SPRITE_H
#define SPRITE_H

#include <raylib.h>
#include "GlobalVariables.h"
#include <unordered_map>
#include <vector>
#include <string>

class Sprite
{
public:
    virtual void SwitchAnimation(STATE state_) = 0;
    virtual void Draw(Entity &entity) = 0;
    virtual ~Sprite() = default;
};

class MarioSprite : public Sprite
{
public:
    Texture2D marioIdleTexture;
    Texture2D marioWalkTexture;
    Texture2D marioJumpTexture;
    std::unique_ptr<Texture2D> currentTexture;
    STATE prevState; // Previous state for animation switching
    Rectangle frameRec = {0, 0, 32, 32};
    int frameCounter = 0;
    int frameSpeed = 6; // 6fps

    MarioSprite()
    {
        // Initialize the current animation to idle state
        marioIdleTexture = LoadTexture("assets/Mario/mario_idle_sprite.png");
        marioWalkTexture = LoadTexture("assets/Mario/mario_walk_sprite.png");
        marioJumpTexture = LoadTexture("assets/Mario/mario_jump_sprite.png");
        currentTexture = std::make_unique<Texture2D>(marioIdleTexture);
    }

    void SwitchAnimation(STATE state_)
    {
        if (state_ == prevState)
            return; // No change in state, skip switching
        switch (state_)
        {
        case STATE_IDLE:
            currentTexture = std::make_unique<Texture2D>(marioIdleTexture);
            break;
        case STATE_WALKING:
            currentTexture = std::make_unique<Texture2D>(marioWalkTexture);
            break;
        case STATE_JUMPING:
            currentTexture = std::make_unique<Texture2D>(marioJumpTexture);
            break;
        case STATE_FALLING:
            break;
        case STATE_DUCKING:
            break;
        case STATE_SWIMMING:
            break;
        default:
            std::cerr << "Unknown state: " << state_ << std::endl;
            break;
        }
        frameCounter = 0;
        prevState = state_; // Update previous state
    }

    void Draw(Entity &entity)
    {
        if (!currentTexture)
        {
            std::cerr << "Current texture is not set!" << std::endl;
            return;
        }
        // Update frame counter
        frameCounter++;
        if (frameCounter >= frameSpeed)
        {
            frameCounter = 0;
            // Update frame rectangle for animation
            frameRec.x += frameRec.width;
            if (frameRec.x >= currentTexture->width)
            {
                frameRec.x = 0; // Reset to the first frame
            }
        }
        if (entity.direction == LEFT)
        {
            frameRec.width = -abs(frameRec.width); // Flip the frame for left direction
        }
        else
        {
            frameRec.width = abs(frameRec.width); // Ensure positive width for right direction
        }
        DrawTextureRec(*currentTexture, frameRec, entity.position, WHITE);
    }
};

#endif // SPRITE_H