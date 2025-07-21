#pragma once

#include "vector"

using std::vector;

class Enemy;

class ICollisionStrategy
{
public:
	virtual void collide(Enemy&) = 0;
	virtual ~ICollisionStrategy() = default;
};

class CollisionStrategyWallReverseDirection : public ICollisionStrategy
{
public:
	void collide(Enemy&) override;


};

class CollisionStrategyFireBall : public ICollisionStrategy
{
public:
	void collide(Enemy&) override;
};

class CollisionStrategyFloorWalk : public ICollisionStrategy
{
public:
	void collide(Enemy&) override;

};

class CollisionStrategyFloorJump : public ICollisionStrategy
{
public:
	void collide(Enemy&) override;
};

class CollisionStrategyCombined : public ICollisionStrategy
{
public:
	void collide(Enemy&) override;
	void addStrategy(ICollisionStrategy*);
	~CollisionStrategyCombined();

private:
	vector<ICollisionStrategy*> m_strategies;
};