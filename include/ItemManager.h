#ifndef ITEM_MANAGER_H
#define ITEM_MANAGER_H

#include <vector>
#include <memory>
#include "DGameObjects/Item.h"
#include "Physics.h"
#include "Level.h"
#include "Mario.h"

class ItemManager
{
private:
    std::vector<std::unique_ptr<Item>> items;

public:
    void AddItem(std::unique_ptr<Item> item);
    void UpdateItems(Level &level, Mario &mario);
    void DrawItems();
};

#endif // ITEM_MANAGER_H