#pragma once

#include "vector"

using std::vector;


class Enemy;

class IMoveStrategy
{
public:

	virtual void move(Enemy& e) = 0;
private:

};

class MoveStrategyWander : public IMoveStrategy
{
public:
	MoveStrategyWander(int,Enemy&);
	void move(Enemy& e) override;

private:
	int speed;
	Vector2 velocity = { speed,0 };
};
class MoveStrategySwayUpDown : public IMoveStrategy
{
public:
	MoveStrategySwayUpDown(float, float);
	void move(Enemy& e) override;
private:
	float magnitude;
	float frequency;
	Vector2 oldVelo = { 0,0 };
	Vector2 velo = { 0,magnitude };
};
class MoveStrategyKeepDistance : public IMoveStrategy
{
public:
	MoveStrategyKeepDistance(int, Vector2, const Player*);
	void move(Enemy& e) override;
private:
	int speed;
	Vector2 offset;
	const Player* play;

};
class MoveStrategyChase : public IMoveStrategy
{
public:
	MoveStrategyChase(int, const Player*);
	void move(Enemy& e) override;
private:
	int speed;
	const Player* play;
};
class MoveStrategyFall : public IMoveStrategy
{
public:
	MoveStrategyFall(int);
	void move(Enemy& e) override;
private:
	int gravity;
};
class MoveStrategyRandom : public IMoveStrategy
{
public:
	MoveStrategyRandom(int, int, Vector2*);
	void move(Enemy&) override;
private:
	int boundary;
	int speed;
	Vector2* mark;
	Vector2 randomTarget;
};
class MoveStrategyJump : public IMoveStrategy
{
public:
	MoveStrategyJump(int);
	void move(Enemy&) override;
private:
	int magnitude;
};

class MoveStrategyCombined :public IMoveStrategy
{
public:
	void move(Enemy&) override;
	void addStrategy(IMoveStrategy*);
	~MoveStrategyCombined();
private:
	vector<IMoveStrategy*> list;
};