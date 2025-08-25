#pragma once

#include "vector"
#include "raylib.h"
#include "array"

using namespace std;

class Enemy;
class Level;
class ICollisionMapStrategy;

class CollisionMap
{
private:
	vector<pair<array<int, 2>, float>> m_UnResolvedTiles;

	ICollisionMapStrategy* m_Direction = nullptr;
	ICollisionMapStrategy* m_Rectangle = nullptr;

public:
	CollisionMap(ICollisionMapStrategy* direction, ICollisionMapStrategy* rectangle);
	~CollisionMap();

	static bool compare2(const std::pair<Vector2, float>& a, const std::pair<Vector2, float>& b) {
		return a.second < b.second;
	}


	void DetectCollisionMap(Enemy& e, const Level& level);

	void ResolveCollisionMap(Enemy& e, const Level& level);

	void update(Enemy& e, const Level& level);


	//void CalculateOverlap(const Rectangle& A, const Rectangle& B);
	//void handleCollide(const Rectangle& A, const Rectangle& B);
	//void handleCollide(Enemy& e, const Level& level);
};



class ICollisionMapStrategy
{
public:
	virtual void collide(Enemy&, Rectangle) = 0;
	virtual ~ICollisionMapStrategy() = default;
};

class CollisionStrategyXPushOut : public ICollisionMapStrategy
{
public:
	void collide(Enemy&,  Rectangle) override;
};
class CollisionStrategyXReverse : public ICollisionMapStrategy
{
public:
	void collide(Enemy&, Rectangle) override;
};
class CollisionStrategyXReverseLedge : public ICollisionMapStrategy
{
public:
	void collide(Enemy&, Rectangle) override;
};

class CollisionStrategyYPushOut : public ICollisionMapStrategy
{
public:
	void collide(Enemy&, Rectangle) override;
};
class CollisionStrategyYJump : public ICollisionMapStrategy
{
public:
	CollisionStrategyYJump(float mangnitude);
	void collide(Enemy&, Rectangle) override;
private:
	float m_magnitude;
};

class CollisionStrategyState : public ICollisionMapStrategy
{
public:
	void collide(Enemy&, Rectangle) override;
};

class CollisionMapStrategyCombined : public ICollisionMapStrategy
{
public:
	void collide(Enemy&, Rectangle) override;
	void addStrategy(ICollisionMapStrategy*);
	~CollisionMapStrategyCombined();

private:
	vector<ICollisionMapStrategy*> m_strategies;
};