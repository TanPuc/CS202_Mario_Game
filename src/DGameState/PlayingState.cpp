#include "DGameState/PlayingState.h"
#include "DGameState/GameOverState.h"
#include "DGameState/WinState.h"
#include "DGameState/GetReadyState.h"
#include "DGameState/PauseState.h"
#include "DCore/SoundManager.h"
#include "DCore/SaveManager.h"

PlayingState::PlayingState(GameStateManager *manager, const GameData &initialData) : gsm(manager), currentData(initialData) {}

void PlayingState::enter()
{
    enemyAsset::Load();
    SoundManager::getInstance().stopMusic();
    SoundManager::getInstance().playMusic(MusicTrack::MAIN_THEME);
    heartTexture = LoadTexture("assets/mario.png");
    coinIcon = LoadTexture("assets/mario.png");
    marioTexture = LoadTexture("assets/mario.png");
    pauseIconTexture = LoadTexture("assets/pause.png");
    pauseButton = std::make_unique<ImageButton>(
        Vector2{(float)GetScreenWidth() - 60, 20},
        Vector2{40, 40},
        pauseIconTexture,
        "",
        [this]()
        {
            gsm->pushState(new PauseState(gsm, worldNum, levelNum));
        });

    // player = std::make_unique<Mario>(Vector2{float(GetScreenWidth() / 2 - 16), 0.0f});
    // player = std::make_unique<Mario>(START_POS_WORLD_1_1);


    player = std::make_unique<Mario>(currentData.playerPosition);
    player->lives = currentData.lives;
    player->coins = currentData.coins;
    player->score = currentData.score;

    worldNum = currentData.worldNum;
    levelNum = currentData.levelNum;

    // Items
    // entities.push_back(std::make_unique<Coin>(Vector2{200, 100}));
    // entities.push_back(std::make_unique<Mushroom>(Vector2{300, 100}));
    itemManager.SpawnCoinBlock(Vector2{200, 100});
    itemManager.SpawnCoin(Vector2{200, 100}, Vector2{0, -100.0f});
    // itemManager.AddItem(std::make_unique<Mushroom>(Vector2{300, 100}));
    // itemManager.AddItem(std::make_unique<FireFlower>(Vector2{400, 100}));

    // LEVEL
    levelManager = std::make_unique<LevelManager>();
    levelManager->LoadLevel(levelNum);

    player->lives = gsm->getContext().lives;
    player->coins = 0;
    player->score = 0;

    cameraPos = Vector2{0.0f, 0.0f};

    hudManager = std::make_unique<HUDManager>(heartTexture, coinIcon);
    playerAdapter = std::make_unique<PlayerAdapter>(player.get());

    playerAdapter->attach(hudManager.get());
    playerAdapter->init();

    hudManager->resetTime(currentData.timeRemaining);
    hudManager->updateWorld(worldNum, levelNum);
    playerAdapter->update();

    enemyManager = new EnemyManager(player.get(), levelManager->getCurrentLevel(), fireBallManager.GetFireBalls());

    // Vector2 posEnemy = { 300, 100 };
    // enemyManager->spawnEnemyAt(EnemyType::goopa, posEnemy);
    // enemyManager->spawnEnemyAt(EnemyType::koopa, posEnemy);
    // enemyManager->spawnEnemyAt(EnemyType::cheepcheep, posEnemy);
    // enemyManager->spawnEnemyAt(EnemyType::beezybettle, posEnemy);
    // enemyManager->spawnEnemyAt(EnemyType::blooper, posEnemy);
    // enemyManager->spawnEnemyAt(EnemyType::spiny, posEnemy);
    // enemyManager->spawnEnemyAt(EnemyType::lakitu, posEnemy);
    // enemyManager->spawnEnemyAt(EnemyType::cheepcheep, posEnemy);
    // enemyManager->spawnEnemyAt(EnemyType::paratroopa, posEnemy);
    // enemyManager->spawnEnemyAt(EnemyType::hammer, posEnemy);
    // enemyManager->spawnEnemyAt(EnemyType::piranhaplant, posEnemy);
    // enemyManager->spawnEnemyAt(EnemyType::hammerbro, posEnemy);
    // enemyManager->spawnEnemyAt(EnemyType::bowser, posEnemy);
}

void PlayingState::exit()
{
    UnloadTexture(marioTexture);
    UnloadTexture(heartTexture);
    UnloadTexture(coinIcon);
    UnloadTexture(pauseIconTexture);
    enemyAsset::Unload();
}

void PlayingState::update()
{
    // if we press escape, we want to pause the game
    // if (IsKeyPressed(KEY_ESCAPE))
    // {
    //     gsm->pushState(new PauseState(gsm, worldNum, levelNum));
    //     return;
    // }

    pauseButton->update();
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && pauseButton->contains(GetMousePosition()))
    {
        pauseButton->onClick();
        return;
    }

    currentData.playerPosition = player->position;
    currentData.lives = player->lives;
    currentData.coins = player->coins;
    currentData.score = player->score;
    currentData.timeRemaining = hudManager->getTime();

    player->HandleInput();
    if (player->GetForm() == FIRE)
    {
        if (IsKeyPressed(KEY_LEFT_SHIFT) || IsKeyPressed(KEY_RIGHT_SHIFT))
        {
            fireBallManager.ShootFireBall(player->GetPosition(), player->GetDirection());
        }
    }

    player->Update(*levelManager->getCurrentLevel());

    // Handle Mario's death

    // LEVEL
    levelManager->Update(*player, itemManager);
    levelManager->SpawnEnemy( player->GetPosition().x + float(GetScreenWidth() / 2) , *enemyManager); // May access nullptr and cause error 

    playerAdapter->update();
    hudManager->updateTime();

    // for (auto it = entities.begin(); it != entities.end();)
    // {
    //     (*it)->Update(*level); // Update each entity
    //     if (CheckCollisionRecs(player->GetBounds(), (*it)->GetBounds()))
    //     {
    //         if (auto coin = dynamic_cast<Coin *>((*it).get()))
    //         {
    //             if (!coin->isCollected)
    //             {
    //                 coin->isCollected = true;
    //                 player->coins++;
    //                 player->score += 100;
    //             }
    //         }
    //     }

    //     if (auto coin = dynamic_cast<Coin *>((*it).get()); coin && coin->isCollected)
    //     {
    //         it = entities.erase(it);
    //     }
    //     else
    //     {
    //         ++it;
    //     }
    // }

    fireBallManager.Update(*levelManager->getCurrentLevel());

    itemManager.UpdateItems(*levelManager->getCurrentLevel(), *player);

    // Enemy
    enemyManager->update();

    // Check for game over
    // Time and lives
    if (hudManager->getTime() <= 0 || player->GetPosition().y > HEIGHT_BOUNDARY)
    {
        player->Die();
        gsm->getContext().lives = player->lives;

        if (player->lives <= 0)
        {
            gsm->changeState(new GameOverState(gsm));
        }
        else
        {
            gsm->changeState(new GetReadyState(gsm, worldNum, levelNum, GetReadyReason::RESPAWN));
        }
        return;
    }
}

void PlayingState::draw()
{
    // Camera2D camera = {0};
    // camera.target = {player->position.x + player->rect.width / 2, float(GetScreenHeight() / 2)};
    // camera.offset = {float(GetScreenWidth() / 2), float(GetScreenHeight() / 2)};
    Camera2D camera = {0};
    if (player->GetBounds().x > cameraPos.x)
    {
        cameraPos.x = player->GetBounds().x;
    }
    camera.target = cameraPos;
    camera.offset = Vector2{float(GetScreenWidth() / 2), 0};
    camera.zoom = 1.0f;

    BeginMode2D(camera);
    levelManager->Draw();
    player->Draw();
    enemyManager->draw();

    fireBallManager.Draw();
    itemManager.DrawItems();

    EndMode2D();

    hudManager->draw();
    pauseButton->draw();
}

void PlayingState::saveGameData()
{
    currentData.playerPosition = player->position;
    currentData.lives = player->lives;
    currentData.coins = player->coins;
    currentData.score = player->score;
    currentData.timeRemaining = hudManager->getTime();

    SaveManager::saveGame(currentData, "savegame.dat");
}