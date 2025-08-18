#include "DGameState/PlayingState.h"
#include "DGameState/GameOverState.h"
#include "DGameState/WinState.h"
#include "DGameState/GetReadyState.h"
#include "DGameState/PauseState.h"

PlayingState::PlayingState(GameStateManager *manager, int world, int level) : gsm(manager), worldNum(world), levelNum(level) {}

void PlayingState::enter()
{
    heartTexture = LoadTexture("assets/mario.png");
    coinIcon = LoadTexture("assets/mario.png");
    marioTexture = LoadTexture("assets/mario.png");

    player = std::make_unique<Mario>(Vector2{float(GetScreenWidth() / 2 - 16), 0.0f});

    level = std::make_unique<Level>("./assets/Levels/world_1.1.txt");

    // Items
    // entities.push_back(std::make_unique<Coin>(Vector2{200, 100}));
    // entities.push_back(std::make_unique<Mushroom>(Vector2{300, 100}));
    itemManager.AddItem(std::make_unique<Coin>(Vector2{200, 100}));
    itemManager.AddItem(std::make_unique<Mushroom>(Vector2{300, 100}));
    itemManager.AddItem(std::make_unique<FireFlower>(Vector2{400, 100}));

    player->lives = gsm->getContext().lives;
    player->coins = 0;
    player->score = 0;

    cameraPos = Vector2{0.0f, 0.0f};

    hudManager = std::make_unique<HUDManager>(heartTexture, coinIcon);
    playerAdapter = std::make_unique<PlayerAdapter>(player.get());

    playerAdapter->attach(hudManager.get());
    playerAdapter->init();

    hudManager->resetTime(400);
    hudManager->updateWorld(worldNum, levelNum);
    playerAdapter->update();
}

void PlayingState::exit()
{
    UnloadTexture(marioTexture);
    UnloadTexture(heartTexture);
    UnloadTexture(coinIcon);
}

void PlayingState::update()
{
    // if we press escape, we want to pause the game
    if (IsKeyPressed(KEY_ESCAPE))
    {
        gsm->pushState(new PauseState(gsm, worldNum, levelNum));
        return;
    }

    player->HandleInput();
    if (player->GetForm() == FIRE)
    {
        if (IsKeyPressed(KEY_LEFT_SHIFT) || IsKeyPressed(KEY_RIGHT_SHIFT))
        {
            fireBallManager.ShootFireBall(player->GetPosition(), player->GetDirection());
        }
    }
    player->Update(*level); // Handling player collision and movement

    level->update(*player);

    playerAdapter->update();
    hudManager->updateTime();

    fireBallManager.Update(*level);
    itemManager.UpdateItems(*level, *player); // Update all entities

    // Check for game over
    // Time and lives
    if (hudManager->getTime() <= 0)
    {
        player->lives--;
        gsm->getContext().lives = player->lives;

        if (player->lives <= 0)
        {
            gsm->changeState(new GameOverState(gsm));
        }
        else
        {
            gsm->changeState(new GetReadyState(gsm, worldNum, levelNum));
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
    level->render();
    player->Draw();

    fireBallManager.Draw();
    itemManager.DrawItems();

    EndMode2D();

    hudManager->draw();
}