#include "Tile.h"
#include "Character.h"
#include "BrickPieces.h"
#include "DGameState/PlayingState.h"
#include "ItemManager.h"

float Q_rsqrt(float number)
{
    long i;
    float x2, y;
    const float threehalfs = 1.5f;

    x2 = number * 0.5f;
    y = number;
    i = *(long *)&y;
    i = 0x5f3759df - (i >> 1);
    y = *(float *)&i;
    y = y * (threehalfs - (x2 * y * y));
    return y;
}

bool compare(const std::pair<std::array<int, 2>, float> &a, const std::pair<std::array<int, 2>, float> &b)
{
    return a.second < b.second;
}

TileInstance::TileInstance(Vector2 pos, std::shared_ptr<Tile> tile)
    : pos(pos), tile(tile), bbox(Rectangle{pos.x, pos.y, TILE_SIZE * SCALE, TILE_SIZE * SCALE}) {}

void BrickInstance::handleAnimation()
{
    switch (state)
    {
    case STATE_INTERACTED:
    {
        if (!q_b_a.is_update(pos.y))
        {
            state = STATE_NORMAL;
        }
        dest.y = pos.y;
        bbox.y = pos.y;
    }
    break;
    default:
        break;
    }
}

void BrickInstance::handleBreaking(Character &player)
{
    Rectangle playerBBox = player.rect;
    if (CheckCollisionRecs(playerBBox, hbox))
    {
        switch (state)
        {
        case STATE_NORMAL:
        {
            if (player.GetForm() == BIG || player.GetForm() == FIRE || player.GetForm() == SUPER)
            {
                state = STATE_BROKEN;
            }
            else
            {
                state = STATE_INTERACTED;
                q_b_a.iniVelY();
            }
        }
        break;
        default:
            break;
        }
    }
}

BrickInstance::BrickInstance(Vector2 pos, std::shared_ptr<Tile> brick)
    : TileInstance(pos, brick),
      hbox(Rectangle{
          pos.x + (TILE_SIZE * SCALE / 2) - (HITBOX_WIDTH / 2),
          pos.y + (TILE_SIZE * SCALE),
          HITBOX_WIDTH,
          HITBOX_HEIGHT}),
      dest{pos.x, pos.y, TILE_SIZE * SCALE, TILE_SIZE * SCALE}, q_b_a(Q_B_A(pos.y))
{
    originalBBox = bbox;
}

void BrickInstance::update(Character &player, ItemManager &itemManager, PlayingState *ps)
{
    handleBreaking(player);
    handleAnimation();
}

void BrickInstance::render()
{
    DrawTexturePro(tile->getTexture(), normal, dest, Vector2{0, 0}, 0.0f, WHITE);
    // DrawRectangleLinesEx(hbox, 1.0f, RED); // Draw hitbox
}

QuestionInstance::QuestionInstance(Vector2 pos, std::shared_ptr<Tile> question)
    : TileInstance(pos, question),
      hbox(Rectangle{
          pos.x + (TILE_SIZE * SCALE / 2) - (HITBOX_WIDTH / 2),
          pos.y + (TILE_SIZE * SCALE),
          HITBOX_WIDTH,
          HITBOX_HEIGHT}),
      dest{pos.x, pos.y, TILE_SIZE * SCALE, TILE_SIZE * SCALE}, q_b_a(Q_B_A(pos.y))
{
    originalBBox = bbox;
}

void QuestionInstance::handleAnimation()
{
    switch (state)
    {
    case STATE_NORMAL:
    {
        frameCounter++;
        if (normal.x == 0)
        {
            if (frameCounter >= frameSpeed2)
            {
                frameCounter = 0;
                normal.x += 16;
            }
        }
        else
        {
            if (frameCounter >= frameSpeed)
            {
                frameCounter = 0;
                normal.x += 16;
                if (normal.x >= 48)
                    normal.x = 0;
            }
        }
    }
    break;
    case STATE_INTERACTED:
    {
        normal.x = 48;
        if (!q_b_a.is_update(pos.y))
        {
            state = STATE_ACTIVATED;
        }
        dest.y = pos.y;
        bbox.y = pos.y;
    }
    break;
    case STATE_ACTIVATED:
    {
        normal.x = 48;
    }
    break;
    default:
        break;
    }
}

void QuestionInstance::handleActivation(Character &player, ItemManager &itemManager, PlayingState *ps)
{
    Rectangle playerBBox = player.rect;
    if (CheckCollisionRecs(playerBBox, hbox))
    {
        switch (state)
        {
        case STATE_NORMAL:
        {
            state = STATE_INTERACTED;
            q_b_a.iniVelY();

            player.score += 100;
            SoundManager::getInstance().playSound(SoundEffect::COIN);
            if (ps)
            {
                ps->addFloatingScore(this->pos, "100");
            }

            if (hasMushroom)
            {
                itemManager.SpawnMushroom(Vector2{pos.x, pos.y - TILE_SIZE * SCALE}, Vector2{60.0f, 0.0f}, RIGHT);
            }
            else if (hasFlower)
            {
                itemManager.SpawnFireFlower(Vector2{pos.x, pos.y - TILE_SIZE * SCALE}, Vector2{0.0f, 0.0f}, RIGHT);
            }
            else
            {
                itemManager.SpawnCoin(Vector2{pos.x + TILE_SIZE * SCALE / 4, pos.y - TILE_SIZE * SCALE}, Vector2{0.0f, -100.0f});
            }
        }
        break;
        }
    }
}

void QuestionInstance::update(Character &player, ItemManager &itemManager, PlayingState *ps)
{
    handleActivation(player, itemManager, ps);
    handleAnimation();
}

void QuestionInstance::render()
{
    DrawTexturePro(tile->getTexture(), normal, dest, Vector2{0, 0}, 0.0f, WHITE);
    // DrawRectangleLinesEx(hbox, 1.0f, RED); // Draw hitbox
}

BackgroundInstance::BackgroundInstance(Vector2 pos, std::shared_ptr<Tile> background) : TileInstance(pos, background)
{
    bbox = Rectangle{0, 0, 0, 0};
}

void BackgroundInstance::render()
{
    DrawTextureEx(tile->getTexture(), pos, 0.0f, SCALE, WHITE);
}

void PipeInstance1::render() { DrawTextureEx(tile->getTexture(), pos, 0.0f, SCALE, WHITE); }
void PipeInstance2::render() { DrawTextureEx(tile->getTexture(), pos, 0.0f, SCALE, WHITE); }
void PipeInstance3::render() { DrawTextureEx(tile->getTexture(), pos, 0.0f, SCALE, WHITE); }

HardblockInstance::HardblockInstance(Vector2 pos, std::shared_ptr<Tile> hardblock)
    : TileInstance(pos, hardblock) {}

void HardblockInstance::render()
{
    DrawTextureEx(tile->getTexture(), pos, 0.0f, SCALE, WHITE);
}

GoalpoleInstance::GoalpoleInstance(Vector2 pos, std::shared_ptr<Tile> goalpole)
    : TileInstance(pos, goalpole), hbox(Rectangle{pos.x, pos.y, TILE_SIZE * SCALE, 11 * TILE_SIZE * SCALE}), goalFlag({pos.x - TILE_SIZE * SCALE / 2, pos.y + 1.0625f * TILE_SIZE * SCALE})
{
    bbox = Rectangle{0, 0, 0, 0};
}

void GoalpoleInstance::update(Character &player, ItemManager &itemManager, PlayingState *ps)
{
    if (state == STATE_ACTIVATED && goalFlag.IsFinishedSliding())
    {
        isLevelFinished = true;
    }

    if (!isLevelFinished && CheckCollisionRecs(player.GetBounds(), hbox))
    {
        state = STATE_ACTIVATED;
        Vector2 playerPos = player.GetPosition();
        Vector2 playerGridCoords = {playerPos.x / (TILE_SIZE * SCALE), playerPos.y / (TILE_SIZE * SCALE)};
        player.position.x = ceil(playerGridCoords.x) * (TILE_SIZE * SCALE);
        player.rect.x = player.position.x;
        player.playWinAnimation = true;
        goalFlag.iniVelY();
    }
    goalFlag.Update(state);
}

void GoalpoleInstance::render()
{
    DrawTextureEx(tile->getTexture(), pos, 0.0f, SCALE, WHITE);
    // DrawRectangleLinesEx(hbox, 1.0f, RED); // Draw hitbox
    goalFlag.Draw();
}

PlatformInstance::PlatformInstance(Vector2 pos_1, Vector2 pos_2, std::shared_ptr<Tile> platform, int direction) : TileInstance(pos_1, platform)
{
    if (direction == 0) // Up and down
    {
        topPos = std::make_shared<Vector2>(pos_1);
        bottomPos = std::make_shared<Vector2>(pos_2);
        bbox = Rectangle{topPos->x, topPos->y, platform->getTexture().width * SCALE, platform->getTexture().height * SCALE};
    }
    else if (direction == 1) // Left and right
    {
        leftPos = std::make_shared<Vector2>(pos_1);
        rightPos = std::make_shared<Vector2>(pos_2);
        bbox = Rectangle{leftPos->x, leftPos->y, platform->getTexture().width * SCALE, platform->getTexture().height * SCALE};
    }
}

void LavaSurfaceInstance::update(Character &player, ItemManager &itemManager, PlayingState *ps)
{
    if (CheckCollisionRecs(player.GetBounds(), hbox) && !player.isDead)
    {
        player.Die();
        // GAME_STATE = LOSE
        // PLAYER_STATE = DEAD
    }
}

void LavaSurfaceInstance::render()
{
    DrawTextureEx(tile->getTexture(), pos, 0.0f, SCALE, WHITE);
    // DrawRectangleLinesEx(hbox, 2.0f, RED); // Draw hitbox
}

void HiddenBlockInstance::render()
{
    if (state == STATE_ACTIVATED || state == STATE_INTERACTED)
    {
        DrawTextureEx(tile->getTexture(), pos, 0.0f, SCALE, WHITE);
    }
    // DrawRectangleLinesEx(bbox, 2.0f, RED); // Draw hitbox
}

void HiddenBlockInstance::handleAnimation()
{
    switch (state)
    {
    case STATE_INTERACTED:
    {
        if (!q_b_a.is_update(pos.y))
        {
            state = STATE_ACTIVATED;
        }
    }
    break;
    default:
        break;
    }
}

void HiddenBlockInstance::handleActivation()
{
    switch (state)
    {
    case STATE_NORMAL:
    {
        state = STATE_INTERACTED;
        q_b_a.iniVelY();
        spawnCoin = true;
    }
    break;
    default:
        break;
    }
}

void HiddenBlockInstance::handleHiddenBBox(Character &player)
{
    switch (state)
    {
    case STATE_NORMAL:
    {
        // Only show the bbox when the player is below the block
        if (player.GetPosition().y > original_bbox_y + bbox.height)
        {
            bbox.y = original_bbox_y;
        }
        else
        {
            bbox.y = 0;
        }
    };
    default:
        break;
    }
}

void HiddenBlockInstance::update(Character &player, ItemManager &itemManager, PlayingState *ps)
{
    // handleActivation(player, itemManager);
    handleHiddenBBox(player);
    handleAnimation();

    if (spawnCoin)
    {
        // itemManager.SpawnCoin();
        spawnCoin = false;
        std::cout << "Coin spawned!" << std::endl;
    }
}

void CoinInstance::update(Character &player, ItemManager &itemManager, PlayingState *ps)
{
    if (!CoinInitialized)
    {
        itemManager.SpawnCoinBlock(pos);
        std::cout << "Coin spawned!" << std::endl;
        CoinInitialized = true;
    }
}