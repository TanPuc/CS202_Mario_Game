#include "enemyManager.h"

#include "enemy.h"
#include "enemyState.h"
#include "enemyAttackStrategy.h"
#include "enemyFSMBuilder.h"
#include "enemyStateTransition.h"
#include "enemyStateCondition.h"
#include "enemySprite.h"

#include "enemyEnum.h"

const float WALKSPEED = 20;
const float SHELLSPEED = 40;
const float RANDOMSPEED = 20;
const float RANDOMBOUNDARY = 200;
const float DISTANCESPEED = 50;
const float CHASESPEED = 30;
const float SWIMSPEED = 20;
const float FREQUENCY = 5;
const float MAGNITUDE = 10;
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
		e->Update();
	}
}

void EnemyManager::spawnEnemyAt(EnemyType type, Vector2 position)
{
	Enemy* e = nullptr;
	
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

	case EnemyType::spiny:
	{
		e = spawnSpiny();
		break;
	}

	case EnemyType::lakitu:
	{
		e = spawnLakitu();
		break;
	}

	case EnemyType::paratroopa:
	{
		e = spawnParatroopa();
		break;
	}

	case EnemyType::beezybettle:
	{
		e = spawnBeezyBettle();
		break;
	}

	case EnemyType::cheepcheep:
	{
		e = spawnCheepCheep();
		break;
	}

	case EnemyType::blooper:
	{
		e = spawnBlooper();
		break;
	}

	case EnemyType::hammerbro:
	{
		e = spawnHammerBro();
		break;
	}

	case EnemyType::bowser:
	{
		e = spawnBowser();
		break;
	}

	case EnemyType::hammer:
	{
		e = spawnHammer();
		break;
	}
	default:
		break;
	}

	e->setPosition(position);

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

	Texture2D text = enemyAsset::GetTexture(EnemyType::goopa);

	SpriteEnemy* sprite = new SpriteEnemy();
	sprite->addSpriteConfig(StateType::Walk, {text, {0,0,16,16}, 0, 2 , 1.0f});
	sprite->addSpriteConfig(StateType::DeadStomp, {text, {32,0,16,16}, 32, 1 , 1.0f} );

	Rectangle hitbox = { 0,0,16,16 };

	return new Enemy(EnemyType::goopa, fsm, sprite);
}
Enemy* EnemyManager::spawnKoopa()
{
	FiniteStateMachine* fsm;
	FSMBuilder			builder;

	fsm = builder
		.addState(new WalkState(WALKSPEED, GRAVITY, false))
		.addState(new ShellState(GRAVITY))
		.addState(new ShellSlidingState(SHELLSPEED, GRAVITY))
		.addState(new DeadStateElse(GRAVITYPREMIUM))
		.addTransition(StateType::Walk, new ConditionCollisionY(), StateType::Shell)
		.addTransition(StateType::Shell, new ConditionCollisionY(), StateType::ShellSlide)
		.addTransition(StateType::ShellSlide, new ConditionCollisionY(), StateType::Shell)
		.setInitialState(StateType::Walk)
		.build();

	SpriteEnemy* sprite = new SpriteEnemy();
	sprite->addSpriteConfig(StateType::Walk, {});
	sprite->addSpriteConfig(StateType::Shell, {});
	sprite->addSpriteConfig(StateType::ShellSlide, {});
	sprite->addSpriteConfig(StateType::DeadElse, {});

	Rectangle hitbox = {};

	return new Enemy(EnemyType::koopa, fsm, sprite, hitbox);
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

	SpriteEnemy* sprite = new SpriteEnemy();
	sprite->addSpriteConfig(StateType::Fall, {});
	sprite->addSpriteConfig(StateType::Walk, {});
	sprite->addSpriteConfig(StateType::DeadElse, {});

	Rectangle hitbox = {};

	return new Enemy(EnemyType::spiny, fsm, sprite, hitbox);
}

Enemy* EnemyManager::spawnLakitu()
{
	FiniteStateMachine* fsm;
	FSMBuilder			builder;

	fsm = builder
		.addState(new HoverState(RANDOMSPEED, RANDOMBOUNDARY, DISTANCESPEED, OFFSET, PLAYER))
		.addState(new DeadStateElse(GRAVITYPREMIUM))
		.addTransition(StateType::Hover, new ConditionCollisionY(), StateType::DeadElse)
		.setInitialState(StateType::Hover)
		.build();

	SpriteEnemy* sprite = new SpriteEnemy();
	sprite->addSpriteConfig(StateType::Hover, {});
	sprite->addSpriteConfig(StateType::DeadElse, {});

	Rectangle hitbox = {};

	return new Enemy(EnemyType::lakitu, fsm, sprite, hitbox);
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

	SpriteEnemy* sprite = new SpriteEnemy();
	sprite->addSpriteConfig(StateType::Hop, {});
	sprite->addSpriteConfig(StateType::Walk, {});
	sprite->addSpriteConfig(StateType::Shell, {});
	sprite->addSpriteConfig(StateType::ShellSlide, {});
	sprite->addSpriteConfig(StateType::DeadElse, {});

	Rectangle hitbox = {};

	return new Enemy(EnemyType::paratroopa, fsm, sprite,);
}
Enemy* EnemyManager::spawnBeezyBettle()
{
	FiniteStateMachine* fsm;
	FSMBuilder			builder;

	fsm = builder
		.addState(new WalkState(WALKSPEED, GRAVITY, true))
		.addState(new ShellState(GRAVITY))
		.addState(new ShellSlidingState(SHELLSPEED, GRAVITY))
		.addState(new DeadStateElse(GRAVITYPREMIUM))
		.addTransition(StateType::Walk, new ConditionCollisionY(), StateType::Shell)
		.addTransition(StateType::Shell, new ConditionCollisionY(), StateType::ShellSlide)
		.addTransition(StateType::ShellSlide, new ConditionCollisionY(), StateType::Shell)
		.setInitialState(StateType::Walk)
		.build();

	SpriteEnemy* sprite = new SpriteEnemy();
	sprite->addSpriteConfig(StateType::Walk, {});
	sprite->addSpriteConfig(StateType::Shell, {});
	sprite->addSpriteConfig(StateType::ShellSlide, {});
	sprite->addSpriteConfig(StateType::DeadElse, {});

	Rectangle hitbox = {};

	return new Enemy(EnemyType::beezybettle, fsm, sprite, hitbox);
}

Enemy* EnemyManager::spawnCheepCheep()
{
	FiniteStateMachine* fsm;
	FSMBuilder			builder;

	fsm = builder
		.addState(new SwimState(SWIMSPEED, FREQUENCY, MAGNITUDE))
		.addState(new DeadStateElse(GRAVITYPREMIUM))
		.addTransition(StateType::Swim, new ConditionCollisionY(), StateType::DeadElse)
		.setInitialState(StateType::Swim)
		.build();

	SpriteEnemy* sprite = new SpriteEnemy();
	sprite->addSpriteConfig(StateType::Swim, {});
	sprite->addSpriteConfig(StateType::DeadElse, {});

	Rectangle hitbox = {};

	return new Enemy(EnemyType::beezybettle, fsm, sprite, hitbox);
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

	SpriteEnemy* sprite = new SpriteEnemy();
	sprite->addSpriteConfig(StateType::Fall, {});
	sprite->addSpriteConfig(StateType::Chase, {});
	sprite->addSpriteConfig(StateType::DeadElse, {});

	Rectangle hitbox = {};

	return new Enemy(EnemyType::blooper, fsm, sprite, hitbox);
}
Enemy* EnemyManager::spawnHammerBro()
{
	FiniteStateMachine* fsm;
	FSMBuilder			builder;

	fsm = builder

		.build();

	SpriteEnemy* sprite = new SpriteEnemy();

	Rectangle hitbox = {};

	return new Enemy(EnemyType::hammerbro, fsm,sprite, hitbox);
}
Enemy* EnemyManager::spawnBowser()
{
	FiniteStateMachine* fsm;
	FSMBuilder			builder;

	fsm = builder

		.build();

	SpriteEnemy* sprite = new SpriteEnemy();

	Rectangle hitbox = {};

	return new Enemy(EnemyType::bowser, fsm, sprite, hitbox );
}
Enemy* EnemyManager::spawnHammer()
{
	FiniteStateMachine* fsm;
	FSMBuilder			builder;

	fsm = builder
		.addState(new FallState(GRAVITY))

		.setInitialState(StateType::Fall)
		.build();

	SpriteEnemy* sprite = new SpriteEnemy();

	Rectangle hitbox = {};

	return new Enemy(EnemyType::hammer, fsm, sprite, hitbox);
}