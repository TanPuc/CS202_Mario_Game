#include "Enemy/enemyStateCondition.h"
#include "Level.h"
#include "Tile.h"

#include "raylib.h"

ConditionTimer::ConditionTimer(float timer) : threshold(timer) {}
bool ConditionTimer::evaluate(Enemy &e)
{
    timer += GetFrameTime();

    if (timer >= threshold)
    {
        timer = 0;
        return true;
    }
    return false;
}

ConditionShell::ConditionShell(const vector<Enemy *> &shells) : m_shells(shells) {}
bool ConditionShell::evaluate(Enemy &e)
{
    for (auto &s : m_shells)
    {
        if (s == &e)
            continue;
        return (CheckCollisionRecs(s->getHitBox(), e.getHurtBox()));
    }
    return false;
}

ConditionFireBall::ConditionFireBall(const vector<shared_ptr<FireBall>> &balls) : m_fireballs(balls) {}
ConditionFireBall::ConditionFireBall(const vector<shared_ptr<FireBall>> &balls, int amount) : m_fireballs(balls), m_amount(amount) {}
bool ConditionFireBall::evaluate(Enemy &e)
{
    if (isImmune)
    {
        timer += GetFrameTime();
        if (timer >= immuneDuration)
        {
            timer = 0;
            isImmune = false;
        }
    }
    else
    {
        for (auto &s : m_fireballs)
        {
            if (CheckCollisionRecs(e.getHurtBox(), s->GetBounds()))
            {
                isImmune = true;
                m_counter++;
                if (m_counter >= m_amount)
                    return true;
            }
        }
    }

    return false;
}

ConditionStomped::ConditionStomped(const Character &player) : m_player(player) {}
bool ConditionStomped::evaluate(Enemy &e)
{
    if (CheckCollisionRecs(e.getHurtBox(), m_player.GetBounds()))
    {
        return true;
    }
    return false;
}

ConditionKicked::ConditionKicked(const Character &mario) : m_player(mario) {}
bool ConditionKicked::evaluate(Enemy &e)
{
    if (CheckCollisionRecs(e.getHitBox(), m_player.GetBounds()))
    {
        return true;
    }
    return false;
}

ConditionGrounded::ConditionGrounded(Level &level) : m_level(level) {}
bool ConditionGrounded::evaluate(Enemy &e)
{
    vector<pair<array<int, 2>, float>> unresolvedtile;
    Vector2 cp, cn;
    float et = GetFrameTime();
    Vector2 nextPos = e.GetPosition() + e.getVelocity() * et;
    int minX = std::floor(std::min(e.position.x, nextPos.x) / (TILE_SIZE * SCALE));
    int minY = std::floor(std::min(e.position.y, nextPos.y) / (TILE_SIZE * SCALE));
    int maxX = std::floor(std::max(e.position.x + e.getHurtBox().width, nextPos.x + e.getHurtBox().width) / (TILE_SIZE * SCALE));
    int maxY = std::floor(std::max(e.position.y + e.getHurtBox().height, nextPos.y + e.getHurtBox().height) / (TILE_SIZE * SCALE));
    float t;

    for (int y = minY; y <= maxY; y++)
    {
        for (int x = minX; x <= maxX; x++)
        {
            if (x < 0 || y < 0 || x >= m_level.getGridWidth() || y >= m_level.getGridHeight())
                continue;
            if (m_level.getTileInstance(y, x))
            {
                if (aabb::CheckCollisionStaticRectDynamicRect(e.getHurtBox(), e.getVelocity(),
                                                              m_level.getTileInstance(y, x)->bbox, cp, cn, t, et))
                {
                    return true;
                }
            }
        }
    }

    return false;
}
