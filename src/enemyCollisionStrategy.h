#pragma once

#include "vector"

using std::vector;

class Enemy;

class ICollisionStrategy
{
public:
	virtual void collide(Enemy&, collisionType) = 0;
	virtual ~ICollisionStrategy() = default;
};

class CollisionStrategyNothing : public ICollisionStrategy
{
	void collide(Enemy&, collisionType) override;
};

class CollisionStrategyWallReverseDirection : public ICollisionStrategy
{
public:
	void collide(Enemy&, collisionType) override;


};

class CollisionStrategyFireBall : public ICollisionStrategy
{
public:
	void collide(Enemy&, collisionType) override;
};

class CollisionStrategyFloorWalk : public ICollisionStrategy
{
public:
	void collide(Enemy&, collisionType) override;

};

class CollisionStrategyFloorJump : public ICollisionStrategy
{
public:
	CollisionStrategyFloorJump(int mangnitude);
	void collide(Enemy&, collisionType) override;
private:
	int m_magnitude;
};

class CollisionStrategyPlayerStomp : public ICollisionStrategy
{
public:
	CollisionStrategyPlayerStomp();
	void collide(Enemy&, collisionType) override;
};
class CollisionStrategyPlayerKick : public ICollisionStrategy
{
public:
	CollisionStrategyPlayerKick();
	void collide(Enemy&, collisionType) override;
};

class CollisionStrategyCombined : public ICollisionStrategy
{
public:
	void collide(Enemy&, collisionType) override;
	void addStrategy(ICollisionStrategy*);
	~CollisionStrategyCombined();

private:
	vector<ICollisionStrategy*> m_strategies;
};