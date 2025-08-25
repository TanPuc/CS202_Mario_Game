#ifndef COIN_H
#define COIN_H

#include "Item.h"
#include "GameSprite/CoinSprite.h"
#include "DCore/SoundManager.h"

#define COIN_SIZE 16 * SCALE

class Coin : public Item
{
public:
    CoinSprite coinSprite;
    float timer = 0.0f; // Timer for coin animation
    const float lifeTime = 1.0f;
    Collision collision;

    Coin(Vector2 pos, Vector2 vel) : Item(pos, {COIN_SIZE, COIN_SIZE})
    {
        this->velocity = vel;
    }

    void Draw() override
    {
        coinSprite.Draw(*this);
    }

    void Collect(Character &character) override
    {
        if (isCollected)
            return;
        isCollected = true;
        character.coins++;
        character.score += 100; // Increment score by 100 for collecting a coin
        std::cout << "Coin collected! Total coins: " << character.coins << std::endl;
        SoundManager::getInstance().playSound(SoundEffect::COIN);
    }

    void Update(Level &level) override
    {
        if (!isActive)
            return;

        float dt = GetFrameTime();

        timer += dt;
        if (timer >= lifeTime)
        {
            timer = 0.0f;
            isActive = false;
            return;
        }

        position.y += velocity.y * dt;
        rect.y = position.y;
    }

    void ResolveCollision(Level &level) {};
};

#endif // COIN_H