#include "enemy.h"
#include "enemyState.h"
#include "enemyMoveStrategy.h"
#include "enemyAttackStrategy.h"

Enemy::Enemy(int type, Vector2 position, EnemyState* state):
	m_Type(type), m_position(position), m_State(state),
{}
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