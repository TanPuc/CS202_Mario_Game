#include "enemyCollisionMap.h"

void CollisionStrategyMapNothing::collide(Enemy& e, Map& m)
{

}

CollisionStrategyFloorJump::CollisionStrategyFloorJump(float mag) :
	m_magnitude(mag)
{}
void CollisionStrategyFloorJump::collide(Enemy& e, Map& m)
{
	
}

void CollisionStrategyFloorWalk::collide(Enemy& e, Map& m)
{
	
}

void CollisionStrategyWallReverseDirection::collide(Enemy& e, Map& m)
{


}

void CollisionMapStrategyCombined::collide(Enemy& e, Map& m)
{
	for (auto s : m_strategies)
	{
		s->collide(e, m);
	}
}
void CollisionMapStrategyCombined::addStrategy(ICollisionMapStrategy* s)
{
	m_strategies.push_back(s);
}
CollisionMapStrategyCombined::~CollisionMapStrategyCombined()
{
	for (auto s : m_strategies)
	{
		delete s;
	}
}