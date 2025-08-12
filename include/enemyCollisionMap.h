#pragma once

#include "vector"
#include "raylib.h"

using std::vector;

class Enemy;
class Level;
class ICollisionMapStrategy;

class CollisionMap
{
private:
	Vector2 m_velocity = {};
	Vector2 m_overlap = {};
    int m_choice = 0;

	ICollisionMapStrategy* m_X = nullptr;
	ICollisionMapStrategy* m_Y = nullptr;

public:
	CollisionMap(ICollisionMapStrategy* X, ICollisionMapStrategy* Y);
	~CollisionMap();
	void CalculateOverlap(const Rectangle& A, const Rectangle& B);

	void handleCollide(const Rectangle& A, const Rectangle& B);
	void handleCollide(Enemy& e, const Level& level);
};



class ICollisionMapStrategy
{
public:
	virtual void collide(Enemy&) = 0;
	virtual ~ICollisionMapStrategy() = default;
};

class CollisionStrategyXPushOut : public ICollisionMapStrategy
{
public:
	void collide(Enemy&) override;
};
class CollisionStrategyXReverse : public ICollisionMapStrategy
{
public:
	void collide(Enemy&) override;
};

class CollisionStrategyYPushOut : public ICollisionMapStrategy
{
public:
	void collide(Enemy&) override;
};
class CollisionStrategyYJump : public ICollisionMapStrategy
{
public:
	CollisionStrategyYJump(float mangnitude);
	void collide(Enemy&) override;
private:
	float m_magnitude;
};

class CollisionMapStrategyCombined : public ICollisionMapStrategy
{
public:
	void collide(Enemy&) override;
	void addStrategy(ICollisionMapStrategy*);
	~CollisionMapStrategyCombined();

private:
	vector<ICollisionMapStrategy*> m_strategies;
};