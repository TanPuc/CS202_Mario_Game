#include "enemyManager.h"
#include "enemy.h"
#include "enemyState.h"
#include "enemyAttackStrategy.h"
#include "enemyFSMBuilder.h"
#include "enemyStateTransition.h"
#include "enemyStateCondition.h"
#include "enemyEnum.h"


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
	switch (EnemyType)
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

	case EnemyType::spiny:
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
	}
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
		.addState(new WalkState())
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
		.addState(new WalkState())
		.addState(new ShellState())
		.addState(new ShellSlidingState())
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
		.addState(new WalkState())
		.addState(new DeadStateElse())
		.addTransition(StateType::Walk, new ConditionCollisionX(), StateType::DeadElse)
		.setInitialState(StateType::Walk)
		.build();

	return new Enemy(EnemyType::spiny, fsm);
}

Enemy* EnemyManager::spawnLakitu()
{

}

Enemy* EnemyManager::spawnParatroopa()
{
	FiniteStateMachine* fsm;
	FSMBuilder			builder;

	fsm = builder
		.addState(new HopState())
		.addState(new WalkState())
		.addState(new ShellState())
		.addState(new ShellSlidingState())
		.addState(new DeadStateStomp())
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
		.addState(new WalkState())
		.addState(new ShellState())
		.addState(new ShellSlidingState())
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

}
Enemy* EnemyManager::spawnBlooper()
{

}
Enemy* EnemyManager::spawnHammerBro()
{

}
Enemy* EnemyManager::spawnBowser()
{

}
Enemy* EnemyManager::spawnHammer()
{

}