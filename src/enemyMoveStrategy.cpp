#include "enemyMoveStrategy.h"
#include "enemy.h"
#include "raymath.h"
#include "cmath"
#include "Mario.h"

MoveStrategyBasic::MoveStrategyBasic(int value, Enemy& e, const Mario& mario) :
	speed(value)
{
	if (e.GetPosition().x >= mario.GetPosition().x)
	{
		e.setVelocityX(-speed);
	}
	else {
		e.setVelocityX(speed);	//so it is 20 instead of 20+x...
	}
}
MoveStrategyBasic::MoveStrategyBasic(int value, Enemy& e) :
	speed(value)
{
	e.setVelocityX(speed);	//so it is 20 instead of 20+x...
}
void MoveStrategyBasic::move(Enemy& e)
{

}

MoveStrategySwayUpDown::MoveStrategySwayUpDown(float mag, float fre) :
	m_magnitude(mag), m_frequency(fre)
{}
void MoveStrategySwayUpDown::move(Enemy& e)
{
	e.setVelocityY(m_magnitude * sinf(GetTime() * m_frequency));
}

MoveStrategyFall::MoveStrategyFall(int value) :
	gravity(value)
{}
void MoveStrategyFall::move(Enemy& e)
{
	e.addVelocityY(gravity * GetFrameTime());
}

MoveStrategyKeepDistance::MoveStrategyKeepDistance(float s, Vector2 off, Mario* p) :
	m_speed(s), m_offset(off), m_player(p)
{}
void MoveStrategyKeepDistance::move(Enemy& e)
{
	Vector2 lakituTarget = { m_player->position.x + m_offset.x,m_offset.y };
	Vector2 direction = lakituTarget - Vector2{e.GetPosition().x, m_offset.y};
	Vector2 temp = Vector2Scale(Vector2Normalize(direction) , m_speed);
	e.setVelocityX(temp.x);
	e.setVelocityY(temp.y);
}

MoveStrategyChase::MoveStrategyChase(int value, Mario* p, const Enemy& e) :
	magnitude(value), player(p)
{
	Vector2 direction = player->position - e.GetPosition();
	m_result = Vector2Scale(Vector2Normalize(direction), magnitude);
}
void MoveStrategyChase::move(Enemy& e)
{
	e.setVelocityX(m_result.x);
	e.setVelocityY(m_result.y);
}

MoveStrategyRandom::MoveStrategyRandom(float b, float s, Vector2* m):
	m_boundary(b),m_speed(s), m_mark(m)
{}
void MoveStrategyRandom::move(Enemy& e)
{
	Vector2 direction = Vector2Subtract(randomTarget, e.GetPosition());
	float distance = Vector2Length(direction);
	
	Vector2 temp;

	if (distance < 1.0f || distance > m_boundary)
	{
		temp = Vector2Normalize(direction) * m_speed;
		e.setVelocityX(temp.x);
	}
	else
	{
		temp = *m_mark;
		temp.x = (float)GetRandomValue(temp.x - m_boundary,temp.x);
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