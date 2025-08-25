#pragma once

#include "enemyEnum.h"
#include "raylib.h"

class Enemy;

class EnemyStateChangeStrategy;
class IAttackStrategy;
class EnemyManager;
class AttackStrat;

class Character;

class EnemyState
{
public:
	virtual void enter(Enemy& enemy) = 0;
	virtual void exit(Enemy& enemy) = 0;
	virtual void update(Enemy& enemy) = 0;
	virtual StateType getName() const = 0;
};

//class AliveState : public EnemyState
//{
//public:
//
//	void enter(Enemy& e) override;
//	void exit(Enemy& enemy) override;
//	void update(Enemy& enemy) override;
//private:
//};

class WalkState : public EnemyState
{
public:
	WalkState(int speed, float gravity, Character* mario);
	WalkState(int speed, float gravity);
	void enter(Enemy& e) override;
	void exit(Enemy& enemy) override;
	void update(Enemy& enemy) override;
	StateType getName() const override;
private:
	float			m_speed;
	float			m_gravity;
	Character*	m_mario;
};
class SwimState : public EnemyState
{
public:
	SwimState(float speed, float freq, float magnitude, Character* mario);
	void enter(Enemy& e) override;
	void exit(Enemy& enemy) override;
	void update(Enemy& enemy) override;
	StateType getName() const override;
private:
	float	m_speed;
	float m_frequency;
	float m_magnitude;
	Character* m_player = nullptr;
};

class HoverState : public EnemyState
{
public:
	HoverState(float speedRandom,float boundary, float speedDistance, Vector2 offset, Character* player);
	void enter(Enemy& e) override;
	void exit(Enemy& enemy) override;
	void update(Enemy& enemy) override;
	StateType getName() const override;
private:
	float m_speedRandom, m_boundary;
	float m_speedDistance;
	Vector2 m_offset;
	Character* m_player;
};



class AttackState : public EnemyState
{
public:
	AttackState(EnemyManager*, AttackStrat*);
	AttackState(EnemyManager*, AttackStrat*, int, float);
	~AttackState();
	void enter(Enemy& e) override;
	void exit(Enemy& enemy) override;
	void update(Enemy& enemy) override;
	StateType getName() const override;
private:
	EnemyManager* m_manager;
	AttackStrat* m_attack;
	int m_amout = 1;
	int counter = 1;
	float threshold = 0.25f;
	float timer = 0;
	float timer2 = 0;
	float duration = 0.5f;

};
class AttackOffState : public EnemyState
{
public:
	AttackOffState(EnemyManager*, AttackStrat*);
	~AttackOffState() { delete m_attack; }
	void enter(Enemy& e) override;
	void exit(Enemy& enemy) override;
	void update(Enemy& enemy) override;
	StateType getName() const override;
private:
	EnemyManager* m_manager = nullptr;
	AttackStrat* m_attack;
};




class FallState : public EnemyState
{
public:
	FallState(float grav);
	void enter(Enemy& e) override;
	void exit(Enemy& enemy) override;
	void update(Enemy& enemy) override;
	StateType getName() const override;
private:
	float m_gravity;
};

class PiranhaState : public EnemyState
{
public:
	PiranhaState(float magni, float freq);
	void enter(Enemy& e) override;
	void exit(Enemy& enemy) override;
	void update(Enemy& enemy) override;
	StateType getName() const override;
private:
	float m_magnitude, m_frequency;
};

class HopState : public EnemyState
{
public:
	HopState(float power, float speed, float gravity);
	void enter(Enemy& e) override;
	void exit(Enemy& enemy) override;
	void update(Enemy& enemy) override;
	StateType getName() const override;
private:
	float m_power, m_speed, m_gravity;
};
class ShellState : public EnemyState
{
public:
	ShellState(float gravity);
	void enter(Enemy& e) override;
	void exit(Enemy& enemy) override;
	void update(Enemy& enemy) override;
	StateType getName() const override;
private:
	float m_gravity;
};
class ShellSlidingState : public EnemyState
{
public:
	ShellSlidingState(float speed, float gravity, const Character& );
	void enter(Enemy& e) override;
	void exit(Enemy& enemy) override;
	void update(Enemy& enemy) override;
	StateType getName() const override;
private:
	float m_speed, m_gravity;
	const Character& m_player;
};

class ChaseState : public EnemyState
{
public:
	ChaseState(float speed, Character* player);
	void enter(Enemy& e) override;
	void exit(Enemy& enemy) override;
	void update(Enemy& enemy) override;
	StateType getName() const override;
private:
	float m_speed;
	Character* m_player;
};

class PatrolState : public EnemyState
{
public:
	PatrolState(float boundary, float speed, float jumppower, float timer);
	~PatrolState() { delete m_mark; }
	void enter(Enemy& e) override;
	void exit(Enemy& enemy) override;
	void update(Enemy& enemy) override;
	StateType getName() const override;
private:
	float m_boundary;
	float m_speed;
	float m_JumpPower;
	Vector2* m_mark = nullptr;
	float timer = 0;
	float m_threshold = 3;
};

class DeadStateStomp : public EnemyState
{
public:
	void enter(Enemy& e) override;
	void exit(Enemy& enemy) override;
	void update(Enemy& enemy) override;
	StateType getName() const override;
private:
	float timer = 0;
	float threshold = 1;
};
class DeadStateElse : public EnemyState
{
public:
	DeadStateElse(float);
	void enter(Enemy& e) override;
	void exit(Enemy& enemy) override;
	void update(Enemy& enemy) override;
	StateType getName() const override;
private:
	float m_gravity;
	float timer = 0;
	float threshold = 7;
};


//class WanderState : public EnemyState
//{
//public:
//	void enter(Enemy& e) override;
//	void exit(Enemy& enemy) override;
//	void update(Enemy& enemy) override;
//};
//
//class HammerBroState : public EnemyState
//{
//public:
//	void enter(Enemy& e) override;
//	void exit(Enemy& enemy) override;
//	void update(Enemy& enemy) override;
//};
//class BowserState : public EnemyState
//{
//public:
//	void enter(Enemy& e) override;
//	void exit(Enemy& enemy) override;
//	void update(Enemy& enemy) override;
//};
//
//class LakituState : public EnemyState
//{
//public:
//	void enter(Enemy& e) override;
//	void exit(Enemy& enemy) override;
//	void update(Enemy& enemy) override;
//};
//class SpinyFallState : public EnemyState
//{
//public:
//	void enter(Enemy& e) override;
//	void exit(Enemy& enemy) override;
//	void update(Enemy& enemy) override;
//};
//
//class PiranhaState : public EnemyState
//{
//public:
//	void enter(Enemy& e) override;
//	void exit(Enemy& enemy) override;
//	void update(Enemy& enemy) override;
//};
//
//class CheepCheepState : public EnemyState
//{
//public:
//	void enter(Enemy& e) override;
//	void exit(Enemy& enemy) override;
//	void update(Enemy& enemy) override;
//};
//
//class ParaTrooperState : public EnemyState
//{
//public:
//	void enter(Enemy& e) override;
//	void exit(Enemy& enemy) override;
//	void update(Enemy& enemy) override;
//};
//class KoopaState : public EnemyState
//{
//public:
//	void enter(Enemy& e) override;
//	void exit(Enemy& enemy) override;
//	void update(Enemy& enemy) override;
//};
//class BuzzyBettleState : public EnemyState
//{
//public:
//	void enter(Enemy& e) override;
//	void exit(Enemy& enemy) override;
//	void update(Enemy& enemy) override;
//};
//class ShellState : public EnemyState
//{
//public:
//	void enter(Enemy& e) override;
//	void exit(Enemy& enemy) override;
//	void update(Enemy& enemy) override;
//};
//class ShellSlidingState : public EnemyState
//{
//public:
//	void enter(Enemy& e) override;
//	void exit(Enemy& enemy) override;
//	void update(Enemy& enemy) override;
//};
//
//class BlooperChaseState : public EnemyState
//{
//public:
//	void enter(Enemy& e) override;
//	void exit(Enemy& enemy) override;
//	void update(Enemy& enemy) override;
//};
//class BlooperFallState : public EnemyState
//{
//public:
//	void enter(Enemy& e) override;
//	void exit(Enemy& enemy) override;
//	void update(Enemy& enemy) override;
//};
//
//class HammerState : public EnemyState{
//public:
//	void enter(Enemy& e) override;
//	void exit(Enemy& enemy) override;
//	void update(Enemy& enemy) override;
//};
//class FireBallState : public EnemyState
//{
//public:
//	void enter(Enemy& e) override;
//	void exit(Enemy& enemy) override;
//	void update(Enemy& enemy) override;
//};
//class LavaBubbleState : public EnemyState
//{
//public:
//	void enter(Enemy& e) override;
//	void exit(Enemy& enemy) override;
//	void update(Enemy& enemy) override;
//};
//class BulletBillState : public EnemyState
//{
//public:
//	void enter(Enemy& e) override;
//	void exit(Enemy& enemy) override;
//	void update(Enemy& enemy) override;
//};
//
//class DeadStateStomp : public EnemyState
//{
//public:
//
//	void enter(Enemy& e) override;
//	void exit(Enemy& enemy) override;
//	void update(Enemy& enemy) override;
//private:
//};
//class DeadStateElse : public EnemyState
//{
//public:
//	void enter(Enemy& e) override;
//	void exit(Enemy& enemy) override;
//	void update(Enemy& enemy) override;
//};