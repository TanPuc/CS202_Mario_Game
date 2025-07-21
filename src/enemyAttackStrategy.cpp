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
	if (timeTotal >= cooldown)
	{
		m_manager->spawnEnemyAt(m_type, e.getPositon());
		timeTotal = 0;
	}

	timeTotal += GetFrameTime();
}

AttackFireBall::AttackFireBall(EnemyManager* manager):
	m_manager(manager)
{}
void AttackFireBall::attack(Enemy& e) const
{
	if (timeTotal >= cooldown)
	{
		m_manager->spawnEnemyAt(m_type, e.getPositon());
		timeTotal = 0;
	}

	timeTotal += GetFrameTime();
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