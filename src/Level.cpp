#include "Level.h"
#include "Tile.h"
#include "FortressFlag.h"
#include "ItemManager.h"
#include <ctime>
#include <random>

Level_1_1::Level_1_1(const char *filePath)
{
    tileMap =
        {
            {1, std::make_shared<Tile>("./assets/Tiles/Overworld/pipe2.png")},
            {2, std::make_shared<Tile>("./assets/Tiles/Overworld/background.png")},
            {4, std::make_shared<Tile>("./assets/Tiles/Overworld/fortress.png")},
            {7, std::make_shared<Tile>("./assets/Tiles/Overworld/goalpole.png")},
            {8, std::make_shared<Tile>("./assets/Tiles/Overworld/ground.png")},
            {9, std::make_shared<Tile>("./assets/Tiles/Overworld/hardblock.png")},
            {10, std::make_shared<Tile>("./assets/Tiles/Overworld/pipe1.png")},
            {12, std::make_shared<Tile>("./assets/Tiles/Overworld/pipe3.png")},
            {13, std::make_shared<Tile>("./assets/Tiles/Overworld/question.png")},
            {17, std::make_shared<Tile>("./assets/Tiles/Overworld/brick.png")}
        };

    std::ifstream fin;
    fin.open(filePath);
    if (fin.is_open())
    {
        int grid_height, grid_width;
        fin >> grid_height >> grid_width;
        tileInstancesGrid.resize(grid_height, std::vector<std::shared_ptr<TileInstance>>(grid_width, nullptr));
        int temp = 0;
        for (int i = 0; i < grid_height; ++i)
        {
            for (int j = 0; j < grid_width; ++j)
            {
                fin >> temp;
                Vector2 pos = Vector2{j * TILE_SIZE * SCALE, i * TILE_SIZE * SCALE};
                addTileInstance(pos, temp, i, j);
            }
        }
    }
    fin.close();
}

void Level_1_1::addTileInstance(Vector2 &pos, int &tileID, int &x, int &y)
{
    const int t = TILE_SIZE * SCALE;
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
    {
        tileInstance = std::make_shared<FortressInstance>(pos, tileMap[tileID]);
        entityManager.initFortressFlag(pos, tileMap[tileID]->getTexture().width * SCALE);
    } break;
    case 7:
        tileInstance = std::make_shared<GoalpoleInstance>(pos, tileMap[tileID]);
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
    {
        tileInstance = std::make_shared<QuestionInstance>(pos, tileMap[tileID]);
        auto questionInstance = dynamic_cast<QuestionInstance*>(tileInstance.get());
        if ( x == 9 && y == 21 )
        {
            questionInstance->setHasMushroom();
            std::cout << "HAS MUSHROOM" << std::endl;
        }
        else if ( ( x == 9 && y == 78 ) || ( x == 5 && y == 109 ) )
        {
            questionInstance->setHasFlower();
            std::cout << "HAS FLOWER" << std::endl;
        }
        // x = 9 y = 9 Mushroom
        // x = 9 y = 78 Flower
        // x = 5 y = 109 Flower
    } break;
    case 17:
        tileInstance = std::make_shared<BrickInstance>(pos, tileMap[tileID]);
        break;
    default:
        break;
    }
    if (tileInstance)
        tileInstancesGrid[x][y] = tileInstance;
}

void Level_1_1::update(Mario &player, ItemManager& itemManager)
{
    for (int i = 0; i < getGridHeight(); i++)
    {
        for (int j = 0; j < getGridWidth(); j++)
        {
            if (tileInstancesGrid[i][j])
            {
                tileInstancesGrid[i][j]->update(player, itemManager);
                if (tileInstancesGrid[i][j]->getState() == STATE_BROKEN)
                {
                    entityManager.addBrickPieces(tileInstancesGrid[i][j]->getPos());
                    tileInstancesGrid[i][j] = nullptr;
                }
            }
        }
    }
    entityManager.update(player);
}

void Level_1_1::render()
{
    entityManager.renderFortressFlag();
    for (int i = 0; i < getGridHeight(); i++)
    {
        for (int j = 0; j < getGridWidth(); j++)
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

Level_1_3::Level_1_3(const char *filePath)
{
    tileMap =
        {
            {2, std::make_shared<Tile>("./assets/Tiles/Overworld/bigfortress.png")},
            {3, std::make_shared<Tile>("./assets/Tiles/Overworld/fortress.png")},
            {4, std::make_shared<Tile>("./assets/Tiles/Overworld/ground.png")},
            {5, std::make_shared<Tile>("./assets/Tiles/Overworld/grass_left.png")},
            {6, std::make_shared<Tile>("./assets/Tiles/Overworld/grass_middle.png")},
            {7, std::make_shared<Tile>("./assets/Tiles/Overworld/grass_right.png")},
            {9, std::make_shared<Tile>("./assets/Tiles/Overworld/hardblock.png")},
            {10, std::make_shared<Tile>("./assets/Tiles/Overworld/goalpole.png")},
            {11, std::make_shared<Tile>("./assets/Tiles/Overworld/grassbrick.png")},
            {12, std::make_shared<Tile>("./assets/Tiles/Overworld/background_3.png")},
            {13, std::make_shared<Tile>("./assets/Tiles/Overworld/question.png")}};

    int temp = 0;
    std::ifstream fin;
    fin.open(filePath);
    if (fin.is_open())
    {
        int grid_height, grid_width;
        fin >> grid_height >> grid_width;
        tileInstancesGrid.resize(grid_height, std::vector<std::shared_ptr<TileInstance>>(grid_width, nullptr));
        for (int i = 0; i < grid_height; ++i)
        {
            for (int j = 0; j < grid_width; ++j)
            {
                fin >> temp;
                Vector2 pos = Vector2{j * TILE_SIZE * SCALE, i * TILE_SIZE * SCALE};
                addTileInstance(pos, temp, i, j);
            }
        }
        fin.close();
    }
    entityManager.initPlatform(); // Initialize platform instances
}

void Level_1_3::addTileInstance(Vector2 &pos, int &tileID, int &x, int &y)
{
    std::shared_ptr<TileInstance> tileInstance = nullptr;
    switch (tileID)
    {
    case 2:
        tileInstance = std::make_shared<BigFortressInstance>(pos, tileMap[tileID]);
        break;
    case 3:
        tileInstance = std::make_shared<FortressInstance>(pos, tileMap[tileID]);
        break;
    case 4:
        tileInstance = std::make_shared<GroundInstance>(pos, tileMap[tileID]);
        break;
    case 5:
        tileInstance = std::make_shared<GrassInstance>(pos, tileMap[tileID]);
        break;
    case 6:
        tileInstance = std::make_shared<GrassInstance>(pos, tileMap[tileID]);
        break;
    case 7:
        tileInstance = std::make_shared<GrassInstance>(pos, tileMap[tileID]);
        break;
    case 9:
        tileInstance = std::make_shared<HardblockInstance>(pos, tileMap[tileID]);
        break;
    case 10:
        tileInstance = std::make_shared<GoalpoleInstance>(pos, tileMap[tileID]);
        break;
    case 11:
        tileInstance = std::make_shared<GrassBrickInstance>(pos, tileMap[tileID]);
        break;
    case 12:
        tileInstance = std::make_shared<BackgroundInstance>(pos, tileMap[tileID]);
        break;
    case 13:
        tileInstance = std::make_shared<QuestionInstance>(pos, tileMap[tileID]);
        break;
    default:
        break;
    }
    tileInstancesGrid[x][y] = tileInstance;
}

void Level_1_3::update(Mario &player, ItemManager& itemManager)
{
    for (int i = 0; i < getGridHeight(); i++)
    {
        for (int j = 0; j < getGridWidth(); j++)
        {
            if (tileInstancesGrid[i][j])
            {
                tileInstancesGrid[i][j]->update(player, itemManager);
            }
        }
    }
    entityManager.update(player);
}

void Level_1_3::render()
{
    for (int i = 0; i < getGridHeight(); i++)
    {
        for (int j = 0; j < getGridWidth(); j++)
        {
            if (tileInstancesGrid[i][j])
            {
                tileInstancesGrid[i][j]->render();
            }
        }
    }
    entityManager.render();
}

Level_1_4::Level_1_4(const char *filePath)
{
    srand(time(nullptr));
    tileMap =
        {
            {3, std::make_shared<Tile>("./assets/Tiles/Castle/lava.png")},
            {4, std::make_shared<Tile>("./assets/Tiles/Castle/lava_surface.png")},
            {5, std::make_shared<Tile>("./assets/Tiles/Castle/axe.png")},
            {7, std::make_shared<Tile>("./assets/Tiles/Castle/question.png")},
            {8, std::make_shared<Tile>("./assets/Tiles/Castle/used_block.png")},
            {9, std::make_shared<Tile>("./assets/Tiles/Castle/brick.png")},
            {10, std::make_shared<Tile>("./assets/Tiles/Castle/bridge.png")},
            {11, std::make_shared<Tile>("./assets/Tiles/Castle/chain.png")}};

    // for ( const auto& tile : tileMap )
    // {
    //     if ( tile.second == nullptr )
    //     {
    //         std::cout << "NULLPTR DETECTED" << std::endl;
    //     }
    //     else
    //     {
    //         if ( tile.second->getTexture().id <= 0 )
    //         {
    //             std::cout << "INVALID TEXTURE DETECTED" << std::endl;
    //         }
    //     }
    // }

    int temp = 0;
    std::ifstream fin;
    fin.open(filePath);
    if (fin.is_open())
    {
        int grid_height, grid_width;
        fin >> grid_height >> grid_width;
        tileInstancesGrid.resize(grid_height, std::vector<std::shared_ptr<TileInstance>>(grid_width, nullptr));
        for (int i = 0; i < grid_height; ++i)
        {
            for (int j = 0; j < grid_width; ++j)
            {
                fin >> temp;
                Vector2 pos = Vector2{j * TILE_SIZE * SCALE, i * TILE_SIZE * SCALE};
                addTileInstance(pos, temp, i, j);
            }
        }
        fin.close();
    }
}

void Level_1_4::addTileInstance(Vector2 &pos, int &tileID, int &x, int &y)
{
    std::shared_ptr<TileInstance> tileInstance = nullptr;
    switch (tileID)
    {
    case 3:
        tileInstance = std::make_shared<TileInstance>(pos, tileMap[tileID]);
        break;
    case 4:
        tileInstance = std::make_shared<LavaSurfaceInstance>(pos, tileMap[tileID]);
        break;
    case 5:
        tileInstance = std::make_shared<TileInstance>(pos, tileMap[tileID]);
        break;
    case 7:
        tileInstance = std::make_shared<QuestionInstance>(pos, tileMap[tileID]);
        break;
    case 8:
        tileInstance = std::make_shared<UsedBlockInstance>(pos, tileMap[tileID]);
        break;
    case 9:
        tileInstance = std::make_shared<TileInstance>(pos, tileMap[tileID]);
        break;
    case 10:
        tileInstance = std::make_shared<TileInstance>(pos, tileMap[tileID]);
        break;
    case 11:
        tileInstance = std::make_shared<TileInstance>(pos, tileMap[tileID]);
        break;
    case 12:
    {
        tileInstance = std::make_shared<UsedBlockInstance>(pos, tileMap[tileID - 4]);
        // auto usedBlockInstance = dynamic_cast<UsedBlockInstance*>(tileInstance.get());
        // usedBlockInstance->initFireBar(rand() % 361);
        entityManager.addFireBar(pos, rand() % 361);
    } break;
    default:
        break;
    }
    tileInstancesGrid[x][y] = tileInstance;
}

void Level_1_4::update(Mario &player, ItemManager& itemManager)
{
    for (int i = 0; i < getGridHeight(); i++)
    {
        for (int j = 0; j < getGridWidth(); j++)
        {
            if (tileInstancesGrid[i][j])
            {
                tileInstancesGrid[i][j]->update(player, itemManager);
            }
        }
    }
    entityManager.update(player);
}

void Level_1_4::render()
{
    for (int i = 0; i < getGridHeight(); i++)
    {
        for (int j = 0; j < getGridWidth(); j++)
        {
            if (tileInstancesGrid[i][j])
            {
                tileInstancesGrid[i][j]->render();
            }
        }
    }
    entityManager.render();
}

void EntityManager::addBrickPieces(Vector2 position)
{
    float t = TILE_SIZE * SCALE;
    std::shared_ptr<BrickPiece> brickPiece1 = std::make_shared<BrickPiece>(Vector2{position.x, position.y}, Vector2{t / 2, t / 2}, Rectangle{16, 0, 8, 8}, Vector2{-200, -500});
    std::shared_ptr<BrickPiece> brickPiece2 = std::make_shared<BrickPiece>(Vector2{position.x + t / 2, position.y}, Vector2{t / 2, t / 2}, Rectangle{24, 0, 8, 8}, Vector2{200, -500});
    std::shared_ptr<BrickPiece> brickPiece3 = std::make_shared<BrickPiece>(Vector2{position.x, position.y + t / 2}, Vector2{t / 2, t / 2}, Rectangle{16, 8, 8, 8}, Vector2{-200, -250});
    std::shared_ptr<BrickPiece> brickPiece4 = std::make_shared<BrickPiece>(Vector2{position.x + t / 2, position.y + t / 2}, Vector2{t / 2, t / 2}, Rectangle{24, 8, 8, 8}, Vector2{200, -250});
    brickPieces.push_back(brickPiece1);
    brickPieces.push_back(brickPiece2);
    brickPieces.push_back(brickPiece3);
    brickPieces.push_back(brickPiece4);
}

void EntityManager::initPlatform()
{
    std::shared_ptr<Tile> temp = std::make_shared<Tile>("./assets/Tiles/Overworld/platform.png");
    platforms.push_back(std::make_shared<PlatformInstance>(Vector2{54 * TILE_SIZE * SCALE, 5.5f * TILE_SIZE * SCALE},
                                                           Vector2{54 * TILE_SIZE * SCALE, 14 * TILE_SIZE * SCALE - temp->getTexture().height * SCALE}, temp, 0));
    platforms.push_back(std::make_shared<PlatformInstance>(Vector2{86 * TILE_SIZE * SCALE, 8 * TILE_SIZE * SCALE},
                                                           Vector2{0 * TILE_SIZE * SCALE, 8 * TILE_SIZE * SCALE - temp->getTexture().height * SCALE}, temp, 1));
    platforms.push_back(std::make_shared<PlatformInstance>(Vector2{94 * TILE_SIZE * SCALE, 9 * TILE_SIZE * SCALE},
                                                           Vector2{0 * TILE_SIZE * SCALE, 9 * TILE_SIZE * SCALE - temp->getTexture().height * SCALE}, temp, 1));
    platforms.push_back(std::make_shared<PlatformInstance>(Vector2{131 * TILE_SIZE * SCALE, 6 * TILE_SIZE * SCALE},
                                                           Vector2{0 * TILE_SIZE * SCALE, 6 * TILE_SIZE * SCALE - temp->getTexture().height * SCALE}, temp, 1));
}

void EntityManager::initFortressFlag(Vector2 position, float fortressWidth)
{
    fortressFlag = std::make_shared<FortressFlag>(Vector2{position.x + fortressWidth / 2 - TILE_SIZE * SCALE / 2, position.y + TILE_SIZE * SCALE / 4});
}

void EntityManager::addFireBar(Vector2 position, float initial_angle)
{
    Vector2 center = { position.x + TILE_SIZE * SCALE / 2, position.y + TILE_SIZE * SCALE / 2 };
    auto fireBar = std::make_shared<FireBar>(center, initial_angle);
    fireBars.push_back(std::move(fireBar));
}

void EntityManager::update(Mario &player)
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

    // for (const auto &platform : platforms)
    // {
    //     platform->update(player);
    // }

    for ( auto& fireBar : fireBars )
    {
        fireBar->Update(player);
    }

    // WIN 
    if ( fortressFlag )
    {
        fortressFlag->Update();
    } 
}

void EntityManager::render()
{
    for (const auto &brickPiece : brickPieces)
    {
        brickPiece->Draw();
    }
    for (const auto &platform : platforms)
    {
        platform->render();
    }
    for (const auto &fireBar : fireBars)
    {
        fireBar->Draw();
    }
}

void EntityManager::renderFortressFlag()
{
    if (fortressFlag)
        fortressFlag->Draw();
}
