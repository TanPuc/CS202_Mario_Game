#pragma once	

#include <vector>

#include "enemyEnum.h"

using std::vector;

class Enemy;

class EnemyManager;


class IAttackStrategy
{
public:
	virtual void attack(Enemy&) const = 0;
};

class AttackThrowHammer : public IAttackStrategy
{
public:
	AttackThrowHammer(EnemyManager*);
	void attack(Enemy&) const override;
private:
	EnemyManager* m_manager;
	EnemyType m_type = EnemyType::hammer;
};

class AttackFireBall : public IAttackStrategy
{
public:
	AttackFireBall(EnemyManager*);
	void attack(Enemy&) const override;
private:
	EnemyManager* m_manager;
	EnemyType m_type = EnemyType::fireball;
};

class AttackSpiny : public IAttackStrategy
{
public:
	AttackSpiny(EnemyManager*);
	void attack(Enemy& e) const override;
private:
	EnemyManager* m_manager;
	EnemyType m_type = EnemyType::spiny;
};

class AttackNothing :public IAttackStrategy
{
public:
	void attack(Enemy&) const override;
};

class AttackCombined : public IAttackStrategy
{
public:
	void attack(Enemy&) const override;
	void addStrategy(IAttackStrategy*);
	~AttackCombined();

private:
	vector<IAttackStrategy*> m_Strategies;
};
