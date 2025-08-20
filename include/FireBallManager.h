#ifndef FIREBALLMANAGER_H
#define FIREBALLMANAGER_H

#include <raylib.h>
#include <vector>
#include "DGameObjects/FireBall.h"
#include "Level.h"

class FireBallManager
{
private:
    std::vector<std::shared_ptr<FireBall>> fireballs;

public:
    FireBallManager();

    void Update(Level &level);
    void Draw();
    void ShootFireBall(Vector2 position, DIRECTION direction);
};

#endif // FIREBALLMANAGER_H