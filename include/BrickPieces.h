#ifndef BRICK_PIECES_H
#define BRICK_PIECES_H

#include <raylib.h>
#include "Entity.h"

// Forward declaration
class Level;

class BrickPiece : public Entity {
public:
    bool isOutOfScreen = false;
    int frameCounter = 0;
    const int frameSpeed = 12;
    const float gravity = 1000.0f;
    Rectangle source; 
    Vector2 velocity;
    Texture2D texture;

    BrickPiece ( char const *filePath, Vector2 position, Vector2 size, Rectangle source, Vector2 velocity )
        : Entity(position, size), source(source), velocity(velocity) {
        texture = LoadTexture(filePath);
    }

    void Update(Level& level) override {}

    void Update(){
        // Position 
        float deltaTime = GetFrameTime();
        velocity.y += gravity * deltaTime;
        position.x += velocity.x * deltaTime;
        position.y += velocity.y * deltaTime;

        // Animation 
        frameCounter++;
        if (frameCounter >= frameSpeed) {
            frameCounter = 0;
            source.x += 8;
            if (source.x > 24) source.x = 16;
        }

        // IsOutOfBound
        if ( position.y > SCREEN_HEIGHT * SCALE ) isOutOfScreen = true;
    }

    void Draw() override {
        rect.x = position.x; rect.y = position.y;
        DrawTexturePro(texture, source, rect, Vector2{0, 0}, 0.0f, WHITE);
    }

    void ResolveCollision(Entity &other) override {}
    void ResolveCollision(Level &level) override {}

};

#endif // BRICK_PIECES_H