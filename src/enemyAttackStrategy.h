#pragma once	

#include "vector"

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
	const int m_type = EnemyType::hammer;
};

class AttackFireBall : public IAttackStrategy
{
public:
	AttackFireBall(EnemyManager*);
	void attack(Enemy&) const override;
private:
	EnemyManager* m_manager;
	const int m_type = EnemyType::fireball;
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
