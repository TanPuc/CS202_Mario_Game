#pragma once

#include "raylib.h"
#include "raymath.h"

#include "enemyEnum.h"
#include "Entity.h"

class Enemy;

class EnemyState;
class FiniteStateMachine;

class IMoveStrategy;
class IAttackStrategy;
class ICollisionMapStrategy;
class CollisionMap;

class SpriteEnemy;

//context
class Enemy : public Entity
{
public:
	Enemy(EnemyType type, FiniteStateMachine* fsm, SpriteEnemy* sprite, Vector2 size, Vector2 positon);
	~Enemy();

	bool isActive() const;
	void UnActivate();

	void setMoveStrategy(IMoveStrategy*);
	void setCollisionMap(CollisionMap*);
	//void setAttackStrategy(IAttackStrategy*);
	//void setCollisionPlayerStrategy(ICollisionPlayerStrategy*);
	//void setState(EnemyState*);

	void setSprite(StateType);

	void handleInput(int input);
	void Update(Level& level) override;
	void Draw() override;

	void destroy();

	void setVelocityX(float X);
	void setVelocityY(float Y);
	void addVelocityY(float Y);
	Vector2 getVelocity() const;

	int getDirectionSelf() const;
	void reverseDirection();
	int getDirectionPlayer() const;

	void setPosition(Vector2);

	Rectangle getHurtBox() const;
	void setHurtBox();

	Rectangle getHitBox() const;
	void setHitBox();		

	void setIsCollidedMap();
	bool getIsCollidedMap();


	void ResolveCollision(Entity& other) override;
	void ResolveCollision(Level& level) override;

private:
	EnemyType					m_Type					;
	bool						m_isActive				= true;

	Vector2						m_velocity				= { 0,0 };
	int							m_initialDirection		= 1;

	Rectangle					m_HitBox				= {};  //bound is ratio
	Rectangle					m_HurtBox				= {};

	FiniteStateMachine*			m_FSM					= nullptr;
	
	IMoveStrategy*				m_MoveStrategy			= nullptr;
	CollisionMap*				m_CollideMap			= nullptr;

	SpriteEnemy*				m_sprite				= nullptr;

	bool						m_isCollidedMap			= false;


	//IAttackStrategy*			m_AttackStrategy		= nullptr;
	//ICollisionMapStrategy*	m_CollideMapStrategy	= nullptr;
	//Vector2					m_position				= { 0,0 };
	//EnemyState*				m_State					= nullptr;
	//ICollisionPlayerStrategy*	m_CollidePlayerStrategy = nullptr;
};




/*
class Monster : public Enemy
{
public:
	Monster();
	~Monster();

private:
	bool isActive;
};



class Shell : public Monster
{
public:
	Shell();
	~Shell();

private:

};

class Paratroopa : public Shell
{
public:
	Paratroopa();
	~Paratroopa();

private:

};

class BuzzyBettle : public Shell
{
public:
	BuzzyBettle();
	~BuzzyBettle();

private:

};

class Koopa : public Shell
{
public:
	Koopa();
	~Koopa();

private:

};

class Goopa : public Enemy
{
public:
	Goopa();
	~Goopa();

	void Update() override;
private:
};

class Hammer : public Enemy
{
public:
	Hammer();
	~Hammer();

private:

};

class HammerBro : public Hammer
{
public:
	HammerBro();
	~HammerBro();

private:

};

class Bowser : public Hammer
{
public:
	Bowser();
	~Bowser();

private:

};

class Blooper
{
public:
	Blooper();
	~Blooper();

private:

};

class CheepCheep
{
public:
	CheepCheep();
	~CheepCheep();

private:

};

class Lakitu
{
public:
	Lakitu();
	~Lakitu();

private:

};

class Spiny
{
public:
	Spiny();
	~Spiny();

private:

};

class PiranhaPlant
{
public:
	PiranhaPlant();
	~PiranhaPlant();

private:

};

//
class Trap : public Enemy
{
public:
	Trap();
	~Trap();

private:

};


class FireBar : public Trap
{
public:
	FireBar();
	~FireBar();

private:

};

class LavaBubble : public Trap
{
public:
	LavaBubble();
	~LavaBubble();

private:

};

class BullerBill : public Trap
{
public:
	BullerBill();
	~BullerBill();

private:

};
*/