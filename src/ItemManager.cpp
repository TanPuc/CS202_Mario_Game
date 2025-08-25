#include "ItemManager.h"
#include "Level.h"
#include "DGameState/PlayingState.h"
#include <algorithm>

void ItemManager::AddItem(std::unique_ptr<Item> item)
{
    if (item)
    {
        items.push_back(std::move(item));
    }
}

void ItemManager::UpdateItems(Level &level, Character &character, PlayingState *ps)
{
    for (auto &item : items)
    {
        if (item)
        {
            item->Update(level);
            if (CheckCollisionRecs(item->rect, character.rect))
            {
                // std::cout << "Collision detected between Character and item!" << std::endl;
                item->Collect(character);
            }
        }
    }

    // Remove destroyed items (optional)
    for (auto it = items.begin(); it != items.end();)
    {
        if (!(*it)->isActive || (*it)->isCollected)
        {
            it = items.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void ItemManager::DrawItems()
{
    for (const auto &item : items)
    {
        if (item)
        {
            item->Draw();
        }
    }
}

void ItemManager::SpawnMushroom(Vector2 position, Vector2 velocity, DIRECTION direction)
{
    items.push_back(std::make_unique<Mushroom>(position, velocity, direction));
}

void ItemManager::SpawnFireFlower(Vector2 position, Vector2 velocity, DIRECTION direction)
{
    items.push_back(std::make_unique<FireFlower>(position, velocity, direction));
}
void ItemManager::SpawnCoinBlock(Vector2 position)
{
    items.push_back(std::make_unique<CoinBlock>(position, coinBlockSprite));
}

void ItemManager::SpawnCoin(Vector2 position, Vector2 velocity)
{
    items.push_back(std::make_unique<Coin>(position, velocity));
}