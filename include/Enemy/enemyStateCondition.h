#pragma once
#include <vector>
#include "enemy.h"
#include "FireBall.h"
#include "Mario.h"


using namespace std;


class EnemyState;

class EnemyStateCondition
{
public:
	virtual bool evaluate(Enemy& e) = 0;
};

class ConditionTimer : public EnemyStateCondition
{
public:
	ConditionTimer(float timer);
	bool evaluate(Enemy& e) override;
private:
	float timer = 0;
	float threshold = 3;
};
class ConditionShell : public EnemyStateCondition
{
public:
	ConditionShell(const vector<Enemy*>& shells);
	bool evaluate(Enemy& e) override;
private:
	const vector<Enemy*>& m_shells;
};
class ConditionFireBall : public EnemyStateCondition
{
public:
	ConditionFireBall(const vector<FireBall*>& balls);
	bool evaluate(Enemy& e) override;
private:
	const vector<FireBall*>& m_fireballs;
};
class ConditionStomped : public EnemyStateCondition
{
public :
	ConditionStomped(const Mario& player);
	bool evaluate(Enemy& e) override;
private:
	const Mario& m_player;
};
class ConditionKicked : public EnemyStateCondition
{
public:
	ConditionKicked(const Mario& player);
	bool evaluate(Enemy& e) override;
private:
	const Mario& m_player;
};
class ConditionGrounded : public EnemyStateCondition
{
public :
	ConditionGrounded(const Level& level);
	bool evaluate(Enemy& e) override;
private:
	const Level& m_level;
};

