#include "enemyCollisionStrategy.h"

void CollisionStrategyFireBall::collide(Enemy& e)
{

}

void CollisionStrategyFloorJump::collide(Enemy& e)
{

}

void CollisionStrategyFloorWalk::collide(Enemy& e)
{

}

void CollisionStrategyWallReverseDirection::collide(Enemy& e)
{

}

void CollisionStrategyCombined::collide(Enemy& e)
{
	for (auto s : m_strategies)
	{
		s->collide(e);
	}
}
void CollisionStrategyCombined::addStrategy(ICollisionStrategy* s)
{
	m_strategies.push_back(s);
}
CollisionStrategyCombined::~CollisionStrategyCombined()
{
	for (auto s : m_strategies)
	{
		delete s;
	}
}