#include "enemyStateCondition.h"

#include "raylib.h"

ConditionTimer::ConditionTimer(float timer) :
	threshold(timer) {}
bool ConditionTimer::evaluate(Enemy& e)
{
	timer += GetFrameTime();

	return timer >= threshold;
}

ConditionShell::ConditionShell(const vector<Enemy*>& shells) :
	m_shells(shells) {}
bool ConditionShell::evaluate(Enemy& e)
{
	for (auto& s : m_shells)
	{
		if (CheckCollision(e, *s))
		{
			return true;
		}
	}
	return false;
}


ConditionFireBall::ConditionFireBall(const vector<FireBall*>& balls) :
	m_fireballs(balls) {}
bool ConditionFireBall::evaluate(Enemy& e)
{
	for (auto& s : m_fireballs)
	{
		if (CheckCollision(e, *s))
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
	if (CheckCollision(e, m_player))
	{
		return true;
	}
	return false;
}
