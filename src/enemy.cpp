
#include "cmath"

#include "enemy.h"
#include "enemyState.h"
#include "enemyMoveStrategy.h"
#include "enemyAttackStrategy.h"
#include "enemyCollisionPlayer.h"
#include "enemyCollisionMap.h"
#include "enemyFSM.h"
#include "enemySprite.h"

Enemy::Enemy(EnemyType type, FiniteStateMachine* state, SpriteEnemy* sprite, Vector2 size, Vector2 positon):
	Entity(positon, size),
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

void Enemy::Update(Level& level)
{
	if (m_CollideMap) m_CollideMap->handleCollide(*this, level);

	update();

}
void Enemy::update()
{
	if (m_MoveStrategy) m_MoveStrategy->move(*this);
	position = Vector2Add(position, Vector2Scale(Vector2Scale(m_velocity, GetFrameTime()), float(m_direction)));


	if (m_AttackStrategy) m_AttackStrategy->attack(*this);
	
	if (m_FSM) m_FSM->update(*this);

	if (m_sprite) m_sprite->update(*this);

	rect.x = position.x; //most stupid fck i have ever seen
	rect.x = position.y;
	DrawRectangleLines(rect.x, rect.y, rect.width, rect.height, RED);
}
void Enemy::Draw()
{
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
void Enemy::setCollisionMap(CollisionMap* collidemap)
{
	delete m_CollideMap;
	m_CollideMap = collidemap;
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

int Enemy::getDirection() const
{
	return m_direction;
}
void Enemy::reverseDirection()
{
	m_direction *= -1;
}

Rectangle Enemy::getHitBox() const {
	return m_HitBox;
}
void Enemy::setHitBox()
{
	//rect.
}

Vector2 Enemy::getPrevPosition() const
{
	Vector2 result = { rect.x - m_velocity.x, rect.y - m_velocity.y };
	return result;
}

void Enemy::setPosition(Vector2 pos)
{
	position = pos;
}

void Enemy::ResolveCollision(Entity& other)
{

}
void Enemy::ResolveCollision(Level& level)
{

}

//Vector2 Enemy::getPositon() const
//{
//	return position;
//}
//void Enemy::setCollisionPlayerStrategy(ICollisionPlayerStrategy* strategy)
//{
//	delete m_CollidePlayerStrategy;
//	m_CollidePlayerStrategy = strategy;
//}
