#pragma once

#include "vector"

using std::vector;

class Enemy;
class Mario;

class ICollisionPlayerStrategy
{
public:
	virtual void collide(Enemy&, Mario&) = 0;
	virtual ~ICollisionPlayerStrategy() = default;
};

class CollisionStrategyPlayerNothing : public ICollisionPlayerStrategy
{
	void collide(Enemy&, Mario&) override;
};



class CollisionStrategyFireBall : public ICollisionPlayerStrategy
{
public:
	void collide(Enemy&, Mario&) override;
};





//class CollisionStrategyPlayerStomp : public ICollisionStrategy
//{
//public:
//	CollisionStrategyPlayerStomp();
//	void collide(Enemy&, collisionType*) override;
//};
//class CollisionStrategyPlayerKick : public ICollisionStrategy
//{
//public:
//	CollisionStrategyPlayerKick();
//	void collide(Enemy&, collisionType*) override;
//};

class CollisionPlayerStrategyCombined : public ICollisionPlayerStrategy
{
public:
	void collide(Enemy&, Mario&) override;
	void addStrategy(ICollisionPlayerStrategy*);
	~CollisionPlayerStrategyCombined();

private:
	vector<ICollisionPlayerStrategy*> m_strategies;
};