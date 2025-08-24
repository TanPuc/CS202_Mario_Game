#include "FireBar.h"
#include "Mario.h"

void FireBarElement::update(Mario& player)
{
    // Rotate 10 degree every 8 frames 
    timer++;
    if (timer > 8)
    {
        timer = 0;
    
        float dx = centerOfElement.x - centerOfRotation.x;
        float dy = centerOfElement.y - centerOfRotation.y;

        float rotatedX = dx * std::cos(angle) + dy * std::sin(angle);
        float rotatedY = - dx * std::sin(angle) + dy * std::cos(angle);

        centerOfElement.x = centerOfRotation.x + rotatedX;
        centerOfElement.y = centerOfRotation.y + rotatedY;

        position.x = centerOfElement.x - FIREBALL_SIZE / 2;
        position.y = centerOfElement.y - FIREBALL_SIZE / 2;

        rect.x = position.x;
        rect.y = position.y;

        std::cout << centerOfElement.x << " " << centerOfElement.y << std::endl;
    }

    if ( CheckCollisionRecs(player.GetBounds(), rect) )
    {
        player.Die();
    }

}