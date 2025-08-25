#pragma once

#include "vector"

using std::vector;

class Enemy;
class Character;

class ICollisionPlayerStrategy
{
public:
	virtual void collide(Enemy &, Character &) = 0;
	virtual ~ICollisionPlayerStrategy() = default;
};

class CollisionStrategyPlayerNothing : public ICollisionPlayerStrategy
{
	void collide(Enemy &, Character &) override;
};

class CollisionStrategyFireBall : public ICollisionPlayerStrategy
{
public:
	void collide(Enemy &, Character &) override;
};

// class CollisionStrategyPlayerStomp : public ICollisionStrategy
//{
// public:
//	CollisionStrategyPlayerStomp();
//	void collide(Enemy&, collisionType*) override;
// };
// class CollisionStrategyPlayerKick : public ICollisionStrategy
//{
// public:
//	CollisionStrategyPlayerKick();
//	void collide(Enemy&, collisionType*) override;
// };

class CollisionPlayerStrategyCombined : public ICollisionPlayerStrategy
{
public:
	void collide(Enemy &, Character &) override;
	void addStrategy(ICollisionPlayerStrategy *);
	~CollisionPlayerStrategyCombined();

private:
	vector<ICollisionPlayerStrategy *> m_strategies;
};