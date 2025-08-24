#include "EnemySpawnLocation.h"

// Enemy spawn location
// Level 1.1
// x = 22 y = 12: 1 goomba

// x = 40 y = 12: 1 goomba

// x = 48 y = 12: 2 goomba
    // Separate them

// x = 79 y = 8: 1 goomba
    // x = 81 y = 4: 1 goomba

// x = 95 y = 12: 1 goomba
    // x = 97 y = 12: 1 goomba

// x = 103 y = 12: 1 koopa 
    // x = 105 y = 12: 1 goomba
    // x = 110 y = 12: 1 goomba
    // x = 117 y = 12: 4 goomba 
        // Separate them 

// x = 165 y = 12: 2 goomba 
    // Separate them 

// Level 1.3


EnemySpawnLocationLevel_1_1::EnemySpawnLocationLevel_1_1(int tb) : EnemySpawnLocationLevel(tb)
{
    float t = TILE_SIZE * SCALE;
    Vector2 goomba_spawn_pos = { 22 * t, 12 * t };
    ETLs.push_back
    (
        EnemyTriggerLocation
        (
            tb, 
            goomba_spawn_pos,
            std::vector<EnemySpawnLocation>
            {
                EnemySpawnLocation(EnemyType::GOOMBA, goomba_spawn_pos)
            }
        )
    );
    
    Vector2 goomba_spawn_pos_1 = { 40 * t, 12 * t };
    ETLs.push_back
    (
        EnemyTriggerLocation
        (
            tb,
            goomba_spawn_pos_1,
            std::vector<EnemySpawnLocation>
            {
                EnemySpawnLocation(EnemyType::GOOMBA, goomba_spawn_pos_1)
            }
        )
    );

    Vector2 goomba_spawn_pos_2 = { 48 * t, 12 * t };
    Vector2 goomba_spawn_pos_3 = { 49 * t, 12 * t };
    ETLs.push_back
    (
        EnemyTriggerLocation
        (
            tb,
            goomba_spawn_pos_2,
            std::vector<EnemySpawnLocation>
            {
                EnemySpawnLocation(EnemyType::GOOMBA, goomba_spawn_pos_2),
                EnemySpawnLocation(EnemyType::GOOMBA, goomba_spawn_pos_3)
            }
        )
    );

    Vector2 goomba_spawn_pos_4 = { 79 * t, 8 * t };
    Vector2 goomba_spawn_pos_5 = { 81 * t, 4 * t };
    ETLs.push_back
    (
        EnemyTriggerLocation
        (
            tb,
            goomba_spawn_pos_4,
            std::vector<EnemySpawnLocation>
            {
                EnemySpawnLocation(EnemyType::GOOMBA, goomba_spawn_pos_4),
                EnemySpawnLocation(EnemyType::GOOMBA, goomba_spawn_pos_5)
            }
        )
    );

    Vector2 koopa_spawn_pos = { 103 * t, 12 * t };
    Vector2 goomba_spawn_pos_6 = { 105 * t, 12 * t };
    Vector2 goomba_spawn_pos_7 = { 110 * t, 12 * t };
    Vector2 goomba_spawn_pos_8 = { 117 * t, 12 * t };
    Vector2 goomba_spawn_pos_9 = { 118 * t, 12 * t };
    Vector2 goomba_spawn_pos_10 = { 119 * t, 12 * t };
    Vector2 goomba_spawn_pos_11 = { 120 * t, 12 * t };
    ETLs.push_back
    (
        EnemyTriggerLocation
        (
            tb,
            koopa_spawn_pos,
            std::vector<EnemySpawnLocation>
            {
                EnemySpawnLocation(EnemyType::KOOPA, koopa_spawn_pos),
                EnemySpawnLocation(EnemyType::GOOMBA, goomba_spawn_pos_6),
                EnemySpawnLocation(EnemyType::GOOMBA, goomba_spawn_pos_7),
                EnemySpawnLocation(EnemyType::GOOMBA, goomba_spawn_pos_8),
                EnemySpawnLocation(EnemyType::GOOMBA, goomba_spawn_pos_9),
                EnemySpawnLocation(EnemyType::GOOMBA, goomba_spawn_pos_10),
                EnemySpawnLocation(EnemyType::GOOMBA, goomba_spawn_pos_11)
            }
        )
    );

    Vector2 goomba_spawn_pos_12 = { 165 * t, 12 * t };
    Vector2 goomba_spawn_pos_13 = { 167 * t, 12 * t };
    ETLs.push_back
    (
        EnemyTriggerLocation
        (
            tb,
            goomba_spawn_pos_12,
            std::vector<EnemySpawnLocation>
            {
                EnemySpawnLocation(EnemyType::GOOMBA, goomba_spawn_pos_12),
                EnemySpawnLocation(EnemyType::GOOMBA, goomba_spawn_pos_13)
            }
        )
    );
}

std::vector<EnemySpawnLocation> EnemySpawnLocationLevel::getEnemySpawnLocation(float right_border_x)
{
    std::vector<EnemySpawnLocation> result{0};
    for ( auto& ETL : ETLs )
    {
        // Check if the right border is past the trigger position
        if ( right_border_x > ETL.trigger_position.x && !ETL.triggered )
        {
            ETL.triggered = true; // Mark as triggered
            for ( const auto& enemy : ETL.enemies )
            {
                result.push_back(enemy);
            }
        }
    }
    return result;
}