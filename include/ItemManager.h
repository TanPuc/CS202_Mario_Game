#ifndef ITEM_MANAGER_H
#define ITEM_MANAGER_H

#include <vector>
#include <memory>
#include "DGameObjects/Item.h"
#include "DGameObjects/Mushroom.h"
#include "DGameObjects/FireFlower.h"
#include "DGameObjects/CoinBlock.h"
#include "DGameObjects/Coin.h"
#include "Physics.h"
// #include "Level.h"
#include "Mario.h"

// Forward declaration
class Level;

class ItemManager
{
private:
    std::vector<std::unique_ptr<Item>> items;
    // std::unique_ptr<CoinBlockSprite> coinBlockSprite;
    std::shared_ptr<CoinBlockSprite> coinBlockSprite;
public:
    ItemManager()
    {
        coinBlockSprite = std::make_shared<CoinBlockSprite>();
    };

    void AddItem(std::unique_ptr<Item> item);
    void SpawnMushroom(Vector2 position, Vector2 velocity, DIRECTION direction);
    void SpawnFireFlower(Vector2 position, Vector2 velocity, DIRECTION direction);
    void SpawnCoinBlock(Vector2 position);
    void SpawnCoin(Vector2 position, Vector2 velocity);
    void UpdateItems(Level &level, Mario &mario);
    void DrawItems();
};

#endif // ITEM_MANAGER_H