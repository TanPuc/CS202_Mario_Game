#include "Enemy/enemyMoveStrategy.h"
#include "Enemy/enemy.h"
#include "raymath.h"
#include "cmath"
#include "Character.h"
#include "algorithm"
#include "Physics.h"

using namespace std;

MoveStrategyBasic::MoveStrategyBasic(int value, Enemy& e, const Character& Character) :
	speed(value)
{
	if (e.GetPosition().x + e.getHurtBox().width/2 >= Character.GetPosition().x + Character.rect.width/2)
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
	e.setVelocityX(-speed);	//so it is 20 instead of 20+x...
}
void MoveStrategyBasic::move(Enemy& e)
{
	int direction = 1;
	if (e.getVelocity().x <= 0)
		direction = -1;
	else direction = 1;
	e.setVelocityX(abs(speed) * direction);
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

MoveStrategyKeepDistance::MoveStrategyKeepDistance(float s, Vector2 off, Character* p) :
	m_speed(s), m_offset(off), m_player(p)
{}
void MoveStrategyKeepDistance::move(Enemy& e)
{
	float Lengthfactor = m_player->velocity.x / MAX_VELOCITY;

	Vector2 lakituTarget = { m_player->position.x + m_offset.x * Lengthfactor ,m_offset.y };
	Vector2 direction = lakituTarget - Vector2{e.GetPosition().x, m_offset.y};


	Vector2 temp = Vector2Scale(Vector2Normalize(direction) , m_speed);

	/*test*/ //e.setVelocityX(0);
	float result;
	
	if (temp.x >= 0)
	{
		result = temp.x * Lengthfactor;
		/*if (result < temp.x / 4)
		{
			result = temp.x / 4;
		}*/
		e.addVelocityX(result);

	}
	else
	{
		result = temp.x * (abs(e.GetPosition().x - m_player->GetPosition().x) / m_offset.x);
		if (result < temp.x/5)
		{
			result = temp.x / 5;
		}
		e.addVelocityX(result);
	}

	// cout << e.getVelocity().x << endl;

	if (e.getVelocity().x > m_speed) e.setVelocityX(m_speed);


	e.setVelocityY(temp.y);
}

MoveStrategyChase::MoveStrategyChase(int value, Character* p, const Enemy& e) :
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
{
	randomTarget = *m_mark;
}
void MoveStrategyRandom::move(Enemy& e)
{
	Vector2 direction = Vector2Subtract(randomTarget, e.GetPosition());
	float distance = Vector2Length({ direction.x,0 });
	
	Vector2 temp;

	if (distance < 10.0f || distance > m_boundary)
	{
		temp = Vector2{ m_mark->x, e.GetPosition().y };
		temp.x = (float)GetRandomValue(temp.x - m_boundary, temp.x + m_boundary);
		randomTarget = temp;
	}
	else
	{
		//if (distance < 1) { direction = { -1,0 }; }
		temp = Vector2Normalize({ direction.x,0 }) * m_speed;
		e.setVelocityX(temp.x);
	}
}

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