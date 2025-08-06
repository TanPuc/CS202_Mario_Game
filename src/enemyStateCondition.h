#pragma once
class EnemyState;

class EnemyStateCondition
{
public:
	virtual bool evaluate() = 0;
};

class ConditionTimer : public EnemyStateCondition
{
public:
	bool evaluate() override;
private:
	float timer = 0;
	float threshold = 3;
};

class ConditionCollisionX : public EnemyStateCondition
{
public:
	bool evaluate() override;
private:

};

class ConditionCollisionY : public EnemyStateCondition
{
public:
	bool evaluate() override;
private:
};


