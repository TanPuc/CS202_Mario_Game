#include "ItemManager.h"
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
            if (!item->isCollected && CheckCollisionRecs(item->rect, character.rect))
            {
                item->Collect(character);
            }
        }
    }

    items.erase(std::remove_if(items.begin(), items.end(),
                               [](const auto &item)
                               { return !item || item->isCollected; }),
                items.end());
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
    items.push_back(std::move(std::make_unique<Mushroom>(position, velocity, direction)));
}

void ItemManager::SpawnFireFlower(Vector2 position, Vector2 velocity, DIRECTION direction)
{
    items.push_back(std::move(std::make_unique<FireFlower>(position, velocity, direction)));
}