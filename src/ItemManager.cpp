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
            if (CheckCollision(*item, mario))
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