#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include <memory>
#include "EnemySpawnLocation.h"

// Forward declaration
class Level;
class EnemyManager;
class Mario;
class ItemManager;

class LevelManager
{
public:
    std::unique_ptr<Level> m_currentLevel;
    std::unique_ptr<EnemySpawnLocationLevel> m_enemySpawnLocationLevel;

    Level* getCurrentLevel()
    {
        return m_currentLevel.get();
    }

    void LoadLevel(int levelNumber);
    
    void SpawnEnemy(float right_border_camera_x, EnemyManager& enemyManager);

    void Update(Mario& player, ItemManager& itemManager);

    void Draw();
};

#endif // LEVEL_MANAGER_H