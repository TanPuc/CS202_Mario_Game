#include "Enemy/enemy.h"
#include "Enemy/enemyState.h"
#include "Enemy/enemyMoveStrategy.h"
#include "Enemy/enemyAttackStrategy.h"
#include "Enemy/enemyCollisionPlayer.h"
#include "Enemy/enemyCollisionMap.h"
#include "Enemy/enemyEnum.h"
#include "Enemy/enemySprite.h"

#include "Mario.h"
WalkState::WalkState(int speed, float gravity):
	m_speed(speed), m_gravity(gravity) , m_mario(nullptr){
}
WalkState::WalkState(int speed, float gravity, Mario* mario) :
	m_speed(speed), m_gravity(gravity), m_mario(mario) {
}
void WalkState::enter(Enemy& e)
{
	e.setCollisionMap(new CollisionMap(new CollisionStrategyXReverse(), nullptr));

	MoveStrategyCombined* compoMove = new MoveStrategyCombined();
	if(m_mario) compoMove->addStrategy(new MoveStrategyBasic(m_speed,e, *m_mario));
	else compoMove->addStrategy(new MoveStrategyBasic(m_speed, e));
	compoMove->addStrategy(new MoveStrategyFall(m_gravity));
	e.setMoveStrategy(compoMove);

	e.setSprite(getName());
}
void WalkState::exit(Enemy& e) {}
void WalkState::update(Enemy& e) {}
StateType WalkState::getName() const
{
	return StateType::Walk;
}

SwimState::SwimState(float speed, float freq, float magni) :
	m_speed(speed), m_frequency(freq), m_magnitude(magni) {}
void SwimState::enter(Enemy& e)
{
	MoveStrategyCombined* compoMove = new MoveStrategyCombined();
	compoMove->addStrategy(new MoveStrategyBasic(m_speed, e));
	compoMove->addStrategy(new MoveStrategySwayUpDown(m_magnitude, m_frequency));
	e.setMoveStrategy(compoMove);

	e.setSprite(getName());
}
void SwimState::exit(Enemy& e) {}
void SwimState::update(Enemy& e) {}
StateType SwimState::getName() const
{
	return StateType::Swim;
}

HoverState::HoverState(float speedRandom, float boundary, float speedDistace, Vector2 offset, Mario* player):
	m_speedDistance(speedDistace),m_boundary(boundary), m_speedRandom(speedRandom),m_offset(offset), m_player(player) {}
void HoverState::enter(Enemy& e)
{
	MoveStrategyCombined* compoMove = new MoveStrategyCombined();
	compoMove->addStrategy(new MoveStrategyRandom(m_boundary, m_speedRandom, &m_player->position));
	compoMove->addStrategy(new MoveStrategyKeepDistance(m_speedDistance, m_offset , m_player));
	e.setMoveStrategy(compoMove);

	e.setSprite(getName());
}
void HoverState::exit(Enemy& e) {}
void HoverState::update(Enemy& e) {}
StateType HoverState::getName() const
{
	return StateType::Hover;
}

AttackState::AttackState(EnemyManager* manager, IAttackStrategy* attack, int number):
	m_manager(manager), m_attack(attack), m_amount(number) {}
AttackState::AttackState(EnemyManager* manager, IAttackStrategy* attack) :
	m_manager(manager), m_attack(attack) {}
AttackState::~AttackState() { delete m_attack; }
void AttackState::enter(Enemy& e)
{
	//e.setAttackStrategy(m_attack);

	e.setSprite(getName());
}
void AttackState::exit(Enemy& e)
{	
	m_attack->attack(e);

	while (m_counter < m_amount)
	{
		timer += GetFrameTime();
		if (timer >= threshold)
		{
			m_attack->attack(e);
			timer = 0;
			m_counter++;
		}
	}
	//e.setAttackStrategy(nullptr);
}
void AttackState::update(Enemy& e)
{

}
StateType AttackState::getName() const
{
	return StateType::Attack;
}

FallState::FallState(float gravity):
	m_gravity(gravity) {}
void FallState::enter(Enemy& e)
{
	e.setVelocityX(0);
	e.setMoveStrategy(new MoveStrategyFall(m_gravity));

	e.setSprite(getName());
}
void FallState::exit(Enemy& e) {}
void FallState::update(Enemy& e) {}
StateType FallState::getName() const
{
	return StateType::Fall;
}

PiranhaState::PiranhaState(float boundary, float frequency):
	m_magnitude(boundary), m_frequency(frequency) {}
void PiranhaState::enter(Enemy& e)
{
	e.setMoveStrategy(new MoveStrategySwayUpDown(m_magnitude, m_frequency));

	e.setSprite(getName());
}
void PiranhaState::exit(Enemy& e) {}
void PiranhaState::update(Enemy& e) {}
StateType PiranhaState::getName() const
{
	return StateType::Piranha;
}

HopState::HopState(float power, float speed, float gravity):
	m_power(power), m_speed(speed), m_gravity(gravity)
{}
void HopState::enter(Enemy& e)
{
	MoveStrategyCombined* compoMove = new MoveStrategyCombined();
	compoMove->addStrategy(new MoveStrategyBasic(m_speed, e));
	compoMove->addStrategy(new MoveStrategyFall(m_gravity));
	e.setMoveStrategy(compoMove);

	e.setCollisionMap(new CollisionMap(new CollisionStrategyXReverse(),new CollisionStrategyYJump(m_power)));

	e.setSprite(getName());
}
void HopState::exit(Enemy& e) {}
void HopState::update(Enemy& e) {}
StateType HopState::getName() const
{
	return StateType::Hop;
}

ShellState::ShellState(float gravity):
	m_gravity(gravity) {}
void ShellState::enter(Enemy& e)
{
	MoveStrategyCombined* compoMove = new MoveStrategyCombined();
	compoMove->addStrategy(new MoveStrategyBasic(0, e));
	compoMove->addStrategy(new MoveStrategyFall(m_gravity));
	e.setMoveStrategy(compoMove);

	e.rect.width = 16;
	e.rect.height = 16;

	e.setSprite(getName());
}
void ShellState::exit(Enemy& e) {}
void ShellState::update(Enemy& e) {}
StateType ShellState::getName() const
{
	return StateType::Shell;
}

ShellSlidingState::ShellSlidingState(float speed, float gravity, const Mario& mario) :
	m_speed(speed), m_gravity(gravity), m_player(mario) {}
void ShellSlidingState::enter(Enemy& e)
{
	MoveStrategyCombined* compoMove = new MoveStrategyCombined();
	compoMove->addStrategy(new MoveStrategyBasic(-m_speed, e, m_player));
	compoMove->addStrategy(new MoveStrategyFall(m_gravity));
	e.setMoveStrategy(compoMove);

	e.setSprite(getName());
}
void ShellSlidingState::exit(Enemy& e) {}
void ShellSlidingState::update(Enemy& e) {}
StateType ShellSlidingState::getName() const
{
	return StateType::ShellSlide;
}

ChaseState::ChaseState(float speed, Mario* player) :
	m_speed(speed), m_player(player) {}
void ChaseState::enter(Enemy& e)
{
	e.setMoveStrategy(new MoveStrategyChase(m_speed, m_player, e));

	e.setSprite(getName());
}
void ChaseState::exit(Enemy& e) {
	e.setVelocityX(0);
	e.setVelocityY(0);
}
void ChaseState::update(Enemy& e) {}
StateType ChaseState::getName() const
{
	return StateType::Chase;
}

PatrolState::PatrolState(float boundary, float speed) :
	m_boundary(boundary), m_speed(speed) {}
void PatrolState::enter(Enemy& e)
{
	Vector2* mark = new Vector2(e.GetPosition());
	e.setMoveStrategy(new MoveStrategyRandom(m_boundary,m_speed,mark));

	e.setSprite(getName());
}
void PatrolState::exit(Enemy& enemy)
{

}
void PatrolState::update(Enemy& enemy)
{

}
StateType PatrolState::getName() const
{
	return StateType::Patrol;
}

void DeadStateStomp::enter(Enemy& e)
{
	e.setMoveStrategy(new MoveStrategyBasic(0,e));

	e.setSprite(getName());
}
void DeadStateStomp::exit(Enemy& e) {}
void DeadStateStomp::update(Enemy& e) {
	timer += GetFrameTime();

	if (timer >= threshold)
	{
		e.UnActivate();
	}
}
StateType DeadStateStomp::getName() const
{
	return StateType::DeadStomp;
}

DeadStateElse::DeadStateElse(float gravity):
	m_gravity(gravity) {}
void DeadStateElse::enter(Enemy& e)
{
	e.setVelocityX(0);
	e.setVelocityY(-300);
	e.setMoveStrategy(new MoveStrategyFall(m_gravity));

	e.setSprite(getName());
}
void DeadStateElse::exit(Enemy& e) {}
void DeadStateElse::update(Enemy& e) 
{
	timer += GetFrameTime();

	if (timer >= threshold)
	{
		e.UnActivate();
	}
}
StateType DeadStateElse::getName() const
{
	return StateType::DeadElse;
}

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