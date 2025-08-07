#pragma once

#include "vector"

using std::vector;

class Enemy;
class Map;

class ICollisionMapStrategy
{
public:
	virtual void collide(Enemy&, Map&) = 0;
	virtual ~ICollisionMapStrategy() = default;
};

class CollisionStrategyMapNothing : public ICollisionMapStrategy
{
	void collide(Enemy&, Map&) override;
};

class CollisionStrategyWallReverseDirection : public ICollisionMapStrategy
{
public:
	void collide(Enemy&, Map&) override;
};

class CollisionStrategyFloorWalk : public ICollisionMapStrategy
{
public:
	void collide(Enemy&, Map&) override;
};

class CollisionStrategyFloorJump : public ICollisionMapStrategy
{
public:
	CollisionStrategyFloorJump(float mangnitude);
	void collide(Enemy&, Map&) override;
private:
	float m_magnitude;
};



class CollisionMapStrategyCombined : public ICollisionMapStrategy
{
public:
	void collide(Enemy&, Map&) override;
	void addStrategy(ICollisionMapStrategy*);
	~CollisionMapStrategyCombined();

private:
	vector<ICollisionMapStrategy*> m_strategies;
};