#include "enemy.h"
#include "enemyState.h"
#include "enemyMoveStrategy.h"
#include "enemyAttackStrategy.h"
#include "enemyCollisionStrategy.h"
#include "enemyFSM.h"

Enemy::Enemy(int type, FiniteStateMachine* state):
	m_Type(type), m_FSM(state)
{}
Enemy::~Enemy()
{
	destroy();
}


void Enemy::handleInput(int Input)
{
	m_State->handleInput(*this, Input);
}
void Enemy::update()
{
	m_AttackStrategy->attack();
	m_MoveStrategy->move();
	
	m_FSM->update(*this);
}

void Enemy::setState(EnemyState* state)
{
	delete m_State;
	m_State = state;
}
void Enemy::setMoveStrategy(IMoveStrategy* strategy)
{
	delete m_MoveStrategy;
	m_MoveStrategy = strategy;
}
void Enemy::setAttackStrategy(IAttackStrategy* strategy)
{
	setVelocityX(0);
	setVelocityY(0);
	delete m_AttackStrategy;
	m_AttackStrategy = strategy;
}
//void Enemy::setCollisionStrategy(ICollisionStrategy* strategy)
//{
//	delete m_CollideStrategy;
//	m_CollideStrategy = strategy;
//}

void Enemy::destroy()
{
	delete m_MoveStrategy;
	m_MoveStrategy = nullptr;

	delete m_State;
	m_State = nullptr;
}


void Enemy::setVelocityX(float X)
{
	m_velocity.x = X;
}
void Enemy::setVelocityY(float Y)
{
	m_velocity.y = Y;
}
void Enemy::addVelocityY(float Y)
{
	m_velocity.y += Y;
}

Vector2 Enemy::getPositon() const
{
	return m_position;
}

void Enemy::setPosition(Vector2 pos)
{
	m_position = pos;
}