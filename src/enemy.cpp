
#include "cmath"

#include "enemy.h"
#include "enemyState.h"
#include "enemyMoveStrategy.h"
#include "enemyAttackStrategy.h"
#include "enemyCollisionPlayer.h"
#include "enemyCollisionMap.h"
#include "enemyFSM.h"
#include "enemySprite.h"

Enemy::Enemy(EnemyType type, FiniteStateMachine* state, SpriteEnemy* sprite):
	m_Type(type), m_FSM(state), m_sprite(sprite)
{
	m_FSM->runInitialState(*this);
}
Enemy::~Enemy()
{
	destroy();
}


void Enemy::handleInput(int Input)
{
	//m_State->handleInput(*this, Input);
}
void Enemy::update()
{
	m_MoveStrategy->move(*this);
	m_position = Vector2Add(m_position, Vector2Scale(m_velocity, GetFrameTime()));

	m_AttackStrategy->attack(*this);
	
	m_FSM->update(*this);

	m_sprite->update(*this);
	m_sprite->draw(*this);
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
void Enemy::setCollisionMapStrategy(ICollisionMapStrategy* strategy)
{
	delete m_CollideMapStrategy;
	m_CollideMapStrategy = strategy;
}
void Enemy::setCollisionPlayerStrategy(ICollisionPlayerStrategy* strategy)
{
	delete m_CollidePlayerStrategy;
	m_CollidePlayerStrategy = strategy;
}

void Enemy::setSprite(StateType state)
{
	m_sprite->setCurrentState(state);
}

void Enemy::destroy()
{
	delete m_MoveStrategy;
	m_MoveStrategy = nullptr;

	delete m_FSM;
	m_FSM = nullptr;
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