#include "Entity.h"

class Coin : public Entity
{
    public:
        bool isCollected;

        Coin(Texture2D texture, Vector2 position): Entity(texture, position), isCollected(false) {}
        void Update() override
        {
            // Coins typically don't move, but you could add animations or effects here
        }
        void OnCollision(Entity &other) override
        {
        }
};