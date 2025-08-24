#ifndef ENEMY_SPAWN_LOCATION_H
#define ENEMY_SPAWN_LOCATION_H

#include <raylib.h>
#include <vector>
#include "Enemy/enemyEnum.h"
#include "GlobalVariables.h"

struct EnemySpawnLocation
{
    EnemyType type;
    Vector2 spawn_position;
    EnemySpawnLocation() {}
    EnemySpawnLocation(EnemyType t, Vector2 pos) 
        : type(t), spawn_position(pos) {}
};

struct EnemyTriggerLocation
{
    Vector2 trigger_position;
    bool triggered = false;
    std::vector<EnemySpawnLocation> enemies;

    EnemyTriggerLocation() 
    {
        
    }
    EnemyTriggerLocation(int tb, Vector2 t, std::vector<EnemySpawnLocation> e)
        : trigger_position(t), enemies(e) 
    {
        // Adjust trigger position based on the number of tiles before
        trigger_position.x -= tb * TILE_SIZE * SCALE; 
    }
};

class EnemySpawnLocationLevel
{
public:
    std::vector<EnemyTriggerLocation> ETLs;
    std::vector<EnemySpawnLocation> getEnemySpawnLocation(float right_border_x);
};

class EnemySpawnLocationLevel_1_1 : public EnemySpawnLocationLevel
{
public:
    EnemySpawnLocationLevel_1_1(int tb);
};

class EnemySpawnLocationLevel_1_3 : public EnemySpawnLocationLevel 
{
public:
    EnemySpawnLocationLevel_1_3(int tb);
};

class EnemySpawnLocationLevel_1_4 : public EnemySpawnLocationLevel
{
public:
    EnemySpawnLocationLevel_1_4(int tb);
};

#endif // ENEMY_SPAWN_LOCATION_H