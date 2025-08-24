#include <raylib.h>
#include <vector>
#include "GlobalVariables.h"

enum EnemyType
{
    GOOMBA,
    KOOPA
};

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
    int tilesBefore; 
    Vector2 trigger_position;
    bool triggered = false;
    std::vector<EnemySpawnLocation> enemies;

    EnemyTriggerLocation() 
    {
        
    }
    EnemyTriggerLocation(int tb, Vector2 t, std::vector<EnemySpawnLocation> e)
        : tilesBefore(tb), trigger_position(t), enemies(e) 
    {
        // Adjust trigger position based on the number of tiles before
        trigger_position.x -= tb * TILE_SIZE * SCALE; 
    }
};

class EnemySpawnLocationLevel
{
public:
    int tilesBefore;
    std::vector<EnemyTriggerLocation> ETLs;
    EnemySpawnLocationLevel(int tb) : tilesBefore(tb) {}
    std::vector<EnemySpawnLocation> getEnemySpawnLocation(float right_border_x);
};

class EnemySpawnLocationLevel_1_1 : public EnemySpawnLocationLevel
{
public:
    EnemySpawnLocationLevel_1_1(int tb);
    // How to use
    // Declaration
    // std::shared_ptr<EnemySpawnLocationLevel> ESLL = std::make_shared<EnemySpawnLocationLevel_1_1>(5);
    // Loop
    // std::vector<EnemySpawnLocation> ESLs = ESLL->getEnemySpawnLocation(right_border_x);
    // for ( const auto& ESL : ESLs )
    // {
    //     enemyManager.spawnEnemy(ESL.type, ESL.spawn_position);
    // }
};

