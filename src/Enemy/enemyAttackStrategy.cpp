#include "Enemy/enemyAttackStrategy.h"
#include "Enemy/enemyManager.h"
#include "Enemy/enemy.h"


AttackStrat::AttackStrat(EnemyManager* manager, EnemyType type):
	m_manager(manager), m_type(type) {}
AttackStrat::AttackStrat(EnemyManager* manager, EnemyType type, int amount) :
	m_manager(manager), m_type(type), m_amount(amount) {}
AttackStrat::AttackStrat(EnemyManager* manager, EnemyType type, int amount, float timer) :
	m_manager(manager), m_type(type), m_amount(amount), m_threshold(timer) {}
void AttackStrat::attack(Enemy& e) const
{
	m_manager->spawnEnemyAt(m_type, e.GetPosition() + Vector2{e.getHurtBox().width /2,0 });
}


//AttackThrowHammer::AttackThrowHammer(EnemyManager* manager) :
//	m_manager(manager)
//{}
//void AttackThrowHammer::attack(Enemy& e) const
//{
//	m_manager->spawnEnemyAt(m_type, e.GetPosition() + Vector2Scale({ e.getHurtBox().width ,e.getHurtBox().height }, 1 / 2));
//}
//
//AttackFireBall::AttackFireBall(EnemyManager* manager):
//	m_manager(manager)
//{}
//void AttackFireBall::attack(Enemy& e) const
//{
//	m_manager->spawnEnemyAt(m_type, e.GetPosition() + Vector2Scale({ e.getHurtBox().width ,e.getHurtBox().height }, 1 / 2));
//}
//
//AttackSpiny::AttackSpiny(EnemyManager* manager) :
//	m_manager(manager) {}
//void AttackSpiny::attack(Enemy& e) const
//{
//	m_manager->spawnEnemyAt(m_type, e.GetPosition() + Vector2Scale({ e.getHurtBox().width ,e.getHurtBox().height }, 1 / 2));
//}
//
//void AttackCombined::attack(Enemy& e) const
//{
//	for (auto m : m_Strategies)
//	{
//		m->attack(e);
//	}
//}
//void AttackCombined::addStrategy(IAttackStrategy* s)
//{
//	m_Strategies.push_back(s);
//}
//AttackCombined::~AttackCombined()
//{
//	for (auto m : m_Strategies)
//	{
//		delete m;
//	}
//}