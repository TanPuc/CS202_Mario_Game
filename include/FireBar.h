#include <cmath>
#include <memory>
#include <iostream>
#include "raylib.h"
#include "Entity.h"
#include "GlobalVariables.h"
#include "GameSprite/FireBallSprite.h"

// Forward declaration
class Level;
class Mario;

class FireBarElement : public Entity
{
public:
    Sprite* sprite;
    Vector2 centerOfRotation;
    Vector2 centerOfElement;
    const float angle = 10 * ( 2 * M_PI ) / 360;
    int timer = 0;

    FireBarElement(Vector2 centerOfElement, Vector2 centerOfRotation)
        : Entity(Vector2{0, 0}, Vector2{FIREBALL_SIZE, FIREBALL_SIZE}),
        centerOfRotation(centerOfRotation), centerOfElement(centerOfElement)
    {
        position.x = centerOfElement.x - FIREBALL_SIZE / 2;
        position.y = centerOfElement.y - FIREBALL_SIZE / 2;
        sprite = new FireBallSprite();
    }

    void Update(Level& level)
    {
        
    }

    void update(Mario& player);

    void Draw() 
    {
        sprite->Draw(*this);
        DrawRectangleLinesEx(rect, 1.0f, RED); // Draw hurt box
    }

    ~FireBarElement()
    {
        delete sprite;
    }
};

class FireBar
{
public:
    std::vector<std::shared_ptr<FireBarElement>> elements;
    FireBar(Vector2 center, float initialAngle)
    {
        // Initial angle with respect to the y axis and counterclockwise
        // 1 fireball at the center
        auto centerFireball = std::make_shared<FireBarElement>(center, center);
        elements.push_back(std::move(centerFireball));

        // 5 more fireballs
        float distance = FIREBALL_SIZE;
        for ( int i = 1; i <= 5; ++i)
        {
            Vector2 pos = { center.x - i * distance * std::sin(initialAngle),
                            center.y + i * distance * std::cos(initialAngle) };
            auto fireball = std::make_shared<FireBarElement>(pos, center);
            elements.push_back(std::move(fireball));
        }
    }

    void Update(Mario& player)
    {
        for (auto& element : elements)
        {
            if ( element )
            {
                element->update(player);
            }
        }
    }

    void Draw()
    {
        for (auto& element : elements)
        {
            if ( element )
            {
                element->Draw();
            }
        }
    }
};
