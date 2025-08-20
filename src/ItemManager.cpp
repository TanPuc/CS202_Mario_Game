#include "ItemManager.h"
#include <algorithm>

void ItemManager::AddItem(std::unique_ptr<Item> item)
{
    if (item)
    {
        items.push_back(std::move(item));
    }
}

void ItemManager::UpdateItems(Level &level, Mario &mario)
{
    for (auto &item : items)
    {
        if (item)
        {
            item->Update(level);
            if (CheckCollisionRecs(item->rect, mario.rect))
            {
                // std::cout << "Collision detected between Mario and item!" << std::endl;
                item->Collect(mario);
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