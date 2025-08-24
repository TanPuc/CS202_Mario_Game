#ifndef GAME_CAMERA_H
#define GAME_CAMERA_H

#include <raylib.h>
#include "GlobalVariables.h"

class GameCamera
{
public:
    Camera2D camera;
    Vector2 target;
    Rectangle bounds;

    // Accessor for the singleton instance
    static GameCamera &getInstance()
    {
        static GameCamera instance; // created once, guaranteed by C++11
        return instance;
    }

    void setTarget(Vector2 target)
    {
        this->target = target;
        camera.target = target;
    }

private:
    // Private constructor
    GameCamera()
    {
        target = {0.0f, 0.0f};
        bounds = {0, 0, (float)SCREEN_WIDTH * SCALE, (float)SCREEN_HEIGHT * SCALE};
        camera.offset = Vector2{float(GetScreenWidth() / 2), 0};
        camera.target = target;
        camera.zoom = 1.0f;
    }

    // You may still allow parameterized initialization once
    GameCamera(Vector2 target, Rectangle bounds)
        : target(target), bounds(bounds)
    {
        camera.offset = Vector2{float(GetScreenWidth() / 2), 0};
        camera.target = target;
        camera.zoom = 1.0f;
    }

    // Prevent copying
    GameCamera(const GameCamera &) = delete;
    GameCamera &operator=(const GameCamera &) = delete;
};

#endif // GAME_CAMERA_H
