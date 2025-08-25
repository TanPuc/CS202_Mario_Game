#include "DGameState/PlayingState.h"
#include "DGameState/GameOverState.h"
#include "DGameState/WinState.h"
#include "DGameState/GetReadyState.h"
#include "DGameState/PauseState.h"
#include "DCore/SoundManager.h"
#include "DCore/SaveManager.h"
#include "ItemManager.h"

PlayingState::PlayingState(GameStateManager *manager, const GameData &initialData) : gsm(manager), currentData(initialData)
{
    itemManager = std::make_unique<ItemManager>();
}

void PlayingState::addFloatingScore(Vector2 position, const std::string &text)
{
    floatingScores.emplace_back(position, text);
}

void PlayingState::setGoalpole(std::shared_ptr<GoalpoleInstance> gp)
{
    goalpole = gp;
}

void PlayingState::enter()
{
    SoundManager::getInstance().stopMusic();
    SoundManager::getInstance().playMusic(MusicTrack::MAIN_THEME);
    std::string headIcon;
    if (gsm->getContext().selectedCharacter == "luigi")
    {
        headIcon = "assets/luigiHead.png";
    }
    else
    {
        headIcon = "assets/marioHead.png";
    }
    heartTexture = LoadTexture(headIcon.c_str());
    coinIcon = LoadTexture("assets/coinHUD.png");
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

    this->worldNum = currentData.worldNum;
    this->levelNum = currentData.levelNum;
    // level = std::make_unique<Level>("./assets/Levels/world_1.1.txt", this);
    std::string mapFilePath = "./assets/Levels/world_" + std::to_string(this->worldNum) + "." + std::to_string(this->levelNum) + ".txt";

    std::cout << "Loading map from: " << mapFilePath << std::endl;
    level = std::make_unique<Level>(mapFilePath.c_str(), this);

    CHARACTER charToCreate = MARIO;
    if (gsm->getContext().selectedCharacter == "luigi")
    {
        charToCreate = LUIGI;
    }
    

    player = std::make_unique<Character>(
        charToCreate,
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
    player->form = currentData.playerForm;
    player->sprite->SwitchForm(player->form);
    if (player->form != SMALL)
    {
        player->rect.height = CHARACTER_HEIGHT * 2.0f;
    }

    worldNum = currentData.worldNum;
    levelNum = currentData.levelNum;

    // TILE
    for (int i = 0; i < GRID_HEIGHT; i++)
    {
        for (int j = 0; j < GRID_WIDTH; j++)
        {
            if (level->tileInstancesGrid[i][j])
            {
                level->tileInstancesGrid[i][j]->state = currentData.tileStates[i][j];
            }
        }
    }

    // Items
    // entities.push_back(std::make_unique<Coin>(Vector2{200, 100}));
    // entities.push_back(std::make_unique<Mushroom>(Vector2{300, 100}));
    itemManager->AddItem(std::make_unique<Coin>(Vector2{200, 100}));
    itemManager->AddItem(std::make_unique<Mushroom>(Vector2{300, 100}));
    itemManager->AddItem(std::make_unique<FireFlower>(Vector2{400, 100}));

    // player->lives = gsm->getContext().lives;
    // player->coins = 0;
    // player->score = 0;

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

void PlayingState::updatePlaying()
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

    player->Update(*level); // Handling player collision and movement
    Vector2 playerPos = player->GetPosition();

    if (player->GetBounds().x > cameraPos.x)
    {
        cameraPos.x = player->GetBounds().x;
    }

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

    if (IsKeyPressed(KEY_F))
    {
        Vector2 playerGridCoords = {playerPos.x / (TILE_SIZE * SCALE), playerPos.y / (TILE_SIZE * SCALE)};
        player->Slide(playerGridCoords);
        // player->ChangeForm(SMALL);
    }

    if (player->GetBounds().x > cameraPos.x)
    {
        cameraPos.x = player->GetBounds().x;
    }

    level->update(*player, this);

    // for (int i=0; i<GRID_HEIGHT; i++)
    // {
    //     for (int j=0; j<GRID_WIDTH; j++)
    //     {
    //         if (auto goalpole= std::dynamic_pointer_cast<GoalpoleInstance>(level->tileInstancesGrid[i][j]))
    //         {
    //             if (goalpole->isLevelFinished)
    //             {
    //                 // Save checkpoint
    //                 gsm->getContext().checkpointWorld = worldNum;
    //                 gsm->getContext().checkpointLevel = levelNum;

    //                 // Transition to GetReadyState
    //                 saveGameData();
    //                 gsm->changeState(new GetReadyState(gsm, worldNum, levelNum, GetReadyReason::NEW_GAME));
    //                 return;
    //             }
    //         }
    //     }
    // }

    if (auto gp_ptr = goalpole.lock())
    {
        if (gp_ptr->isLevelFinished)
        {
            std::cout << "Level Clear! Starting score tally." << std::endl;
            SoundManager::getInstance().stopMusic();
            timeToConvert = hudManager->getTime();
            subState = PlaySubState::SCORE_TALLY;
            return; // Dừng updatePlaying()
            // std::cout << "Level Finished! Updating checkpoint." << std::endl;
            // GameData dataAtCheckPoint = this->currentData;
            // dataAtCheckPoint.playerForm = player->form;
            // int nextLevel = dataAtCheckPoint.levelNum + 1;
            // int nextWorld = dataAtCheckPoint.worldNum;

            // dataAtCheckPoint.worldNum = nextWorld;
            // dataAtCheckPoint.levelNum = nextLevel;

            // dataAtCheckPoint.playerPosition = { 100.0f, 100.0f };
            // dataAtCheckPoint.timeRemaining = 400;

            // gsm->getContext().checkpointData = dataAtCheckPoint;
            // gsm->getContext().checkpointIsSet = true;

            // // gsm->getContext().checkpointWorld = nextWorld;
            // // gsm->getContext().checkpointLevel = nextLevel;

            // // GameData nextLevelData;
            // // nextLevelData.worldNum = nextWorld;
            // // nextLevelData.levelNum = nextLevel;
            // // nextLevelData.lives = player->lives;
            // // nextLevelData.coins = player->coins;
            // // nextLevelData.score = player->score;
            // // nextLevelData.playerForm = player->form;

            // // gsm->getContext().currentScore = player->score;
            // // gsm->getContext().currentCoins = player->coins;
            // gsm->changeState(new GetReadyState(gsm, nextWorld, nextLevel, GetReadyReason::NEW_GAME));

            return;
        }
    }

    playerAdapter->update();
    hudManager->updateTime();

    fireBallManager.Update(*level);
    itemManager->UpdateItems(*level, *player, this); // Update all entities

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

    // Check for game over
    // Time and lives
    if (hudManager->getTime() <= 0)
    {
        player->Die();
        gsm->getContext().lives = player->lives;

        // gsm->getContext().scoreBeforeRespawn = player->score;

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

    // Update floating scores
    for (auto it = floatingScores.begin(); it != floatingScores.end();)
    {
        it->update();
        if (it->isDead())
        {
            it = floatingScores.erase(it); // Remove dead effect
        }
        else
        {
            ++it;
        }
    }
}

void PlayingState::updateLevelClearAnimation()
{
    // Update level clear animation logic here
}

void PlayingState::updateScoreTally()
{
    scoreTallyTimer += GetFrameTime();
    if (scoreTallyTimer >= 0.01f && timeToConvert > 0)
    {
        scoreTallyTimer = 0.0f;

        timeToConvert--;
        player->score += 1000;
        hudManager->timeDisplay.setTime(timeToConvert);
        hudManager->scoreDisplay.updateScore(player->score);

        SoundManager::getInstance().playSound(SoundEffect::COIN);
    }
    if (timeToConvert <= 0)
    {
        if (scoreTallyTimer > 1.0f)
        {
            currentData.score = player->score;

            GameData nextLevelData = this->currentData;
            nextLevelData.playerForm = player->form;

            int nextLevel = nextLevelData.levelNum + 1;
            int nextWorld = nextLevelData.worldNum;

            nextLevelData.worldNum = nextWorld;
            nextLevelData.levelNum = nextLevel;

            nextLevelData.playerPosition = {100.0f, 100.0f};
            nextLevelData.timeRemaining = 400;

            gsm->getContext().checkpointData = nextLevelData;
            gsm->getContext().checkpointIsSet = true;

            gsm->changeState(new GetReadyState(gsm, nextWorld, nextLevel, GetReadyReason::NEW_GAME));
        }
    }
}

void PlayingState::update()
{

    switch (subState)
    {
    case PlaySubState::PLAYING:
        updatePlaying();
        break;
    case PlaySubState::LEVEL_CLEAR_ANIMATION:
        updateLevelClearAnimation();
        break;
    case PlaySubState::SCORE_TALLY:
        updateScoreTally();
        break;
    }
}

void PlayingState::draw()
{
    ClearBackground(SKYBLUE);
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), SKYBLUE);
    camera.setTarget(cameraPos);

    BeginMode2D(camera.camera);
    level->render();
    player->Draw();

    fireBallManager.Draw();
    itemManager->DrawItems();
    for (auto &score : floatingScores)
    {
        score.draw();
    }

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
    currentData.playerForm = player->form;

    for (int i = 0; i < GRID_HEIGHT; i++)
    {
        for (int j = 0; j < GRID_WIDTH; j++)
        {
            if (level->tileInstancesGrid[i][j])
            {
                currentData.tileStates[i][j] = level->tileInstancesGrid[i][j]->state;
            }
        }
    }

    SaveManager::saveGame(currentData, "savegame.dat");
}
