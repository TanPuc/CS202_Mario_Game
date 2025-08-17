#include "Enemy/enemyStateCondition.h"

#include "raylib.h"

ConditionTimer::ConditionTimer(float timer) :
	threshold(timer) {}
bool ConditionTimer::evaluate(Enemy& e)
{
	timer += GetFrameTime();

	if (timer >= threshold)
	{
		timer = 0;
		return true;
	}
	return false;
}

ConditionShell::ConditionShell(const vector<Enemy*>& shells) :
	m_shells(shells) {}
bool ConditionShell::evaluate(Enemy& e)
{
	for (auto& s : m_shells)
	{
        if (s == &e) continue;
        return (CheckCollisionRecs(s->getHitBox(), e.getHurtBox()));
	}
	return false;
}


ConditionFireBall::ConditionFireBall(const vector<FireBall*>& balls) :
	m_fireballs(balls) {}
bool ConditionFireBall::evaluate(Enemy& e)
{
	for (auto& s : m_fireballs)
	{
        if (CheckCollisionRecs(e.getHurtBox(), s->GetBounds()))
        {
            return true;
        }
	}
	return false;
}

ConditionStomped::ConditionStomped(const Mario& player) :
	m_player(player) {}
bool ConditionStomped::evaluate(Enemy& e)
{
    if (CheckCollisionRecs(e.getHurtBox(), m_player.GetBounds()))
    {
        return true;
    }
	return false;
}

ConditionKicked::ConditionKicked(const Mario& mario):
    m_player(mario) {}
bool ConditionKicked::evaluate(Enemy& e)
{
    if (CheckCollisionRecs(e.getHitBox(), m_player.GetBounds()))
    {
        return true;
    }
    return false;
}

ConditionGrounded::ConditionGrounded(const Level& level) :
	m_level(level) {}
bool ConditionGrounded::evaluate(Enemy& e)
{
    vector<pair<array<int, 2>, float>> unresolvedtile;
    Vector2 cp, cn;
    float et = GetFrameTime();
    Vector2 nextPos = e.GetPosition() + e.getVelocity() * et;
    int minX = std::floor(std::min(e.position.x, nextPos.x) / 64.0f);
    int minY = std::floor(std::min(e.position.y, nextPos.y) / 64.0f);
    int maxX = std::floor(std::max(e.position.x + e.getHurtBox().width, nextPos.x + e.getHurtBox().width) / 64.0f);
    int maxY = std::floor(std::max(e.position.y + e.getHurtBox().height, nextPos.y + e.getHurtBox().height) / 64.0f);
    float t;

    for (int y = minY; y <= maxY; y++) {
        for (int x = minX; x <= maxX; x++) {
            if (x < 0 || y < 0 || x >= GRID_WIDTH || y >= GRID_HEIGHT) continue;
            if (m_level.tileManager.tileInstancesGrid[y][x]) {
                if (aabb::CheckCollisionStaticRectDynamicRect(e.getHurtBox(), e.getVelocity(),
                    m_level.tileManager.tileInstancesGrid[y][x]->getBBox(), cp, cn, t, et)) {
                    array<int, 2> temp = { y , x };
                    unresolvedtile.push_back({ temp , t });
                }
            }
        }
    }

    bool result = false;

    std::sort(unresolvedtile.begin(), unresolvedtile.end(), compare);
    for (auto j : unresolvedtile) {
        Vector2 cp, cn;
        float ct = 0.0f;
        if (aabb::CheckCollisionStaticRectDynamicRect(e.getHurtBox(), e.getVelocity(),
            m_level.tileManager.tileInstancesGrid[j.first[0]][j.first[1]]->getBBox(), cp, cn, ct, GetFrameTime())) {
            e.setVelocityX(e.getVelocity().x + cn.x * abs(e.getVelocity().x) * (1 - ct));
            e.setVelocityY(e.getVelocity().y + cn.y * abs(e.getVelocity().y) * (1 - ct));
            result = true;
        }
    }
    unresolvedtile.clear();

    return result;
}

