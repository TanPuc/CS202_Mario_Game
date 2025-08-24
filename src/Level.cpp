#include "Level.h"
#include "Tile.h"
#include "DGameState/PlayingState.h"

Level::Level(const char *filePath, PlayingState *ps)
{
    tileMap = {
        {1, std::make_shared<Tile>("./assets/Tiles/Overworld/pipe2.png")},
        {2, std::make_shared<Tile>("./assets/Tiles/Overworld/background.png")},
        {4, std::make_shared<Tile>("./assets/Tiles/Overworld/fortress.png")},
        {7, std::make_shared<Tile>("./assets/Tiles/Overworld/goalpole.png")},
        {8, std::make_shared<Tile>("./assets/Tiles/Overworld/ground.png")},
        {9, std::make_shared<Tile>("./assets/Tiles/Overworld/hardblock.png")},
        {10, std::make_shared<Tile>("./assets/Tiles/Overworld/pipe1.png")},
        {12, std::make_shared<Tile>("./assets/Tiles/Overworld/pipe3.png")},
        {13, std::make_shared<Tile>("./assets/Tiles/Overworld/question.png")},
        {17, std::make_shared<Tile>("./assets/Tiles/Overworld/brick.png")}};

    int temp = 0;
    std::ifstream fin;
    fin.open(filePath);
    if (fin.is_open())
    {
        for (int i = 0; i < GRID_HEIGHT; ++i)
            for (int j = 0; j < GRID_WIDTH; ++j)
            {
                fin >> temp;
                Vector2 pos = Vector2{j * TILE_SIZE * SCALE, i * TILE_SIZE * SCALE};
                addTileInstance(pos, temp, i, j, ps);
            }
        fin.close();
    }
}

void Level::addTileInstance(Vector2 pos, int tileID, int x, int y, PlayingState *ps)
{
    float t = TILE_SIZE * SCALE;
    std::shared_ptr<TileInstance> tileInstance = nullptr;
    switch (tileID)
    {
    case 1:
    {
        tileInstance = std::make_shared<PipeInstance2>(pos, tileMap[tileID]);
        tileInstancesGrid[x][y + 1] = std::make_shared<DummyInstance>(Vector2{pos.x + t, pos.y});
        tileInstancesGrid[x + 1][y] = std::make_shared<DummyInstance>(Vector2{pos.x, pos.y + t});
        tileInstancesGrid[x + 1][y + 1] = std::make_shared<DummyInstance>(Vector2{pos.x + t, pos.y + t});
        tileInstancesGrid[x + 2][y] = std::make_shared<DummyInstance>(Vector2{pos.x, pos.y + 2 * t});
        tileInstancesGrid[x + 2][y + 1] = std::make_shared<DummyInstance>(Vector2{pos.x + t, pos.y + 2 * t});
    }
    break;
    case 2:
        tileInstance = std::make_shared<BackgroundInstance>(pos, tileMap[tileID]);
        break;
    case 4:
        tileInstance = std::make_shared<FortressInstance>(pos, tileMap[tileID]);
        break;
    case 7:
    {
        auto goalpoleInstance = std::make_shared<GoalpoleInstance>(pos, tileMap[tileID]);
        tileInstance = goalpoleInstance;

        if (ps)
        {
            ps->setGoalpole(goalpoleInstance);
        }
    }
    break;
    case 8:
        tileInstance = std::make_shared<GroundInstance>(pos, tileMap[tileID]);
        break;
    case 9:
        tileInstance = std::make_shared<HardblockInstance>(pos, tileMap[tileID]);
        break;
    case 10:
    {
        tileInstance = std::make_shared<PipeInstance1>(pos, tileMap[tileID]);
        tileInstancesGrid[x][y + 1] = std::make_shared<DummyInstance>(Vector2{pos.x + t, pos.y});
        tileInstancesGrid[x + 1][y] = std::make_shared<DummyInstance>(Vector2{pos.x, pos.y + t});
        tileInstancesGrid[x + 1][y + 1] = std::make_shared<DummyInstance>(Vector2{pos.x + t, pos.y + t});
    }
    break;
    case 12:
    {
        tileInstance = std::make_shared<PipeInstance3>(pos, tileMap[tileID]);
        tileInstancesGrid[x][y + 1] = std::make_shared<DummyInstance>(Vector2{pos.x + t, pos.y});
        tileInstancesGrid[x + 1][y] = std::make_shared<DummyInstance>(Vector2{pos.x, pos.y + t});
        tileInstancesGrid[x + 1][y + 1] = std::make_shared<DummyInstance>(Vector2{pos.x + t, pos.y + t});
        tileInstancesGrid[x + 2][y] = std::make_shared<DummyInstance>(Vector2{pos.x, pos.y + 2 * t});
        tileInstancesGrid[x + 2][y + 1] = std::make_shared<DummyInstance>(Vector2{pos.x + t, pos.y + 2 * t});
        tileInstancesGrid[x + 3][y] = std::make_shared<DummyInstance>(Vector2{pos.x, pos.y + 3 * t});
        tileInstancesGrid[x + 3][y + 1] = std::make_shared<DummyInstance>(Vector2{pos.x + t, pos.y + 3 * t});
    }
    break;
    case 13:
        tileInstance = std::make_shared<QuestionInstance>(pos, tileMap[tileID]);
        break;
    case 17:
        tileInstance = std::make_shared<BrickInstance>(pos, tileMap[tileID]);
        break;
    default:
        break;
    }
    if (tileInstance)
    {
        tileInstancesGrid[x][y] = tileInstance;
    }
}

void Level::update(Character &player, PlayingState *ps)
{
    for (int i = 0; i < GRID_HEIGHT; i++)
    {
        for (int j = 0; j < GRID_WIDTH; j++)
        {
            if (tileInstancesGrid[i][j])
            {
                tileInstancesGrid[i][j]->update(player, ps);
                if (tileInstancesGrid[i][j]->getState() == STATE_BROKEN)
                {
                    entityManager.addBrickPieces(tileInstancesGrid[i][j]->getPos());
                    tileInstancesGrid[i][j] = nullptr;
                }
            }
        }
    }
    entityManager.update();
}

void Level::render()
{
    for (int i = 0; i < GRID_HEIGHT; i++)
    {
        for (int j = 0; j < GRID_WIDTH; j++)
        {
            if (tileInstancesGrid[i][j])
            {
                tileInstancesGrid[i][j]->render();
                DrawRectangleLinesEx(tileInstancesGrid[i][j]->bbox, 2.0f, RED); // Debug: Draw bounding box
            }
        }
    }
    entityManager.render();
}

void EntityManager::addBrickPieces(Vector2 position)
{
    std::shared_ptr<BrickPiece> brickPiece1 = std::make_shared<BrickPiece>(Vector2{position.x, position.y}, Vector2{32, 32}, Rectangle{16, 0, 8, 8}, Vector2{-200, -500});
    std::shared_ptr<BrickPiece> brickPiece2 = std::make_shared<BrickPiece>(Vector2{position.x + 32, position.y}, Vector2{32, 32}, Rectangle{24, 0, 8, 8}, Vector2{200, -500});
    std::shared_ptr<BrickPiece> brickPiece3 = std::make_shared<BrickPiece>(Vector2{position.x, position.y + 32}, Vector2{32, 32}, Rectangle{16, 8, 8, 8}, Vector2{-200, -250});
    std::shared_ptr<BrickPiece> brickPiece4 = std::make_shared<BrickPiece>(Vector2{position.x + 32, position.y + 32}, Vector2{32, 32}, Rectangle{24, 8, 8, 8}, Vector2{200, -250});
    brickPieces.push_back(brickPiece1);
    brickPieces.push_back(brickPiece2);
    brickPieces.push_back(brickPiece3);
    brickPieces.push_back(brickPiece4);
}

void EntityManager::update()
{
    for (int i = 0; i < brickPieces.size(); i++)
    {
        brickPieces[i]->Update();
        // Check for out-of-screen brick pieces to remove
        if (brickPieces[i]->isOutOfScreen)
            toRemove.push_back(i);
    }
    std::sort(toRemove.rbegin(), toRemove.rend());
    for (const auto &idx : toRemove)
        brickPieces.erase(brickPieces.begin() + idx);
    toRemove.clear();
}

void EntityManager::render()
{
    for (const auto &brickPiece : brickPieces)
    {
        brickPiece->Draw();
    }
}

// Level_2::Level_2(const char* filePath) {
//     tileMap =
//     {
//         { 2, std::make_shared<Tile>("./assets/Tiles/Overworld/bigfortress.png")},
//         { 3, std::make_shared<Tile>("./assets/Tiles/Overworld/fortress.png")},
//         { 4, std::make_shared<Tile>("./assets/Tiles/Overworld/ground.png")},
//         { 5, std::make_shared<Tile>("./assets/Tiles/Overworld/grass_left.png")},
//         { 6, std::make_shared<Tile>("./assets/Tiles/Overworld/grass_middle.png")},
//         { 7, std::make_shared<Tile>("./assets/Tiles/Overworld/grass_right.png")},
//         { 9, std::make_shared<Tile>("./assets/Tiles/Overworld/hardblock.png")},
//         { 10, std::make_shared<Tile>("./assets/Tiles/Overworld/goalpole.png")},
//         { 11, std::make_shared<Tile>("./assets/Tiles/Overworld/grassbrick.png")}
//     };

//     int temp = 0;
//     std::ifstream fin;
//     fin.open(filePath);
//     if ( fin.is_open() )
//     {
//         for (int i = 0; i < GRID_HEIGHT; ++i)
//         {
//             for (int j = 0; j < GRID_WIDTH_2; ++j)
//             {
//                 fin >> temp;
//                 std::cout << temp << std::endl;
//                 Vector2 pos = Vector2{ j * TILE_SIZE * SCALE, i * TILE_SIZE * SCALE };
//                 addTileInstance(pos, temp, i, j);
//             }
//         }
//         fin.close();
//     }
// }

// void Level_2::addTileInstance(Vector2& pos, int& tileID, int& x, int& y)
// {
//     std::shared_ptr<TileInstance> tileInstance = nullptr;
//     switch(tileID) {
//         case 2: tileInstance = std::make_shared<BigFortressInstance>(pos, tileMap[tileID]); break;
//         case 3: tileInstance = std::make_shared<FortressInstance>(pos, tileMap[tileID]); break;
//         case 4: tileInstance = std::make_shared<GroundInstance>(pos, tileMap[tileID]); break;
//         case 5: tileInstance = std::make_shared<GrassInstance>(pos, tileMap[tileID]); break;
//         case 6: tileInstance = std::make_shared<GrassInstance>(pos, tileMap[tileID]); break;
//         case 7: tileInstance = std::make_shared<GrassInstance>(pos, tileMap[tileID]); break;
//         case 9: tileInstance = std::make_shared<HardblockInstance>(pos, tileMap[tileID]); break;
//         case 10: tileInstance = std::make_shared<GoalpoleInstance>(pos, tileMap[tileID]); break;
//         case 11: tileInstance = std::make_shared<GrassBrickInstance>(pos, tileMap[tileID]); break;
//         default: break;
//     }
//     tileInstancesGrid[x][y] = tileInstance;
// }

// void Level_2::update(Character& player)
// {
//     for ( int i = 0; i < GRID_HEIGHT; i++ )
//     {
//         for ( int j = 0; j < GRID_WIDTH_2; j++ )
//         {
//             if ( tileInstancesGrid[i][j] )
//             {
//                 tileInstancesGrid[i][j]->update(player);
//             }
//         }
//     }
// }

// void Level_2::render()
// {
//     for ( int i = 0; i < GRID_HEIGHT; i++ )
//     {
//         for ( int j = 0; j < GRID_WIDTH_2; j++ )
//         {
//             if ( tileInstancesGrid[i][j] )
//             {
//                 tileInstancesGrid[i][j]->render();
//             }
//         }
//     }
// }