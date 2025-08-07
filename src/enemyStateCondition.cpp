#include "enemyStateCondition.h"

#include "raylib.h"

bool ConditionTimer::evaluate()
{
	timer += GetFrameTime();

	return timer >= threshold;
}

bool ConditionCollisionX::evaluate()
{
	return false;
}

bool ConditionCollisionY::evaluate()
{
	return false;
}