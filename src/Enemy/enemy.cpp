
#include "cmath"

#include "Enemy/enemy.h"
#include "Enemy/enemyState.h"
#include "Enemy/enemyMoveStrategy.h"
#include "Enemy/enemyAttackStrategy.h"
#include "Enemy/enemyCollisionPlayer.h"
#include "Enemy/enemyCollisionMap.h"
#include "Enemy/enemyFSM.h"
#include "Enemy/enemySprite.h"
#include "Enemy/enemyEnum.h"
#include "DGameState/PlayingState.h"

Enemy::Enemy(EnemyType type, FiniteStateMachine *state, SpriteEnemy *sprite, Vector2 size, Vector2 positon) : Entity(positon, size),
																											  m_Type(type), m_FSM(state), m_sprite(sprite)
{
	m_FSM->runInitialState(*this);
	setHurtBox(rect);
	setHitBox({rect.x, rect.y, m_HurtBox.width, m_HurtBox.height});
	setSpriteBox({position.x, position.y, rect.width, rect.height});
}
Enemy::~Enemy()
{
	destroy();
}

bool Enemy::isActive() const
{
	return m_isActive;
}
void Enemy::UnActivate()
{
	m_isActive = false;
}

void Enemy::handleInput(int Input)
{
	// m_State->handleInput(*this, Input);
}

void Enemy::Update(Level &level)
{
	// move -> FSM -> collide -> position -> sprite

	if (m_MoveStrategy)
		m_MoveStrategy->move(*this);

	if (m_FSM)
		m_FSM->update(*this);

	if (m_CollideMap)
		m_CollideMap->update(*this, level);

	position = Vector2Add(position, Vector2Scale(Vector2{m_velocity.x, m_velocity.y}, GetFrameTime()));

	if (m_sprite)
		m_sprite->update(*this);

	rect.x = position.x; // most stupid fck i have ever seen
	rect.y = position.y;

	setHurtBox(rect);
	setHitBox({rect.x, rect.y, m_HurtBox.width, m_HurtBox.height});
	setSpriteBox({position.x, position.y, m_SpriteBox.width / SCALE, m_SpriteBox.height / SCALE});
}

void Enemy::Draw()
{
	m_sprite->draw(*this);
	DrawRectangleLines(m_HurtBox.x, m_HurtBox.y, m_HurtBox.width, m_HurtBox.height, RED);
	DrawRectangleLines(m_HitBox.x, m_HitBox.y, m_HitBox.width, m_HitBox.height, GREEN);
}

void Enemy::setMoveStrategy(IMoveStrategy *strategy)
{
	delete m_MoveStrategy;
	m_MoveStrategy = strategy;
}
// void Enemy::setAttackStrategy(IAttackStrategy* strategy)
//{
//	m_AttackStrategy = strategy;
// }
void Enemy::setCollisionMap(CollisionMap *collidemap)
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
void Enemy::addVelocityX(float X)
{
	m_velocity.x += X;
}
Vector2 &Enemy::getVelocity()
{
	return m_velocity;
}

int Enemy::getDirectionSelf() const
{
	if (m_velocity.x <= 0)
	{
		return 1;
	}
	else
		return -1;
}
void Enemy::reverseDirection()
{
	m_velocity.x *= -1;
}

Rectangle &Enemy::getHurtBox()
{
	return m_HurtBox;
}
void Enemy::setHurtBox(Rectangle recta)
{
	// m_HurtBox.x = rect.x;
	// m_HurtBox.y = rect.y;
	// m_HurtBox.width = rect.width * SCALE;
	// m_HurtBox.height = rect.height * SCALE;

	m_HurtBox.x = recta.x;
	m_HurtBox.y = recta.y;
	m_HurtBox.width = recta.width * SCALE;
	m_HurtBox.height = recta.height * SCALE;
}

Rectangle &Enemy::getHitBox()
{
	return m_HitBox;
}
void Enemy::setHitBox(Rectangle rectan)
{
	// float offset = 5;
	// m_HitBox.x = rect.x - offset;
	// m_HitBox.y = rect.y + offset;
	// m_HitBox.width = m_HurtBox.width + 2 * offset;
	// m_HitBox.height = m_HurtBox.height - offset;

	float offset = 5;
	m_HitBox.x = rectan.x - offset;
	m_HitBox.y = rectan.y + offset;
	m_HitBox.width = rectan.width + 2 * offset;
	m_HitBox.height = rectan.height - offset;
}

Rectangle &Enemy::getSpriteBox()
{
	return m_SpriteBox;
}
void Enemy::setSpriteBox(Rectangle rectan)
{
	m_SpriteBox.x = rectan.x;
	m_SpriteBox.y = rectan.y;
	m_SpriteBox.width = rectan.width * SCALE;
	m_SpriteBox.height = rectan.height * SCALE;
}

void Enemy::setIsCollidedMap()
{
	m_isCollidedMap = true;
}
bool Enemy::getIsCollidedMap()
{
	bool result = m_isCollidedMap;
	if (result)
	{
		m_isCollidedMap = false;
	}
	return result;
}

void Enemy::setPosition(Vector2 pos)
{
	position = pos;
}

void Enemy::onDefeated()
{
	if (m_playingStateRef)
	{
		m_playingStateRef->reportEnemyKill(this->GetPosition());
	}
}
//Vector2 Enemy::getPositon() const
void Enemy::SwitchNoHurtBox()
{
	m_hasNoHurtBox = !m_hasNoHurtBox;
}
bool Enemy::CheckHasNoHurtBox()
{
	return m_hasNoHurtBox;
}

void Enemy::SwitchNoHitBox()
{
	m_hasNoHitBox = !m_hasNoHitBox;
}
bool Enemy::CheckHasNoHitBox()
{
	return m_hasNoHitBox;
}

void Enemy::isDead()
{
	m_isDead = true;
}
bool Enemy::CheckIsDead()
{
	return m_isDead;
}
// Vector2 Enemy::getPositon() const
//{
//	return position;
// }
// void Enemy::setCollisionPlayerStrategy(ICollisionPlayerStrategy* strategy)
//{
//	delete m_CollidePlayerStrategy;
//	m_CollidePlayerStrategy = strategy;
// }
