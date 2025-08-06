#include "enemyStateCondition.h"

#include "raylib.h"

bool ConditionTimer::evaluate()
{
	timer += GetFrameTime();

	return timer >= threshold;
}