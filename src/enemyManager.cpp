#include "enemyManager.h"
#include "enemy.h"
#include "enemyState.h"
#include "enemyAttackStrategy.h"
#include "enemyFSMBuilder.h"
#include "enemyStateTransition.h"
#include "enemyStateCondition.h"
#include "enemyEnum.h"

const float WALKSPEED = 20;
const float SHELLSPEED = 40;
const float RANDOMSPEED = 20;
const float RANDOMBOUNDARY = 200;
const float DISTANCESPEED = 50;
const float CHASESPEED = 30;
const float GRAVITY = 10;
const float GRAVITYPREMIUM = 20;
const float HOPPOWER = 40;

const Vector2 OFFSET = { 500, 600};
Mario* PLAYER;


void EnemyManager::update() {
	for (auto e : m_toSpawn)
	{
		m_enemies.push_back(e);
	}
	m_toSpawn.clear();

	for (auto e : m_enemies)
	{
		e->update();
	}
}

void EnemyManager::spawnEnemyAt(EnemyType type, Vector2 position)
{
	Enemy* e = nullptr;
	e->setPosition(position);
	switch (type)
	{
	case EnemyType::goopa:
	{
		e = spawnGooba();
		break;
	}

	case EnemyType::koopa:
	{
		e = spawnKoopa();
		break;
	}

	/*case EnemyType::spiny:
	{
		e = new Enemy(type, position,new SpinyFallState());
		break;
	}

	case EnemyType::lakitu:
	{
		e = new Enemy(type, position,new LakituState());
		break;
	}

	case EnemyType::paratroopa:
	{
		e = new Enemy(type, position,new ParaTrooperState());
		break;
	}

	case EnemyType::beezybettle:
	{
		e = new Enemy(type, position, new BuzzyBettleState());
		break;
	}

	case EnemyType::cheepcheep:
	{
		e = new Enemy(type, position, new CheepCheepState());
		break;
	}

	case EnemyType::blooper:
	{
		e = new Enemy(type, position, new BlooperFallState());
		break;
	}

	case EnemyType::hammerbro:
	{
		e = new Enemy(type, position, new HammerBroState());
		e->setAttackStrategy(new AttackThrowHammer(this));
		break;
	}

	case EnemyType::bowser:
	{
		e = new Enemy(type, position, new BowserState()); 
		AttackCombined* compositeAttack = new AttackCombined();
		compositeAttack->addStrategy(new AttackThrowHammer(this));
		compositeAttack->addStrategy(new AttackFireBall(this));
		e->setAttackStrategy(compositeAttack);

		break;
	}

	case EnemyType::hammer:
	{
		e = new Enemy(type, position,new HammerState());
		break;
	}*/
	default:
		break;
	}



	m_toSpawn.push_back(e);
}

Enemy* EnemyManager::spawnGooba()
{
	FiniteStateMachine* fsm;
	FSMBuilder			builder;

	fsm = builder
		.addState(new WalkState(WALKSPEED, GRAVITY, false))
		.addState(new DeadStateStomp())
		.addTransition(StateType::Walk, new ConditionCollisionY(), StateType::DeadStomp)
		.setInitialState(StateType::Walk)
		.build();

	return new Enemy(EnemyType::goopa, fsm);
}
Enemy* EnemyManager::spawnKoopa()
{
	FiniteStateMachine* fsm;
	FSMBuilder			builder;

	fsm = builder
		.addState(new WalkState(WALKSPEED, GRAVITY, false))
		.addState(new ShellState(GRAVITY))
		.addState(new ShellSlidingState(SHELLSPEED, GRAVITY))
		.addState(new DeadStateStomp())
		.addTransition(StateType::Walk, new ConditionCollisionY(), StateType::Shell)
		.addTransition(StateType::Shell, new ConditionCollisionY(), StateType::ShellSlide)
		.addTransition(StateType::ShellSlide, new ConditionCollisionY(), StateType::Shell)
		.setInitialState(StateType::Walk)
		.build();

	return new Enemy(EnemyType::koopa, fsm);
}
Enemy* EnemyManager::spawnSpiny()
{
	FiniteStateMachine* fsm;
	FSMBuilder			builder;

	fsm = builder
		.addState(new FallState(GRAVITY))
		.addState(new WalkState(WALKSPEED, GRAVITY, false))
		.addState(new DeadStateElse(GRAVITYPREMIUM))
		.addTransition(StateType::Fall, new ConditionCollisionY(), StateType::Walk)
		.addTransition(StateType::Walk, new ConditionCollisionX(), StateType::DeadElse)
		.setInitialState(StateType::Fall)
		.build();

	return new Enemy(EnemyType::spiny, fsm);
}

Enemy* EnemyManager::spawnLakitu()
{
	FiniteStateMachine* fsm;
	FSMBuilder			builder;

	fsm = builder
		.addState(new HoverState(RANDOMSPEED, RANDOMBOUNDARY, DISTANCESPEED, OFFSET, PLAYER))
		.addState(new DeadStateStomp())
		.addState(new DeadStateElse(GRAVITYPREMIUM))
		.addTransition(StateType::Hover, new ConditionCollisionY(), StateType::DeadStomp)
		.addTransition(StateType::Hover, new ConditionCollisionY(), StateType::DeadElse)
		.setInitialState(StateType::Hover)
		.build();

	return new Enemy(EnemyType::lakitu, fsm);
}

Enemy* EnemyManager::spawnParatroopa()
{
	FiniteStateMachine* fsm;
	FSMBuilder			builder;

	fsm = builder
		.addState(new HopState(HOPPOWER, WALKSPEED, GRAVITY))
		.addState(new WalkState(WALKSPEED, GRAVITY, false))
		.addState(new ShellState(GRAVITY))
		.addState(new ShellSlidingState(SHELLSPEED, GRAVITY))
		.addState(new DeadStateStomp())
		.addState(new DeadStateElse(GRAVITYPREMIUM))
		.addTransition(StateType::Hop, new ConditionCollisionY(), StateType::Walk)
		.addTransition(StateType::Walk, new ConditionCollisionY(), StateType::Shell)
		.addTransition(StateType::Shell, new ConditionCollisionY(), StateType::ShellSlide)
		.addTransition(StateType::ShellSlide, new ConditionCollisionY(), StateType::Shell)
		.setInitialState(StateType::Hop)
		.build();

	return new Enemy(EnemyType::paratroopa, fsm);
}
Enemy* EnemyManager::spawnBeezyBettle()
{
	FiniteStateMachine* fsm;
	FSMBuilder			builder;

	fsm = builder
		.addState(new WalkState(WALKSPEED, GRAVITY, true))
		.addState(new ShellState(GRAVITY))
		.addState(new ShellSlidingState(SHELLSPEED, GRAVITY))
		.addState(new DeadStateStomp())
		.addTransition(StateType::Walk, new ConditionCollisionY(), StateType::Shell)
		.addTransition(StateType::Shell, new ConditionCollisionY(), StateType::ShellSlide)
		.addTransition(StateType::ShellSlide, new ConditionCollisionY(), StateType::Shell)
		.setInitialState(StateType::Walk)
		.build();

	return new Enemy(EnemyType::beezybettle, fsm);
}

Enemy* EnemyManager::spawnCheepCheep()
{
	FiniteStateMachine* fsm;
	FSMBuilder			builder;

	fsm = builder
		.addState(new WalkState(WALKSPEED, GRAVITY, true))
		.addState(new ShellState(GRAVITY))
		.addState(new ShellSlidingState(SHELLSPEED, GRAVITY))
		.addState(new DeadStateStomp())
		.addTransition(StateType::Walk, new ConditionCollisionY(), StateType::Shell)
		.addTransition(StateType::Shell, new ConditionCollisionY(), StateType::ShellSlide)
		.addTransition(StateType::ShellSlide, new ConditionCollisionY(), StateType::Shell)
		.setInitialState(StateType::Walk)
		.build();

	return new Enemy(EnemyType::beezybettle, fsm);
}
Enemy* EnemyManager::spawnBlooper()
{
	FiniteStateMachine* fsm;
	FSMBuilder			builder;

	fsm = builder
		.addState(new FallState(GRAVITY))
		.addState(new ChaseState(CHASESPEED, PLAYER))
		.addState(new DeadStateElse(GRAVITYPREMIUM))
		.addTransition(StateType::Fall, new ConditionTimer(), StateType::Chase)
		.addTransition(StateType::Chase, new ConditionTimer(), StateType::Fall)
		.addTransition(StateType::Fall, new ConditionCollisionY(), StateType::DeadElse)
		.addTransition(StateType::Chase, new ConditionCollisionY(), StateType::DeadElse)
		.setInitialState(StateType::Fall)
		.build();

	return new Enemy(EnemyType::blooper, fsm);
}
Enemy* EnemyManager::spawnHammerBro()
{
	FiniteStateMachine* fsm;
	FSMBuilder			builder;

	fsm = builder

		.build();

	return new Enemy(EnemyType::hammerbro, fsm);
}
Enemy* EnemyManager::spawnBowser()
{
	FiniteStateMachine* fsm;
	FSMBuilder			builder;

	fsm = builder

		.build();

	return new Enemy(EnemyType::bowser, fsm);
}
Enemy* EnemyManager::spawnHammer()
{
	FiniteStateMachine* fsm;
	FSMBuilder			builder;

	fsm = builder
		.addState(new FallState(GRAVITY))

		.setInitialState(StateType::Fall)
		.build();

	return new Enemy(EnemyType::hammer, fsm);
}