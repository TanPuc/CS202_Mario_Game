#ifndef COINBLOCK_H
#define COINBLOCK_H

#include <raylib.h>
#include <iostream>
#include "Item.h"
#include "Collision.h"
#include "GlobalVariables.h"
#include "GameSprite/CoinBlockSprite.h"
#include "DCore/SoundManager.h"

#define COIN_SIZE 16 * SCALE

class CoinBlock : public Item
{
public:
    float timer = 0.0f; // Timer for coin animation
    const float lifeTime = 1.0f;
    Collision collision;
    std::shared_ptr<CoinBlockSprite> coinBlockSprite;

    CoinBlock(Vector2 pos) : Item(pos, {COIN_SIZE, COIN_SIZE}) {}
    CoinBlock(Vector2 pos, std::shared_ptr<CoinBlockSprite> sprite) : Item(pos, {COIN_SIZE, COIN_SIZE}), coinBlockSprite(std::move(sprite)) {}

    void Draw() override
    {
        coinBlockSprite->Draw(*this);
    }

    void Collect(Character &player) override
    {
        if (isCollected)
            return;
        isCollected = true;
        player.coins++;
        player.score += 100; // Increment score by 100 for collecting a coin
        std::cout << "Coin collected! Total coins: " << player.coins << std::endl;
        SoundManager::getInstance().playSound(SoundEffect::COIN);
    }

    void Update(Level &level) override
    {
        float gravity = 900.0f;
        float dt = GetFrameTime();
        ApplyGravity(velocity, gravity);

        ResolveCollision(level);

        position.x += velocity.x * dt;
        position.y += velocity.y * dt;
        rect.x = position.x;
        rect.y = position.y;
    }

    void ResolveCollision(Level &level)
    {
        collision.MushroomVsLevel(position, rect, velocity, level);
    };
};

#endif // COIN_H