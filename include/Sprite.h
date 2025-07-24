#ifndef SPRITE_H
#define SPRITE_H

#include <raylib.h>

#include "raylib.h"
#include <unordered_map>
#include <vector>
#include <string>

enum class MarioState
{
    IDLE,
    WALKING,
    JUMPING,
    FALLING,
    DUCKING,
    SWIMMING
};

struct Animation
{
    std::vector<Rectangle> frames; // Rectangles for each frame in the spritesheet
    float frameTime;               // How long each frame lasts
    bool loop;                     // Should the animation loop
};

class Sprite
{
public:
    Sprite(const std::string &filePath, float scale = 1.0f)
        : currentFrame(0), timer(0.0f), currentState(MarioState::IDLE), scale(scale)
    {
        texture = LoadTexture(filePath.c_str());
    }

    ~Sprite()
    {
        UnloadTexture(texture);
    }

    void AddAnimation(MarioState state, const Animation &anim)
    {
        animations[state] = anim;
    }

    void SetState(MarioState state)
    {
        if (currentState != state)
        {
            currentState = state;
            currentFrame = 0;
            timer = 0.0f;
        }
    }

    void Update(float deltaTime)
    {
        Animation &anim = animations[currentState];
        timer += deltaTime;

        if (timer >= anim.frameTime)
        {
            timer = 0.0f;
            currentFrame++;
            if (currentFrame >= anim.frames.size())
            {
                if (anim.loop)
                    currentFrame = 0;
                else
                    currentFrame = anim.frames.size() - 1; // Hold on last frame
            }
        }
    }

    void Draw(Vector2 position, bool flip = false)
    {
        Animation &anim = animations[currentState];
        Rectangle src = anim.frames[currentFrame];
        Rectangle dest = {position.x, position.y, src.width * scale, src.height * scale};

        Vector2 origin = {0, 0};
        DrawTexturePro(texture, src, dest, origin, 0.0f,
                       flip ? WHITE : WHITE);
    }

private:
    Texture2D texture;
    std::unordered_map<MarioState, Animation> animations;
    MarioState currentState;

    int currentFrame;
    float timer;
    float scale;
};

#endif // SPRITE_H