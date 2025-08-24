#pragma once

#include "vector"
#include "raylib.h"

using std::vector;


class Enemy;
class Mario;

class IMoveStrategy
{
public:

	virtual void move(Enemy& e) = 0;
private:

};

class MoveStrategyBasic : public IMoveStrategy
{
public:
	MoveStrategyBasic(int,Enemy&);
	MoveStrategyBasic(int, Enemy&, const Mario& mario);
	void move(Enemy& e) override;

private:
	int speed;
	Vector2 velocity = { (float)speed,0 };
};
class MoveStrategySwayUpDown : public IMoveStrategy
{
public:
	MoveStrategySwayUpDown(float magni, float freq);
	void move(Enemy& e) override;
private:
	float m_magnitude;
	float m_frequency;
};
class MoveStrategyFall : public IMoveStrategy
{
public:
	MoveStrategyFall(int);
	void move(Enemy& e) override;
private:
	int gravity;
};
class MoveStrategyKeepDistance : public IMoveStrategy
{
public:
	MoveStrategyKeepDistance(float speed, Vector2 offset, Mario* player);
	void move(Enemy& e) override;
private:
	float m_speed;
	Mario* m_player;

	Vector2 m_offset;


};
class MoveStrategyChase : public IMoveStrategy
{
public:
	MoveStrategyChase(int, Mario*, const Enemy& e);
	void move(Enemy& e) override;
private:
	int magnitude;
	Mario* player;
	Vector2 m_result;
};
class MoveStrategyRandom : public IMoveStrategy
{
public:
	MoveStrategyRandom(float boundary, float speed, Vector2* mark);
	void move(Enemy&) override;
private:
	float m_boundary;
	float m_speed;
	Vector2* m_mark;
	Vector2 randomTarget = *m_mark;
};
//class MoveStrategyJump : public IMoveStrategy
//{
//public:
//	MoveStrategyJump(int);
//	void move(Enemy&) override;
//private:
//	int magnitude;
//};

class MoveStrategyCombined :public IMoveStrategy
{
public:
	void move(Enemy&) override;
	void addStrategy(IMoveStrategy*);
	~MoveStrategyCombined();
private:
	vector<IMoveStrategy*> list;
};