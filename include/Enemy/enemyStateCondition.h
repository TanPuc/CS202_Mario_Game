#pragma once
#include <vector>
#include "enemy.h"
#include "DGameObjects/FireBall.h"
#include "Character.h"


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
	ConditionFireBall(const vector<shared_ptr<FireBall>>& balls);
	ConditionFireBall(const vector<shared_ptr<FireBall>>& balls, int amount);
	bool evaluate(Enemy& e) override;
private:
	const vector<shared_ptr<FireBall>>& m_fireballs;
	int m_amount = 1;
	int m_counter = 0;
	float timer = 0;
	float immuneDuration = 0.5f;
	bool isImmune = false;
};
class ConditionStomped : public EnemyStateCondition
{
public :
	ConditionStomped(const Character& player);
	bool evaluate(Enemy& e) override;
private:
	const Character& m_player;
};
class ConditionKicked : public EnemyStateCondition
{
public:
	ConditionKicked(const Character& player);
	bool evaluate(Enemy& e) override;
private:
	const Character& m_player;
};
class ConditionGrounded : public EnemyStateCondition
{
public :
	ConditionGrounded(Level& level);
	bool evaluate(Enemy& e) override;
private:
	Level& m_level;
};

