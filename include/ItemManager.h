#ifndef ITEM_MANAGER_H
#define ITEM_MANAGER_H

#include <vector>
#include <memory>
#include "DGameObjects/Item.h"
#include "DGameObjects/Mushroom.h"
#include "DGameObjects/FireFlower.h"
#include "DGameState/PlayingState.h"
#include "DCore/SoundManager.h"
#include "Physics.h"
#include "Level.h"
#include "Character.h"

class Item;
class Mario;
class PlayingState;
class Level;

class ItemManager
{
private:
    std::vector<std::unique_ptr<Item>> items;

public:
    void AddItem(std::unique_ptr<Item> item);
    void SpawnMushroom(Vector2 position, Vector2 velocity, DIRECTION direction);
    void SpawnFireFlower(Vector2 position, Vector2 velocity, DIRECTION direction);
    void UpdateItems(Level &level, Character &character, PlayingState *ps);
    void DrawItems();
};

#endif // ITEM_MANAGER_H