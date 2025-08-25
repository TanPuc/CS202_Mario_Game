#include "Enemy/enemy.h"
#include "Enemy/enemyState.h"
#include "Enemy/enemyMoveStrategy.h"
#include "Enemy/enemyAttackStrategy.h"
#include "Enemy/enemyCollisionPlayer.h"
#include "Enemy/enemyCollisionMap.h"
#include "Enemy/enemyEnum.h"
#include "Enemy/enemySprite.h"
#include "Enemy/enemyManager.h"

#include "Character.h"

WalkState::WalkState(int speed, float gravity):
	m_speed(speed), m_gravity(gravity) , m_mario(nullptr){
}
WalkState::WalkState(int speed, float gravity, Character* mario) :
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
void WalkOnLedgeState::enter(Enemy& e)
{
	WalkState::enter(e);
	//e.setCollisionMap(new CollisionMap(new CollisionStrategyXReverse(),new CollisionStrategyXReverseLedge()));
	e.setCollisionMap(new CollisionMap(new CollisionStrategyXReverse(), nullptr));
}
void WalkState::exit(Enemy& e) {}
void WalkState::update(Enemy& e) {}
StateType WalkState::getName() const
{
	return StateType::Walk;
}

SwimState::SwimState(float speed, float freq, float magni, Character* mario) :
	m_speed(speed), m_frequency(freq), m_magnitude(magni), m_player(mario) {}
void SwimState::enter(Enemy& e)
{
	MoveStrategyCombined* compoMove = new MoveStrategyCombined();
	if (m_player) compoMove->addStrategy(new MoveStrategyBasic(m_speed, e, *m_player));
	else compoMove->addStrategy(new MoveStrategyBasic(m_speed, e));
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

HoverState::HoverState(float speedRandom, float boundary, float speedDistace, Vector2 offset, Character* player):
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

AttackState::AttackState(EnemyManager* manager, AttackStrat* attack) :
	m_manager(manager), m_attack(attack) {}
AttackState::AttackState(EnemyManager* manager, AttackStrat* attack, int amount, float durat) :
	m_manager(manager), m_attack(attack), m_amout(amount) , duration(durat){}
AttackState::~AttackState() { delete m_attack; }
void AttackState::enter(Enemy& e)
{
	//e.setAttackStrategy(m_attack);

	e.setSprite(getName());
}
void AttackState::exit(Enemy& e)
{	
	m_attack->attack(e);
	counter = 1;
	timer = 0;
	//e.setAttackStrategy(nullptr);
}
void AttackState::update(Enemy& e)
{
	timer += GetFrameTime();
	if (timer <= threshold) return;

	//m_attack->attack(e);
	
	timer2 += GetFrameTime();

	if (timer2 >= duration / m_amout && counter < m_amout )
	{
		m_attack->attack(e);
		counter++;
		timer2 = 0;
	}

	//float times = threshold + duration / m_amout * counter;
	//if (timer  >= times)
	//{
	//	m_attack->attack(e);
	//	counter++;
	//}
}
StateType AttackState::getName() const
{
	return StateType::Attack;
}

AttackOffState::AttackOffState(EnemyManager* manager, AttackStrat* attack) :
	m_manager(manager), m_attack(attack){}
void AttackOffState::enter(Enemy& e)
{
	e.setSprite(getName());
}
void AttackOffState::exit(Enemy& e)
{
	m_attack->attack(e);
}
void AttackOffState::update(Enemy& e)
{

}
StateType AttackOffState::getName() const
{
	return StateType::attackOff;
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

	CollisionMapStrategyCombined* CombinedCollisionStrategy = new CollisionMapStrategyCombined();
	CombinedCollisionStrategy->addStrategy(new CollisionStrategyXReverse());
	CombinedCollisionStrategy->addStrategy(new CollisionStrategyYJump(m_power));
	e.setCollisionMap(new CollisionMap(CombinedCollisionStrategy, nullptr));

	e.setSprite(getName());
}
void HopState::exit(Enemy& e) {}
void HopState::update(Enemy& e) {}
StateType HopState::getName() const
{
	return StateType::Hop;
}

ShellState::ShellState(float gravity):
	m_gravity(gravity)  {}
void ShellState::enter(Enemy& e)
{
	MoveStrategyCombined* compoMove = new MoveStrategyCombined();
	compoMove->addStrategy(new MoveStrategyBasic(0, e));
	compoMove->addStrategy(new MoveStrategyFall(m_gravity));
	e.setMoveStrategy(compoMove);

	e.rect.width = 16;
	e.rect.height = 16;
	e.setSpriteBox({e.GetPosition().x,e.GetPosition().y,16,16});

	e.setSprite(getName());
}
void ShellState::exit(Enemy& e) {}
void ShellState::update(Enemy& e) {}
StateType ShellState::getName() const
{
	return StateType::Shell;
}

ShellSlidingState::ShellSlidingState(float speed, float gravity, const Character& mario, EnemyManager* manager) :
	m_speed(speed), m_gravity(gravity), m_player(mario), m_manager(manager) {}
void ShellSlidingState::enter(Enemy& e)
{
	m_manager->addShell(&e);
	e.SwitchNoHitBox();

	MoveStrategyCombined* compoMove = new MoveStrategyCombined();
	compoMove->addStrategy(new MoveStrategyBasic(-m_speed, e, m_player));
	compoMove->addStrategy(new MoveStrategyFall(m_gravity));
	e.setMoveStrategy(compoMove);

	e.setCollisionMap(new CollisionMap(new CollisionStrategyXReverse(), nullptr));

	e.setSprite(getName());
}
void ShellSlidingState::exit(Enemy& e) {
	m_manager->removeShell(&e);
	e.SwitchNoHitBox();
}
void ShellSlidingState::update(Enemy& e) {}
StateType ShellSlidingState::getName() const
{
	return StateType::ShellSlide;
}

ChaseState::ChaseState(float speed, Character* player) :
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

PatrolState::PatrolState(float boundary, float speed, float JumpPower, float timer) :
	m_boundary(boundary), m_speed(speed), m_JumpPower(JumpPower), m_threshold(timer) {}
void PatrolState::enter(Enemy& e)
{
	if (!m_mark && (e.GetPosition() != Vector2{0,0})) m_mark = new Vector2(e.GetPosition());
	MoveStrategyCombined* combined = new MoveStrategyCombined();
	combined->addStrategy(new MoveStrategyRandom(m_boundary, m_speed, m_mark));
	combined->addStrategy(new MoveStrategyFall(GRAVITY));
	e.setMoveStrategy(combined);

	e.setCollisionMap(new CollisionMap(nullptr, nullptr));

	e.setSprite(getName());
}
void PatrolState::exit(Enemy& enemy)
{

}
void PatrolState::update(Enemy& enemy)
{
	timer += GetFrameTime();
	if (timer >= m_threshold)
	{
		timer = 0;
		enemy.addVelocityY(-m_JumpPower);
	}
}
StateType PatrolState::getName() const
{
	return StateType::Patrol;
}

void DeadStateStomp::enter(Enemy& e)
{
	e.isDead();
	e.setMoveStrategy(new MoveStrategyBasic(0,e));

	e.rect = { 0,0,0,0 };

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
	e.isDead();
	e.setVelocityX(0);
	e.setVelocityY(-100);
	e.setMoveStrategy(new MoveStrategyFall(m_gravity));

	e.rect = {0,0,0,0};

	e.setCollisionMap(nullptr);

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