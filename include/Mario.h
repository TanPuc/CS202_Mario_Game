#ifndef MARIO_H
#define MARIO_H

#include <raylib.h>
#include "Entity.h"
#include <iostream>

class Mario
{
public:
    Texture2D texture;
    Rectangle rect;
    Vector2 position;
    Vector2 velocity;
    bool moveLeft;
    bool moveRight;

    Mario()
    {
        texture = LoadTexture("./assets/mario.png");
        position = {500.0f, 400.0f}; // Initial position
        rect = {position.x, position.y, static_cast<float>(texture.width), static_cast<float>(texture.height)};
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
    }

    void Update()
    {
        float gravity = 98.1f; // Gravity effect
        float speed = 200.0f; // Speed of Mario
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

        if (position.y > 720 - rect.height) // Prevent going below the ground
        {
            position.y = 720 - rect.height;
        }

        rect.x = position.x;
        rect.y = position.y;
    }

    void Draw()
    {
        std::cout << "Drawing Mario at position: (" << position.x << ", " << position.y << ")\n";
        DrawTextureEx(texture, position, 0.0f, 1.0f, WHITE);
    }
};

#endif