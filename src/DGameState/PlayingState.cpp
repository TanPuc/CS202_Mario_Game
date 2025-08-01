#include "DGameState/PlayingState.h"

PlayingState::PlayingState(GameStateManager* manager) : gsm(manager) {}

void PlayingState::enter() 
{
    heartTexture = LoadTexture("assets/mario_head_icon.png");
    coinIcon = LoadTexture("assets/coin_icon.png");
    marioTexture = LoadTexture("assets/mario.png");
    coinTexture = LoadTexture("assets/coin.png");

    player = std::make_unique<Mario>(marioTexture, Vector2{100, 0});
    player->lives = 3; player->coins = 0; player->score = 0;

    level = std::make_unique<Level>();
    level->LoadFromFile("assets/level1.map");

    hudManager = std::make_unique<HUDManager>(heartTexture, coinIcon);
    playerAdapter = std::make_unique<PlayerAdapter>(player.get());

    playerAdapter->attach(hudManager.get());
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