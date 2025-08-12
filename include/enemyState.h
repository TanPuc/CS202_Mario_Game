#pragma once

#include "enemyEnum.h"
#include "raylib.h"

class Enemy;

class EnemyStateChangeStrategy;
class IAttackStrategy;
class EnemyManager;

class Mario;

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
	WalkState(int speed, float gravity);
	void enter(Enemy& e) override;
	void exit(Enemy& enemy) override;
	void update(Enemy& enemy) override;
	StateType getName() const override;
private:
	float	m_speed;
	float	m_gravity;
};
class SwimState : public EnemyState
{
public:
	SwimState(float speed, float freq, float magnitude);
	void enter(Enemy& e) override;
	void exit(Enemy& enemy) override;
	void update(Enemy& enemy) override;
	StateType getName() const override;
private:
	float	m_speed;
	float m_frequency;
	float m_magnitude;
};

class HoverState : public EnemyState
{
public:
	HoverState(float speedRandom,float boundary, float speedDistance, Vector2 offset, Mario* player);
	void enter(Enemy& e) override;
	void exit(Enemy& enemy) override;
	void update(Enemy& enemy) override;
	StateType getName() const override;
private:
	float m_speedRandom, m_boundary;
	float m_speedDistance;
	Vector2 m_offset;
	Mario* m_player;
};
class AttackState : public EnemyState
{
public:
	AttackState(EnemyManager*, IAttackStrategy*);
	void enter(Enemy& e) override;
	void exit(Enemy& enemy) override;
	void update(Enemy& enemy) override;
	StateType getName() const override;
private:
	EnemyManager* m_manager;
	int m_direction = 1;
	IAttackStrategy* m_attack;
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
	ShellSlidingState(float, float);
	void enter(Enemy& e) override;
	void exit(Enemy& enemy) override;
	void update(Enemy& enemy) override;
	StateType getName() const override;
private:
	float m_speed, m_gravity;
};

class ChaseState : public EnemyState
{
public:
	ChaseState(float speed, Mario* player);
	void enter(Enemy& e) override;
	void exit(Enemy& enemy) override;
	void update(Enemy& enemy) override;
	StateType getName() const override;
private:
	float m_speed;
	Mario* m_player;
};

class DeadStateStomp : public EnemyState
{
public:
	void enter(Enemy& e) override;
	void exit(Enemy& enemy) override;
	void update(Enemy& enemy) override;
	StateType getName() const override;
private:
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