#pragma once

#include "raylib.h"
#include "raymath.h"

#include "enemyEnum.h"

class Enemy;

//state
//class EnemyState
//{
//public:
//
//	virtual void enter(Enemy& enemy) = 0;
//	virtual void exit(Enemy& enemy) = 0;
//	virtual void update(Enemy& enemy) = 0;
//private:
//
//};
//
//class AliveState : public EnemyState
//{
//public:
//
//	void enter(Enemy& e) override;
//	void exit(Enemy& enemy) override;
//	void update(Enemy& enemy) override;
//private:
//};
//
//class DeadState : public EnemyState
//{
//public:
//
//	void enter(Enemy& e) override;
//	void exit(Enemy& enemy) override;
//	void update(Enemy& enemy) override;
//private:
//};
class EnemyState;
class FiniteStateMachine;

//strategy
//class IMoveStrategy
//{
//public:
//
//	virtual void move(Enemy& e) = 0;
//private:
//
//};
//
//class MoveStrategyBasic : public IMoveStrategy
//{
//public:
//	void move(Enemy& e) override;
//};
//
//class SwayMoveStrategy : public IMoveStrategy
//{
//public:
//	void move(Enemy& e) override;
//};
//
//class MoveStrategyKeepDistance : public IMoveStrategy
//{
//public:
//	void move(Enemy& e) override;
//};
//
//class MoveStrategyChase : public IMoveStrategy
//{
//public :
//	void move(Enemy& e) override;
//};
//
//class DeadMoveStrategy : public IMoveStrategy
//{
//public:
//	void move(Enemy& e) override;
//};
class IMoveStrategy;
class IAttackStrategy;
class ICollisionMapStrategy;
class ICollisionPlayerStrategy;

//context
class Enemy
{
public:
	Enemy(EnemyType type, FiniteStateMachine* fsm);
	~Enemy();

	void setMoveStrategy(IMoveStrategy*);
	void setAttackStrategy(IAttackStrategy*);
	void setCollisionMapStrategy(ICollisionMapStrategy*);
	void setCollisionPlayerStrategy(ICollisionPlayerStrategy*);
	//void setState(EnemyState*);

	void handleInput(int input);
	void update();

	void destroy();

	void setVelocityX(float X);
	void setVelocityY(float Y);
	void addVelocityY(float Y);

	Vector2 getPositon() const;
	void setPosition(Vector2);

private:
	EnemyType					m_Type					;

	Vector2						m_position				= { 0,0 };
	Vector2						m_velocity				= { 0,0 };

	Rectangle					m_hitbox				= {};

	//EnemyState*				m_State					= nullptr;
	FiniteStateMachine*			m_FSM					= nullptr;
	
	IMoveStrategy*				m_MoveStrategy			= nullptr;
	IAttackStrategy*			m_AttackStrategy		= nullptr;
	ICollisionMapStrategy*		m_CollideMapStrategy	= nullptr;
	ICollisionPlayerStrategy*	m_CollidePlayerStrategy = nullptr;
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