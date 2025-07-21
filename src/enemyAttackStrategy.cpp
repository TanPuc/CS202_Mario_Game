#include "enemyAttackStrategy.h"
#include "enemyManager.h"
#include "enemy.h"

void AttackNothing::attack(Enemy& e) const
{
}

AttackThrowHammer::AttackThrowHammer(EnemyManager* manager) :
	m_manager(manager)
{}
void AttackThrowHammer::attack(Enemy& e) const
{
	m_manager->spawnEnemyAt(m_type,e.getPositon());
}

AttackFireBall::AttackFireBall(EnemyManager* manager):
	m_manager(manager)
{}
void AttackFireBall::attack(Enemy& e) const
{
	m_manager->spawnEnemyAt(m_type, e.getPositon());
}

AttackCombined::attack(Enemy& e) const
{
	for (auto m : m_Strategies)
	{
		e->attack(m);
	}
}
void AttackCombined::addStrategy(IAttackStrategy* s)
{
	m_Strategies.push_back(s);
}
AttackCombined::~AttackCombined()
{
	for (auto m : m_Strategies)
	{
		delete m;
	}
}