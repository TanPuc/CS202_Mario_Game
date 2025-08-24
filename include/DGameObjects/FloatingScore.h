#pragma once
#include "raylib.h"
#include "DCore/ResourceManager.h" 

class FloatingScore
{
public:
    Vector2 position;
    std::string text;
    float lifeTime; 
    float timer;    
    Color color;

    FloatingScore(Vector2 pos, std::string txt)
    {
        //move position a bit up
        position = {pos.x, pos.y - 10.0f}; 
        text = txt;
        lifeTime = 0.7f; // Total lifetime of the effect
        timer = lifeTime;
        color = WHITE;
    }

    // Update position and opacity each frame
    void update()
    {
        float deltaTime = GetFrameTime();
        timer -= deltaTime;
        position.y -= 30.0f * deltaTime; // Speed of upward movement

        // Calculate opacity (alpha) based on remaining time
        color.a = (unsigned char)(255.0f * (timer / lifeTime));
    }

    void draw()
    {
        Font font = ResourceManager::GetInstance().GetGameFont();
        DrawTextEx(font, text.c_str(), position, 10, 1.0f, color);
    }

    bool isDead() const
    {
        return timer <= 0.0f;
    }
};