#include "Enemy/enemyCollisionPlayer.h"

void CollisionStrategyPlayerNothing::collide(Enemy& e, Mario& m)
{

}

void CollisionStrategyFireBall::collide(Enemy& e, Mario& m)
{


}






void CollisionPlayerStrategyCombined::collide(Enemy& e, Mario& m)
{
	for (auto s : m_strategies)
	{
		s->collide(e, m);
	}
}
void CollisionPlayerStrategyCombined::addStrategy(ICollisionPlayerStrategy* s)
{
	m_strategies.push_back(s);
}
CollisionPlayerStrategyCombined::~CollisionPlayerStrategyCombined()
{
	for (auto s : m_strategies)
	{
		delete s;
	}
}