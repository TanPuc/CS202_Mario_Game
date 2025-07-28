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
    Texture2D marioIdleSprite = LoadTexture("assets/Mario/mario_idle_sprite.png");
    Texture2D marioWalkSprite = LoadTexture("assets/Mario/mario_walk_sprite.png");
    Texture2D marioJumpSprite = LoadTexture("assets/Mario/mario_jump_sprite.png");
    Rectangle frameRec;
    std::vector<Rectangle> idleAnimation = {{0, 0, 32, 32}};
    std::vector<Rectangle> walkAnimation = {{0, 0, 32, 32}, {32, 0, 32, 32}, {64, 0, 32, 32}};
    std::vector<Rectangle> jumpAnimation = {{0, 0, 32, 32}};

    int frameCounter;
    int frameSpeed = 8;

    ~Sprite()
    {
        UnloadTexture(marioIdleSprite);
        UnloadTexture(marioWalkSprite);
        UnloadTexture(marioJumpSprite);
    }

    void Update(float deltaTime)
    {
    }

    void Draw(Entity &entity, STATE state)
    {

        switch (state)
        {
        case STATE_IDLE:
            // DrawTextureRec(marioIdleSprite, idleAnimation[0], entity.position, WHITE);
            DrawTexture(marioIdleSprite, entity.position.x, entity.position.y, WHITE);
            std::cout << "Drawing Idle Animation" << std::endl;
            break;
        case STATE_WALKING:
            // DrawTextureRec(marioWalkSprite, walkAnimation[0], entity.position, WHITE);
            DrawTexture(marioWalkSprite, entity.position.x, entity.position.y, WHITE);
            std::cout << "Drawing Walking Animation" << std::endl;
            break;
        case STATE_JUMPING:
            // DrawTextureRec(marioJumpSprite, jumpAnimation[0], entity.position, WHITE);
            DrawTexture(marioJumpSprite, entity.position.x, entity.position.y, WHITE);
            std::cout << "Drawing Jumping Animation" << std::endl;
            break;
        case STATE_FALLING:
            // DrawTextureRec(characterSprite, fallingAnimation[0], entity.position, WHITE);
            std::cout << "Drawing Falling Animation" << std::endl;
            break;
        case STATE_DUCKING:
            // DrawTextureRec(characterSprite, duckingAnimation[0], entity.position, WHITE);
            std::cout << "Drawing Ducking Animation" << std::endl;
            break;
        case STATE_SWIMMING:
            // DrawTextureRec(characterSprite, swimmingAnimation[0], entity.position, WHITE);
            std::cout << "Drawing Swimming Animation" << std::endl;
            break;
        default:
            DrawTextureRec(marioIdleSprite, idleAnimation[0], entity.position, WHITE);
        }
    }
};

#endif // SPRITE_H