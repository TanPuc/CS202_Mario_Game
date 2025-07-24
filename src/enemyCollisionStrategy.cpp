#include "enemyCollisionStrategy.h"

void CollisionStrategyFireBall::collide(Enemy& e, collisionType)
{
	if (collisionType)
	{
		e.setState();
	}
}

CollisionStrategyFloorJump::CollisionStrategyFloorJump(int mag):
	m_magnitude(mag)
{}
void CollisionStrategyFloorJump::collide(Enemy& e, collisionType)
{
	if (collisionType)
	{
		e.setVelocityY(-m_magnitude);
	}
}

void CollisionStrategyFloorWalk::collide(Enemy& e, collisionType)
{
	if (collisionType)
	{
		e.setPosition();
	}
}

void CollisionStrategyWallReverseDirection::collide(Enemy& e, collisionType)
{
	if (collisionType)
	{
		e.setVelocityX();
	}
}

void CollisionStrategyCombined::collide(Enemy& e, collisionType)
{
	for (auto s : m_strategies)
	{
		s->collide(e, collisionType);
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