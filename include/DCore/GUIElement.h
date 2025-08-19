#pragma once
#include "raylib.h"
#include <string>

class GUIElement
{
    public:
        Vector2 position;
        Vector2 size;
        bool isVisible;
        bool isEnabled;
        std::string name;

    virtual ~GUIElement() = default;
    virtual void draw() = 0;
    virtual bool contains (Vector2 point) const
    {
        if (!isVisible || !isEnabled) return false;
        return (point.x >= position.x && point.x <= position.x + size.x &&
                point.y >= position.y && point.y <= position.y + size.y);
    }

    void hide() { isVisible = false; }
    void show() { isVisible = true; }
    void enable() { isEnabled = true; }
    void disable() { isEnabled = false; }
};