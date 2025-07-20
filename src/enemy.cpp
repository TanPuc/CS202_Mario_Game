#include "enemy.h"
#include "enemyState.h"
#include "enemyMoveStrategy.h"

Enemy::Enemy(int type):
	m_MoveStrategy(nullptr),m_State(nullptr),m_Type(0)
{
	switch (type)
	{
	case EnemyType::goopa:
	{
		m_MoveStrategy = new MoveStrategyWander();
		m_State = new AliveState();

		break;
	}
	case EnemyType::koopa:
	{
		m_MoveStrategy = new MoveStrategyWander();
		m_State = new AliveState();

		break;
	}
	default:
		break;
	}
}
Enemy::~Enemy()
{
	destroy();
}


void Enemy::handleInput(int Input)
{
	m_State->handleInput(*this, Input);
}


void Enemy::setState(EnemyState* state)
{
	delete m_State;
	m_State = state;
}
void Enemy::setStrategy(IMoveStrategy* strategy)
{
	delete m_MoveStrategy;
	m_MoveStrategy = strategy;
}

void Enemy::destroy()
{
	delete m_MoveStrategy;
	m_MoveStrategy = nullptr;

	delete m_State;
	m_State = nullptr;
}


Vector2 Enemy::getVelocity() const
{
	return m_velocity;
}
void Enemy::setVelocity(const Vector2& velo)
{
	m_velocity = velo;
}
void Enemy::addVelocity(const Vector2& velo)
{
	m_velocity.x += velo.x;
	m_velocity.y += velo.y;
}

Vector2 Enemy::getPositon() const
{
	return m_position;
}