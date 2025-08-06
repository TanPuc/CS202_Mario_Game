#include "enemy.h"
#include "enemyState.h"
#include "enemyMoveStrategy.h"
#include "enemyAttackStrategy.h"
#include "enemyCollisionStrategy.h"
#include "enemyEnum.h"


//
//void AliveState::handleInput(Enemy& e, int input)
//{
//	if (input == 0)
//	{
//		e.setState(new DeadState());
//	}
//}
//void AliveState::enter(Enemy& e)
//{
//	e.setStrategy(new MoveStrategyBasic(,e));
//}

//void WalkState::enter(Enemy& e)
//{
//	e.setAttackStrategy(new AttackNothing());
//	CollisionStrategyCombined* compositeCollide = new CollisionStrategyCombined();
//	compositeCollide->addStrategy(new CollisionStrategyFloorWalk());
//	compositeCollide->addStrategy(new CollisionStrategyWallReverseDirection());
//	compositeCollide->addStrategy(new CollisionStrategyPlayerStomp());
//	e.setCollisionStrategy(compositeCollide);
//	MoveStrategyCombined* compositeMove = new MoveStrategyCombined();
//	compositeMove->addStrategy(new MoveStrategyBasic(placeholder), e));
//	compositeMove->addStrategy(new MoveStrategyFall(gra));
//	e.setMoveStrategy(compositeMove);
//}
//
//void HammerBroState::enter(Enemy& e)
//{
//	CollisionStrategyCombined* compositeCollide = new CollisionStrategyCombined();
//	compositeCollide->addStrategy(new CollisionStrategyFloorWalk());
//	compositeCollide->addStrategy(new CollisionStrategyPlayerStomp());
//	e.setCollisionStrategy(compositeCollide);
//	e.setMoveStrategy(new MoveStrategyRandom( placeholder , placeholder));
//}
//void BowserState::enter(Enemy& e)
//{
//	CollisionStrategyCombined* compositeCollide = new CollisionStrategyCombined();
//	compositeCollide->addStrategy(new CollisionStrategyFloorWalk());
//	e.setCollisionStrategy(compositeCollide);
//	MoveStrategyCombined* compositeMove = new MoveStrategyCombined();
//	compositeMove->addStrategy(new MoveStrategyBasic(placeholder, e));
//	compositeMove->addStrategy(new MoveStrategyFall(gra));
//	e.setMoveStrategy(compositeMove);
//}
//
//void LakituState::enter(Enemy& e)
//{
//
//}
//
//void SpinyFallState::enter(Enemy& e)
//{
//
//}
//
//void PiranhaState::enter(Enemy& e)
//{
//
//}
//
//void CheepCheepState::enter(Enemy& e)
//{
//
//}
//
//void ParaTrooperState::enter(Enemy& e)
//{
//
//}
//void KoopaState::enter(Enemy& e)
//{
//
//}
//void BuzzyBettleState::enter(Enemy& e)
//{
//
//}
//void ShellState::enter(Enemy& e)
//{
//
//}
//void ShellSlidingState::enter(Enemy& e)
//{
//
//}
//
//void BlooperChaseState::enter(Enemy& e)
//{
//	e.setAttackStrategy(new AttackNothing());
//	e.setCollisionStrategy(new CollisionStrategyNothing());
//	e.setMoveStrategy(new MoveStrategyChase(placeholder,));
//}
//void BlooperFallState::enter(Enemy& e)
//{
//	e.setAttackStrategy(new AttackNothing());
//	e.setCollisionStrategy(new CollisionStrategyNothing());
//	e.setMoveStrategy(new MoveStrategyFall(gra));
//}
//
//void HammerState::enter(Enemy& e)
//{
//
//}
//void FireBallState::enter(Enemy& e)
//{
//
//}
//void LavaBubbleState::enter(Enemy& e)
//{
//
//}
//void BulletBillState::enter(Enemy& e)
//{
//
//}

WalkState::WalkState(int speed, float gravity,bool isSwimming, bool isFireImmune):
	m_isSwimming(isSwimming), m_speed(speed), m_gravity(gravity), m_isFireImmune(isFireImmune) {}
void WalkState::enter(Enemy& e)
{
	e.setAttackStrategy(new AttackNothing());
	CollisionStrategyCombined* compoCol = new CollisionStrategyCombined();
	compoCol->addStrategy(new CollisionStrategyFloorWalk());
	compoCol->addStrategy(new CollisionStrategyWallReverseDirection());
	if (!m_isSwimming) compoCol->addStrategy(new CollisionStrategyPlayerStomp());
	if (!m_isFireImmune) compoCol->addStrategy(new CollisionStrategyFireBall());
	e.setCollisionStrategy(compoCol);
	MoveStrategyCombined* compoMove = new MoveStrategyCombined();
	compoMove->addStrategy(new MoveStrategyBasic(m_speed,e));
	if(!m_isSwimming) compoMove->addStrategy(new MoveStrategyFall(m_gravity));
	e.setMoveStrategy(compoMove);
}
StateType WalkState::getName() const
{
	return StateType::Walk;
}

HoverState::HoverState(int speedRandom, int speedDistace):
	m_speedDistance(speedDistace),m_speedRandom(speedRandom) {}
void HoverState::enter(Enemy& e)
{
	e.setAttackStrategy(new AttackNothing());
	CollisionStrategyCombined* compoCol = new CollisionStrategyCombined();
	compoCol->addStrategy(new CollisionStrategyFireBall());
	compoCol->addStrategy(new CollisionStrategyPlayerStomp());
	e.setCollisionStrategy(compoCol);
	MoveStrategyCombined* compoMove = new MoveStrategyCombined();
	compoMove->addStrategy(new MoveStrategyRandom(m_speedRandom, , ));
	compoMove->addStrategy(new MoveStrategyKeepDistance(m_speedDistance,  ,));
	e.setMoveStrategy(compoMove);
}

AttackState::AttackState(EnemyManager* manager, IAttackStrategy* attack):
	m_manager(manager), m_attack(attack) {}
void AttackState::enter(Enemy& e)
{
	e.setAttackStrategy(m_attack);
}
void AttackState::exit(Enemy& e)
{
	e.setAttackStrategy(new AttackNothing());
}

FallState::FallState(float gravity):
	m_gravity(gravity), EnemyState(StateType::Fall) {}
void FallState::enter(Enemy& e)
{
	e.setAttackStrategy(new AttackNothing());
	e.setMoveStrategy(new MoveStrategyFall(m_gravity));
}

void PiranhaState::enter(Enemy& e)
{
	e.setAttackStrategy(new AttackNothing());
	e.setMoveStrategy(new MoveStrategySwayUpDown(m_magnitude, m_frequency));
}

void HopState::enter(Enemy& e)
{
	e.setAttackStrategy(new AttackNothing());
	MoveStrategyCombined* compoMove = new MoveStrategyCombined();
	compoMove->addStrategy(new MoveStrategyBasic(m_speed, e));
	compoMove->addStrategy(new MoveStrategyFall(m_gravity));
	e.setMoveStrategy(compoMove);
}

void ShellState::enter(Enemy& e)
{
	e.setAttackStrategy(new AttackNothing());
	MoveStrategyCombined* compoMove = new MoveStrategyCombined();
	compoMove->addStrategy(new MoveStrategyBasic(0, e));
	compoMove->addStrategy(new MoveStrategyFall(m_gravity));
	e.setMoveStrategy(compoMove);
}
StateType ShellState::getName() const
{
	return StateType::Shell;
}

void ShellSlidingState::enter(Enemy& e)
{
	e.setAttackStrategy(new AttackNothing());
	MoveStrategyCombined* compoMove = new MoveStrategyCombined();
	compoMove->addStrategy(new MoveStrategyBasic(m_speed, e));
	compoMove->addStrategy(new MoveStrategyFall(m_gravity));
	e.setMoveStrategy(compoMove);
}

void ChaseState::enter(Enemy& e)
{
	e.setAttackStrategy(new AttackNothing());
	e.setMoveStrategy(new MoveStrategyChase(m_speed, play);
}

void DeadStateStomp::enter(Enemy& e)
{
	e.setAttackStrategy(new AttackNothing());
	e.setMoveStrategy(new MoveStrategyBasic(0,e));
}
void DeadStateElse::enter(Enemy& e)
{
	e.setAttackStrategy(new AttackNothing());
	e.setMoveStrategy(new MoveStrategyFall(gra));
}