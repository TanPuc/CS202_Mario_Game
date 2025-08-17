#include "Enemy/enemyAttackStrategy.h"
#include "Enemy/enemyManager.h"
#include "Enemy/enemy.h"

AttackThrowHammer::AttackThrowHammer(EnemyManager* manager) :
	m_manager(manager)
{}
void AttackThrowHammer::attack(Enemy& e) const
{
	m_manager->spawnEnemyAt(m_type, e.GetPosition());
}

AttackFireBall::AttackFireBall(EnemyManager* manager):
	m_manager(manager)
{}
void AttackFireBall::attack(Enemy& e) const
{
	m_manager->spawnEnemyAt(m_type, e.GetPosition());
}

AttackSpiny::AttackSpiny(EnemyManager* manager) :
	m_manager(manager) {}
void AttackSpiny::attack(Enemy& e) const
{
	m_manager->spawnEnemyAt(m_type, e.GetPosition());
}

void AttackCombined::attack(Enemy& e) const
{
	for (auto m : m_Strategies)
	{
		m->attack(e);
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