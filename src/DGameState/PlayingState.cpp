#include "DGameState/PlayingState.h"
#include "DGameState/GameOverState.h"
#include "DGameState/WinState.h"
#include "DGameState/GetReadyState.h"

PlayingState::PlayingState(GameStateManager* manager, int world, int level) : gsm(manager), worldNum(world), levelNum(level) {}

void PlayingState::enter() 
{
    heartTexture = LoadTexture("assets/mario.png");
    coinIcon = LoadTexture("assets/mario.png");
    marioTexture = LoadTexture("assets/mario.png");
    coinTexture = LoadTexture("assets/mario.png");

    player = std::make_unique<Mario>(marioTexture, Vector2{100, 0});
    player->lives = 3; player->coins = 0; player->score = 0;

    level = std::make_unique<Level>();
    level->LoadFromFile("assets/level1.map");

    hudManager = std::make_unique<HUDManager>(heartTexture, coinIcon);
    playerAdapter = std::make_unique<PlayerAdapter>(player.get());

    playerAdapter->attach(hudManager.get());
    
    hudManager->resetTime(400);
    hudManager->updateWorld(worldNum, levelNum);

    playerAdapter->update();

    entities.push_back(std::make_unique<Coin>(coinTexture, Vector2{400, 400}));
}

void PlayingState::exit() 
{
    UnloadTexture(marioTexture);
    UnloadTexture(coinTexture);
    UnloadTexture(heartTexture);
    UnloadTexture(coinIcon);
}

void PlayingState::update() 
{
    player->Update();
    player->CheckCollision(*level.get());
    playerAdapter->update();
    hudManager->updateTime();

    for (auto it = entities.begin(); it != entities.end(); ) 
    {
        if (CheckCollisionRecs(player->GetBounds(), (*it)->GetBounds())) 
        {
            if (auto coin = dynamic_cast<Coin*>((*it).get())) 
            {
                if (!coin->isCollected) 
                {
                    coin->isCollected = true;
                    player->coins++;
                    player->score += 100;
                }
            }
        }
        
        if (auto coin = dynamic_cast<Coin*>((*it).get()); coin && coin->isCollected) 
        {
            it = entities.erase(it);
        } else 
        {
            ++it;
        }
    }
}

void PlayingState::draw() 
{
    Camera2D camera = {0};
    camera.target = {player->position.x + player->rect.width / 2, float(GetScreenHeight() / 2)};
    camera.offset = {float(GetScreenWidth() / 2), float(GetScreenHeight() / 2)};
    camera.zoom = 1.0f;

    BeginMode2D(camera);
    level->Draw(camera);
    for (const auto& entity : entities) 
    {
        entity->Draw();
    }
    player->Draw();
    EndMode2D();

    hudManager->draw();
}