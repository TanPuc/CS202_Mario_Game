#include "EnemySpawnLocation.h"

// Enemy spawn location
// Level 1.1
// All koopas are green 
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

// Level 1.4


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

EnemySpawnLocationLevel_1_1::EnemySpawnLocationLevel_1_1(int tb) 
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
                EnemySpawnLocation(EnemyType::goopa, goomba_spawn_pos)
            }
        )
    );
    
    Vector2 goomba_spawn_pos_1 = { 40.1f * t, 12 * t };
    ETLs.push_back
    (
        EnemyTriggerLocation
        (
            tb,
            goomba_spawn_pos_1,
            std::vector<EnemySpawnLocation>
            {
                EnemySpawnLocation(EnemyType::goopa, goomba_spawn_pos_1)
            }
        )
    );

    Vector2 goomba_spawn_pos_2 = { 48.1f * t, 12 * t };
    Vector2 goomba_spawn_pos_3 = { 49.6f * t, 12 * t };
    ETLs.push_back
    (
        EnemyTriggerLocation
        (
            tb,
            goomba_spawn_pos_2,
            std::vector<EnemySpawnLocation>
            {
                EnemySpawnLocation(EnemyType::goopa, goomba_spawn_pos_2),
                EnemySpawnLocation(EnemyType::goopa, goomba_spawn_pos_3)
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
                EnemySpawnLocation(EnemyType::goopa, goomba_spawn_pos_4),
                EnemySpawnLocation(EnemyType::goopa, goomba_spawn_pos_5)
            }
        )
    );

    Vector2 koopa_spawn_pos = { 103 * t, 11 * t };
    Vector2 goomba_spawn_pos_6 = { 105 * t, 12 * t };
    Vector2 goomba_spawn_pos_7 = { 110 * t, 12 * t };
    Vector2 goomba_spawn_pos_8 = { 117 * t, 12 * t };
    Vector2 goomba_spawn_pos_9 = { 118.5f * t, 12 * t };
    Vector2 goomba_spawn_pos_10 = { 120.5f * t, 12 * t };
    Vector2 goomba_spawn_pos_11 = { 122 * t, 12 * t };
    ETLs.push_back
    (
        EnemyTriggerLocation
        (
            tb,
            koopa_spawn_pos,
            std::vector<EnemySpawnLocation>
            {
                EnemySpawnLocation(EnemyType::koopa, koopa_spawn_pos),
                EnemySpawnLocation(EnemyType::goopa, goomba_spawn_pos_6),
                EnemySpawnLocation(EnemyType::goopa, goomba_spawn_pos_7),
                EnemySpawnLocation(EnemyType::goopa, goomba_spawn_pos_8),
                EnemySpawnLocation(EnemyType::goopa, goomba_spawn_pos_9),
                EnemySpawnLocation(EnemyType::goopa, goomba_spawn_pos_10),
                EnemySpawnLocation(EnemyType::goopa, goomba_spawn_pos_11)
            }
        )
    );

    Vector2 goomba_spawn_pos_12 = { 165.1f * t, 12 * t };
    Vector2 goomba_spawn_pos_13 = { 167 * t, 12 * t };
    ETLs.push_back
    (
        EnemyTriggerLocation
        (
            tb,
            goomba_spawn_pos_12,
            std::vector<EnemySpawnLocation>
            {
                EnemySpawnLocation(EnemyType::goopa, goomba_spawn_pos_12),
                EnemySpawnLocation(EnemyType::goopa, goomba_spawn_pos_13)
            }
        )
    );
}

// Level 1.3
// Tiled map are 1 column short 
// All koopas are red
// x = 27 y = 3: 1 koopa

// x = 41 y = 3: 1 goomba

// x = 44 y = 3: 1 goomba

// x = 72 y = 7: 1 flyingKoopa
    // x = 77 y = 5: 1 goomba
    
// x = 107 y = 5: 1 koopa
    // x = 113 y = 12: 1 flying koopa

// x = 131 y = 11: 1 koopa

EnemySpawnLocationLevel_1_3::EnemySpawnLocationLevel_1_3(int tb)
{
    float t = TILE_SIZE * SCALE;

    Vector2 koopa_spawn_pos = { 27 * t, 3 * t };
    ETLs.push_back
    (
        EnemyTriggerLocation
        (
            tb,
            koopa_spawn_pos,
            std::vector<EnemySpawnLocation>
            {
                EnemySpawnLocation(EnemyType::koopa, koopa_spawn_pos)
            }
        )
    );

    Vector2 goomba_spawn_pos = { 41 * t, 3 * t };
    ETLs.push_back
    (
        EnemyTriggerLocation
        (
            tb,
            goomba_spawn_pos,
            std::vector<EnemySpawnLocation>
            {
                EnemySpawnLocation(EnemyType::goopa, goomba_spawn_pos)
            }
        )
    );

    Vector2 goomba_spawn_pos_1 = { 44 * t, 3 * t };
    ETLs.push_back
    (
        EnemyTriggerLocation
        (
            tb,
            goomba_spawn_pos_1,
            std::vector<EnemySpawnLocation>
            {
                EnemySpawnLocation(EnemyType::goopa, goomba_spawn_pos_1)
            }
        )
    );

    Vector2 flying_koopa_spawn_pos = { 73 * t, 7 * t };
    Vector2 goomba_spawn_pos_2 = { 77 * t, 5 * t };
    ETLs.push_back
    (
        EnemyTriggerLocation
        (
            tb,
            flying_koopa_spawn_pos,
            std::vector<EnemySpawnLocation>
            {
                // CHECKING LATER
                EnemySpawnLocation(EnemyType::cheepcheep, flying_koopa_spawn_pos),
                EnemySpawnLocation(EnemyType::goopa, goomba_spawn_pos_2)
            }
        )
    );

    Vector2 koopa_spawn_pos_1 = { 107 * t, 5 * t };
    Vector2 flying_koopa_spawn_pos_1 = { 113 * t, 12 * t };
    ETLs.push_back
    (
        EnemyTriggerLocation
        (
            tb,
            koopa_spawn_pos_1,
            std::vector<EnemySpawnLocation>
            {
                EnemySpawnLocation(EnemyType::koopa, koopa_spawn_pos_1),
                // CHECKING LATER
                EnemySpawnLocation(EnemyType::cheepcheep, flying_koopa_spawn_pos_1)
            }
        )
    );

    Vector2 koopa_spawn_pos_2 = { 131 * t, 11 * t };
    ETLs.push_back
    (
        EnemyTriggerLocation
        (
            tb,
            koopa_spawn_pos_2,
            std::vector<EnemySpawnLocation>
            {
                EnemySpawnLocation(EnemyType::koopa, koopa_spawn_pos_2)
            }
        )
    );
}

// Level 1.4
// x = 135 y = 8: 1 bowser 

EnemySpawnLocationLevel_1_4::EnemySpawnLocationLevel_1_4(int tb)
{
    float t = TILE_SIZE * SCALE;

    Vector2 bowser_spawn_pos = { 135 * t, 8 * t };
    ETLs.push_back
    (
        EnemyTriggerLocation
        (
            tb,
            bowser_spawn_pos,
            std::vector<EnemySpawnLocation>
            {
                EnemySpawnLocation(EnemyType::bowser, bowser_spawn_pos)
            }
        )
    );
}