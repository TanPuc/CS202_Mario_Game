#include "LevelManager.h"
#include "Enemy/EnemyManager.h"
#include "EnemySpawnLocation.h"
#include "Level.h"

void LevelManager::SpawnEnemy(float right_border_camera_x, EnemyManager& enemyManager)
{
    if (m_enemySpawnLocationLevel)
    {
        std::vector<EnemySpawnLocation> ESLs = m_enemySpawnLocationLevel->getEnemySpawnLocation(right_border_camera_x);
        for ( auto& ESL : ESLs )
        {
            enemyManager.spawnEnemyAt(ESL.type, ESL.spawn_position);
            std::cout << ESL.type << " spawned at " << ESL.spawn_position.x << ", " << ESL.spawn_position.y << std::endl;
        }
    }
}

void LevelManager::LoadLevel(int levelNumber, PlayingState *ps)
{
    switch(levelNumber)
    {
        case 1:
        {
            m_currentLevel = std::make_unique<Level_1_1>("./assets/Levels/world_1.1.txt", ps);
            m_enemySpawnLocationLevel = std::make_unique<EnemySpawnLocationLevel_1_1>(5);
        } break;
        case 2:
        {
            m_currentLevel = std::make_unique<Level_1_3>("./assets/Levels/world_1.3.txt", ps);
            m_enemySpawnLocationLevel = std::make_unique<EnemySpawnLocationLevel_1_3>(5);
        } break;
        case 3:
        {
            m_currentLevel = std::make_unique<Level_1_4>("./assets/Levels/world_1.4.txt", ps);
            m_enemySpawnLocationLevel = std::make_unique<EnemySpawnLocationLevel_1_4>(5);
        } break;
        default: break;
    }
}

void LevelManager::Update(Character& player, ItemManager& itemManager, PlayingState *ps)
{
    if (m_currentLevel)
    {
        m_currentLevel->update(player, itemManager, ps);
    }
}

void LevelManager::Draw()
{
    if (m_currentLevel)
    {
        m_currentLevel->render();
    }
}