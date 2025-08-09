#ifndef MARIO_H
#define MARIO_H

#include <raylib.h>
#include <iostream>
#include "Entity.h"

const int screenWidth = 256;
const int screenHeight = 240;
#define JUMP_FORCE 600.0f 

class Mario
{
public:
    Texture2D texture;
    Rectangle rect;
    Vector2 position;
    Vector2 velocity;
    bool moveLeft;
    bool moveRight;
    Camera2D camera;
    Vector2 centeredPos;

    Mario()
    {
        camera = { 0 };
        camera.offset = { 256.0f * 2.0f, 240.0f * 2.0f };
        texture = LoadTexture("./assets/mario.png");
        position = {500.0f, 700.0f}; // Initial position
        camera.target = { position.x + texture.width / 2.0f, position.y + texture.height / 2.0f };
        rect = {position.x, position.y, static_cast<float>(texture.width * 2), static_cast<float>(texture.height * 2)};
        std::cout << rect.width << " " << rect.height << std::endl;
        moveLeft = false;
        moveRight = false;
        velocity = {0.0f, 0.0f}; // Initial velocity
    }

    void HandleInput()
    {
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
        {
            moveLeft = true;

            if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
            {
                moveLeft = false;
                moveRight = true;
            }
        }
        else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
        {
            moveRight = true;

            if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
            {
                moveRight = false;
                moveLeft = true;
            }
        }
        else
        {
            moveLeft = false;
            moveRight = false;
        }
        if ( IsKeyPressed(KEY_SPACE) && velocity.y == 0 )
        {
            velocity.y = -JUMP_FORCE; // Apply jump force
        }
    }

    void Update()
    {
        // std::cout << "Updating Mario at position: (" << position.x << ", " << position.y << ")\n";
        camera.target = Vector2{ position.x + texture.width / 2.0f, position.y + texture.height / 2.0f };
        camera.zoom = 1.2f; 
        float gravity = 500.0f; // Gravity effect
        float speed = 1000.0f; // Speed of Mario
        float deltaTime = GetFrameTime();

        velocity.x += speed * deltaTime; 
        velocity.y += gravity * deltaTime; // Update velocity with gravity

        if(moveLeft)
        {
            position.x -= speed * deltaTime; // Move left
        }
        else if(moveRight)
        {
            position.x += speed * deltaTime; // Move right
        }
        position.y += velocity.y * deltaTime; // Apply gravity to Mario's position

        if (position.y > screenHeight * 4 - texture.height * 2 ) // Prevent going below the ground
        {
            position.y = screenHeight * 4 - texture.height * 2;
        }
        rect.x = position.x;
        rect.y = position.y;
        centeredPos = Vector2{ position.x + texture.width / 2.0f, position.y + texture.height / 2.0f };
    }

    void Draw()
    {
        // std::cout << "Drawing Mario at position: (" << position.x << ", " << position.y << ")\n";
        DrawTextureEx(texture, position, 0.0f, 2.0f, WHITE);
        DrawRectangleLinesEx(rect, 2.0f, RED);
    }
};

#endif