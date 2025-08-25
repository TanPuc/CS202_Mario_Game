#ifndef SPRITE_H
#define SPRITE_H

#include <raylib.h>
#include "GlobalVariables.h"
#include <vector>
#include "Entity.h"
#include <iostream>

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

    Animation &operator=(const std::vector<Rectangle> &other)
    {
        frames = other;
        totalFrames = static_cast<int>(frames.size());
        frameCounter = 0;
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

#endif // SPRITE_H