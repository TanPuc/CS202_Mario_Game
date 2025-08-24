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

    level = std::make_unique<Level>("./assets/Levels/world_1.1.txt");

    player = std::make_unique<Mario>(
        currentData.playerPosition,
        [this]()
        {
            gsm->getContext().lives = player->lives;
            if (player->lives <= 0)
            {
                pendingGameOver = true;
            }
            else
            {
                pendingRespawn = true;
            }
        });
    player->lives = currentData.lives;
    player->coins = currentData.coins;
    player->score = currentData.score;

    worldNum = currentData.worldNum;
    levelNum = currentData.levelNum;

    // Items
    // entities.push_back(std::make_unique<Coin>(Vector2{200, 100}));
    // entities.push_back(std::make_unique<Mushroom>(Vector2{300, 100}));
    itemManager.AddItem(std::make_unique<Coin>(Vector2{200, 100}));
    itemManager.AddItem(std::make_unique<Mushroom>(Vector2{300, 100}));
    itemManager.AddItem(std::make_unique<FireFlower>(Vector2{400, 100}));

    player->lives = gsm->getContext().lives;
    player->coins = 0;
    player->score = 0;

    cameraPos = Vector2{GetScreenWidth() / 2.0f, 0.0f};
    camera.setTarget(cameraPos);

    hudManager = std::make_unique<HUDManager>(heartTexture, coinIcon);
    playerAdapter = std::make_unique<PlayerAdapter>(player.get());

    playerAdapter->attach(hudManager.get());
    playerAdapter->init();

    hudManager->resetTime(currentData.timeRemaining);
    hudManager->updateWorld(worldNum, levelNum);
    playerAdapter->update();
}

void PlayingState::exit()
{
    UnloadTexture(marioTexture);
    UnloadTexture(heartTexture);
    UnloadTexture(coinIcon);
    UnloadTexture(pauseIconTexture);
}

void PlayingState::update()
{
    // if we press escape, we want to pause the game
    if (IsKeyPressed(KEY_ESCAPE))
    {
        gsm->pushState(new PauseState(gsm, worldNum, levelNum));
        return;
    }

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
    player->Update(*level); // Handling player collision and movement

    if (player->GetForm() == FIRE)
    {
        if ((IsKeyPressed(KEY_LEFT_SHIFT) || IsKeyPressed(KEY_RIGHT_SHIFT)) && !player->isThrowing)
        {
            // player->ShootFireBall();
            std::cout << "Switched animation into throwing\n";
            player->ShootFireBall();
            Vector2 playerHandPos = player->GetPosition();
            playerHandPos.x += player->GetBounds().width;
            playerHandPos.y += (player->GetBounds().height / 2);
            fireBallManager.ShootFireBall(playerHandPos, player->GetDirection());
        }
    }

    Vector2 playerPos = player->GetPosition();

    if (IsKeyPressed(KEY_F))
    {
        // Vector2 playerGridCoords = {playerPos.x / (TILE_SIZE * SCALE), playerPos.y / (TILE_SIZE * SCALE)};
        // player->Slide(playerGridCoords);
        player->ChangeForm(SMALL);
    }

    if (player->GetBounds().x > cameraPos.x)
    {
        cameraPos.x = player->GetBounds().x;
    }

    level->update(*player);

    playerAdapter->update();
    hudManager->updateTime();

    fireBallManager.Update(*level);
    itemManager.UpdateItems(*level, *player); // Update all entities

    // Check for player horizontal bounding
    if (playerPos.x < cameraPos.x - (camera.bounds.width / 2) || playerPos.x + player->GetBounds().width > cameraPos.x + camera.bounds.width)
    {
        player->SetPosition({cameraPos.x - (camera.bounds.width / 2), playerPos.y});
        player->velocity.x = 0; // Stop horizontal movement
    }

    // Handle Mario's death
    if (playerPos.y >= cameraPos.y + camera.bounds.height && pendingRespawn == false)
    {
        player->Die();
    }

    // Check for game over
    // Time and lives
    if (hudManager->getTime() <= 0)
    {
        player->Die();
    }

    if (pendingGameOver)
    {
        gsm->changeState(new GameOverState(gsm));
        return;
    }
    if (pendingRespawn)
    {
        gsm->changeState(new GetReadyState(gsm, worldNum, levelNum, GetReadyReason::RESPAWN));
        return;
    }
}

void PlayingState::draw()
{
    camera.setTarget(cameraPos);

    BeginMode2D(camera.camera);
    level->render();
    player->Draw();

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