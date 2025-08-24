#ifndef ITEM_MANAGER_H
#define ITEM_MANAGER_H

#include <vector>
#include <memory>
#include "DGameObjects/Item.h"
#include "DGameObjects/Mushroom.h"
#include "DGameObjects/FireFlower.h"
#include "Physics.h"
// #include "Level.h"
#include "Mario.h"

// Forward declaration
class Level;

class ItemManager
{
private:
    std::vector<std::unique_ptr<Item>> items;

public:
    void AddItem(std::unique_ptr<Item> item);
    void SpawnMushroom(Vector2 position, Vector2 velocity, DIRECTION direction);
    void SpawnFireFlower(Vector2 position, Vector2 velocity, DIRECTION direction);
    void UpdateItems(Level &level, Mario &mario);
    void DrawItems();
};

#endif // ITEM_MANAGER_H