#include "enemyMoveStrategy.h"
#include "enemy.h"
#include "raymath.h"
#include "cmath"

MoveStrategyChase::MoveStrategyChase(int value, const Player* p):
	speed(value), play(p)
{}
void MoveStrategyChase::move(Enemy& e)
{
	Vector2 direction = play.direction - e.getPositon();
	e.setVelocity(Vector2Scale(direction,speed));
}

MoveStrategyFall::MoveStrategyFall(int value) :
	gravity(value)
{}
void MoveStrategyFall::move(Enemy& e)
{
	Vector2 temp = { 0, gravity * GetFrameTime()};
	e.addVelocity(temp);
}

MoveStrategyKeepDistance::MoveStrategyKeepDistance(int s, Vector2 off, const Player* p) :
	speed(s), offset(off), play(p)
{}
void MoveStrategyKeepDistance::move(Enemy& e)
{
	Vector2 lakituTarget = play.position + offset;
	Vector2 direction = lakituTarget - e.getPositon();
	e.setVelocity(Vector2Normalize(direction * speed));
}

MoveStrategyBasic::MoveStrategyBasic(int value,Enemy& e):
	speed(value)
{
	Vector2 temp = e.getVelocity();
	temp.x = speed;
	e.setVelocity(temp);	//so it is 20 instead of 20+x...
}
void MoveStrategyBasic::move(Enemy& e)
{
	if (collisionWall)
	{
		e.addVelocity(Vector2Scale(velocity,-2));
	}
}

MoveStrategySwayUpDown::MoveStrategySwayUpDown(float vel,float fre):
	magnitude(vel), frequency(fre)
{}
void MoveStrategySwayUpDown::move(Enemy& e)
{
	e.addVelocity(Vector2Scale(oldVelo, -1));
	oldVelo = Vector2Scale(velo, sinf(GetTime() * frequency));
	e.addVelocity(oldVelo);
}

MoveStrategyRandom::MoveStrategyRandom(int b, int s, Vector2* m):
	boundary(b),speed(s), mark(m)
{}
void MoveStrategyRandom::move(Enemy& e)
{
	Vector2 direction = Vector2Subtract(randomTarget, e.getPositon());
	float distance = Vector2Length(direction);

	if (distance < 1.0f || distance > boundary)
	{
		e.setVelocity(Vector2Normalize(direction) * speed);
	}
	else
	{
		Vector2 temp = *mark;
		temp.x = (float)GetRandomValue(temp.x - boundary,temp.x);
		randomTarget = temp;
	}
}

//MoveStrategyJump::MoveStrategyJump(int m) :
//	magnitude(m)
//{}
//void MoveStrategyJump::move(Enemy& e)
//{
//	if (collisonFloor)
//	{
//		Vector2 temp = e.getVelocity();
//		temp.x = magnitude;
//		e.setVelocity(temp);
//	}
//}

void MoveStrategyCombined::move(Enemy& e)
{
	for (auto s : list)
	{
		s->move(e);
	}
}
void MoveStrategyCombined::addStrategy(IMoveStrategy* s)
{
	list.push_back(s);
}
MoveStrategyCombined::~MoveStrategyCombined()
{
	for (auto s : list)
	{
		delete s;
	}
}