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

	ICollisionMapStrategy* m_X = nullptr;
	ICollisionMapStrategy* m_Y = nullptr;

public:
	CollisionMap(ICollisionMapStrategy* X, ICollisionMapStrategy* Y);
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

class CollisionStrategyState : public ICollisionMapStrategy
{
public:
	void collide(Enemy&) override;
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