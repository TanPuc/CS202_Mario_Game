#include "FireBallManager.h"

FireBallManager::FireBallManager()
{
}

void FireBallManager::Update(Level &level)
{
    for (auto it = fireballs.begin(); it != fireballs.end();)
    {
        if ((*it)->isOverLifeTime())
        {
            std::cout << "Fireball expired!" << std::endl;
            it = fireballs.erase(it); // Remove expired fireball
            continue;
        }
        (*it)->Update(level);
        if ((*it)->GetPosition().y < 0 || (*it)->GetPosition().y > GetScreenHeight())
        {
            it = fireballs.erase(it); // Remove fireball if it goes out of bounds
        }
        else
        {
            ++it; // Move to the next fireball
        }
    }
}

void FireBallManager::Draw()
{
    for (const auto &fireball : fireballs)
    {
        fireball->Draw();
    }
}

void FireBallManager::ShootFireBall(Vector2 position, DIRECTION direction)
{
    if (fireballs.size() < FIREBALL_THRESHOLD)
    {
        auto newFireBall = std::make_shared<FireBall>(position, direction);
        newFireBall->velocity.x = (direction == RIGHT) ? FIREBALL_SPEED : -FIREBALL_SPEED;
        fireballs.push_back(std::move(newFireBall));
    }
}
