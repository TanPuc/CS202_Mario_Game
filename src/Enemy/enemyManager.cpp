#include "Enemy/enemyManager.h"

#include "Enemy/enemy.h"
#include "Enemy/enemyState.h"
#include "Enemy/enemyAttackStrategy.h"
#include "Enemy/enemyFSMBuilder.h"
#include "Enemy/enemyStateTransition.h"
#include "Enemy/enemyStateCondition.h"
#include "Enemy/enemySprite.h"

#include "Enemy/enemyEnum.h"

const float WALKSPEED = 50;
const float SHELLSPEED = 200;
const float RANDOMSPEED = 20;
const float RANDOMBOUNDARY = 200;
const float DISTANCESPEED = 50;
const float CHASESPEED = 300;
const float SWIMSPEED = 20;
const float FREQUENCY = 5;
const float MAGNITUDE = 20;
const float PIRANHAMAGNITUDE = 100;
const float GRAVITYPREMIUM = 300;
const float HOPPOWER = 500;
const float ATTACKSPEED = 100;
const float BLOOPERGRAVITY = 100;

const Vector2 OFFSET = { 500, 600};
vector<FireBall*> FIREBALLS = {};

const float CHASETIMER = 1.0f;
const float ATTACKTIMER = 1;
const float COOLDOWNTIMER = 3;

EnemyManager::EnemyManager(Mario* mario, Level* level) :
	m_player(mario), m_level(level) {}
void EnemyManager::update() {
	for (auto e : m_toSpawn)
	{
		m_enemies.push_back(e);
	}
	m_toSpawn.clear();

	auto isNotActive = [this](Enemy* e){
		return !e->isActive();
	};

	m_enemies.erase(remove_if(m_enemies.begin(), m_enemies.end(), isNotActive), m_enemies.end());


	for (auto e : m_enemies)
	{
		e->Update(*m_level);
	}
}

void EnemyManager::draw()
{
	for (auto e : m_enemies)
	{
		e->Draw();
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

	case EnemyType::piranhaplant:
	{
		e = spawnPiranhaPlant();
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
		.addState(new WalkState(WALKSPEED, GRAVITY))
		.addState(new DeadStateStomp())
		.addTransition(StateType::Walk, new ConditionStomped(*m_player), StateType::DeadStomp)
		.setInitialState(StateType::Walk)
		.build();

	Texture2D text = enemyAsset::GetTexture(EnemyType::goopa);

	SpriteEnemy* sprite = new SpriteEnemy();
	sprite->addSpriteConfig(StateType::Walk, {text, {0,0,16,16}, 0, 2 , 1.0f});
	sprite->addSpriteConfig(StateType::DeadStomp, {text, {32,0,16,16}, 32, 1 , 1.0f} );

	Vector2 size = { 16,16 };

	return new Enemy(EnemyType::goopa, fsm, sprite, size, {0,0});
}
Enemy* EnemyManager::spawnKoopa()
{
	FiniteStateMachine* fsm;
	FSMBuilder			builder;

	fsm = builder
		.addState(new WalkState(WALKSPEED, GRAVITY))
		.addState(new ShellState(GRAVITY))
		.addState(new ShellSlidingState(SHELLSPEED, GRAVITY, *m_player))
		.addState(new DeadStateElse(GRAVITYPREMIUM))
		.addTransition(StateType::Walk, new ConditionStomped(*m_player), StateType::Shell)
		.addTransition(StateType::Shell, new ConditionKicked(*m_player), StateType::ShellSlide)
		.addTransition(StateType::ShellSlide, new ConditionStomped(*m_player), StateType::Shell)
		.addTransition(StateType::Walk, new ConditionFireBall(FIREBALLS), StateType::DeadElse)
		.setInitialState(StateType::Walk)
		.build();

	Texture2D text = enemyAsset::GetTexture(EnemyType::koopa);

	SpriteEnemy* sprite = new SpriteEnemy();
	sprite->addSpriteConfig(StateType::Walk, { text, {0,0,16,24}, 0, 2 , 1.0f} );
	sprite->addSpriteConfig(StateType::Shell, { text, {32,8,16,16}, 32, 1 , 0.5f });
	sprite->addSpriteConfig(StateType::ShellSlide, { text, {32,8,16,16}, 32, 1 , 0.5f });
	sprite->addSpriteConfig(StateType::DeadElse, { text, {48,8,16,-16}, 48, 1 , 1.0f });

	Vector2 size = { 16,24 };

	return new Enemy(EnemyType::koopa, fsm, sprite, size, {});
}
Enemy* EnemyManager::spawnSpiny()
{
	FiniteStateMachine* fsm;
	FSMBuilder			builder;

	fsm = builder
		.addState(new FallState(GRAVITY))
		.addState(new WalkState(WALKSPEED, GRAVITY, m_player))
		.addState(new DeadStateElse(GRAVITYPREMIUM))
		.addTransition(StateType::Fall, new ConditionGrounded(*m_level), StateType::Walk)
		.addTransition(StateType::Walk, new ConditionFireBall(FIREBALLS), StateType::DeadElse)
		.setInitialState(StateType::Fall)
		.build();

	Texture2D text = enemyAsset::GetTexture(EnemyType::spiny);

	SpriteEnemy* sprite = new SpriteEnemy();
	sprite->addSpriteConfig(StateType::Fall, { text, {0,0,16,16}, 0, 2 , 0.5f });
	sprite->addSpriteConfig(StateType::Walk, { text, {32,0,16,16}, 32, 2 , 1.0f });
	sprite->addSpriteConfig(StateType::DeadElse, { text, {32,0,16,-16}, 32, 1 , 0.5f });

	Vector2 size = { 16,16 };

	Enemy* emmy = new Enemy(EnemyType::spiny, fsm, sprite, size, {});
	return emmy;
}

Enemy* EnemyManager::spawnLakitu()
{
	FiniteStateMachine* fsm;
	FSMBuilder			builder;

	fsm = builder
		.addState(new HoverState(RANDOMSPEED, RANDOMBOUNDARY, DISTANCESPEED, OFFSET, m_player))
		.addState(new AttackState(this,new AttackSpiny(this)))
		.addState(new DeadStateElse(GRAVITYPREMIUM))
		.addTransition(StateType::Hover, new ConditionTimer(COOLDOWNTIMER), StateType::Attack)
		.addTransition(StateType::Attack, new ConditionTimer(ATTACKTIMER), StateType::Hover)
		.addTransition(StateType::Attack, new ConditionStomped(*m_player), StateType::DeadElse)
		.addTransition(StateType::Hover, new ConditionStomped(*m_player), StateType::DeadElse)
		.addTransition(StateType::Attack, new ConditionFireBall(FIREBALLS), StateType::DeadElse)
		.addTransition(StateType::Hover, new ConditionFireBall(FIREBALLS), StateType::DeadElse)
		.setInitialState(StateType::Hover)
		.build();

	Texture2D text = enemyAsset::GetTexture(EnemyType::lakitu);

	SpriteEnemy* sprite = new SpriteEnemy();
	sprite->addSpriteConfig(StateType::Hover, { text, {0,0,16,24}, 0, 1 , 1.5f });
	sprite->addSpriteConfig(StateType::Attack, { text, {16,0,16,24}, 16, 1 , 1.5f });
	sprite->addSpriteConfig(StateType::DeadElse, { text, {0,0,16,-24}, 0, 1 , 0.5f });

	Vector2 size = { 16,24 };

	return new Enemy(EnemyType::lakitu, fsm, sprite, size, {});
}

Enemy* EnemyManager::spawnParatroopa()
{
	FiniteStateMachine* fsm;
	FSMBuilder			builder;

	fsm = builder
		.addState(new HopState(HOPPOWER, WALKSPEED, GRAVITY))
		.addState(new WalkState(WALKSPEED, GRAVITY))
		.addState(new ShellState(GRAVITY))
		.addState(new ShellSlidingState(SHELLSPEED, GRAVITY, *m_player))
		.addState(new DeadStateStomp())
		.addState(new DeadStateElse(GRAVITYPREMIUM))
		.addTransition(StateType::Hop, new ConditionStomped(*m_player), StateType::Walk)
		.addTransition(StateType::Walk, new ConditionStomped(*m_player), StateType::Shell)
		.addTransition(StateType::Shell, new ConditionKicked(*m_player), StateType::ShellSlide)
		.addTransition(StateType::ShellSlide, new ConditionStomped(*m_player), StateType::Shell)
		.addTransition(StateType::Hop, new ConditionFireBall(FIREBALLS), StateType::DeadElse)
		.addTransition(StateType::Walk, new ConditionFireBall(FIREBALLS), StateType::DeadElse)
		.addTransition(StateType::Shell, new ConditionFireBall(FIREBALLS), StateType::DeadElse)
		.addTransition(StateType::ShellSlide, new ConditionFireBall(FIREBALLS), StateType::DeadElse)
		.setInitialState(StateType::Hop)
		.build();

	Texture2D text = enemyAsset::GetTexture(EnemyType::paratroopa);

	SpriteEnemy* sprite = new SpriteEnemy();
	sprite->addSpriteConfig(StateType::Hop, { text, {32,0,16,24}, 32, 2 , 1.0f });
	sprite->addSpriteConfig(StateType::Walk, { text, {0,0,16,24}, 0, 2 , 1.0f });
	sprite->addSpriteConfig(StateType::Shell, { text, {48,8,16,16}, 64, 1 , 0.5f });
	sprite->addSpriteConfig(StateType::ShellSlide, { text, {48,8,16,16}, 64, 1 , 0.5f });
	sprite->addSpriteConfig(StateType::DeadElse, { text, {80,8,16,-16}, 80, 1 , 1.0f });

	Vector2 size = { 16,24 };

	return new Enemy(EnemyType::paratroopa, fsm, sprite, size, {});
}
Enemy* EnemyManager::spawnBeezyBettle()
{
	FiniteStateMachine* fsm;
	FSMBuilder			builder;

	fsm = builder
		.addState(new WalkState(WALKSPEED, GRAVITY))
		.addState(new ShellState(GRAVITY))
		.addState(new ShellSlidingState(SHELLSPEED, GRAVITY, *m_player))
		.addState(new DeadStateElse(GRAVITYPREMIUM))
		.addTransition(StateType::Walk, new ConditionStomped(*m_player), StateType::Shell)
		.addTransition(StateType::Shell, new ConditionKicked(*m_player), StateType::ShellSlide)
		.addTransition(StateType::ShellSlide, new ConditionStomped(*m_player), StateType::Shell)
		.addTransition(StateType::Walk, new ConditionFireBall(FIREBALLS), StateType::DeadElse)
		.setInitialState(StateType::Walk)
		.build();

	Texture2D text = enemyAsset::GetTexture(EnemyType::beezybettle);

	SpriteEnemy* sprite = new SpriteEnemy();
	sprite->addSpriteConfig(StateType::Walk, { text, {0,0,16,16}, 0, 2 , 1.0f });
	sprite->addSpriteConfig(StateType::Shell, { text, {32,0,16,16}, 32, 1 , 1.0f });
	sprite->addSpriteConfig(StateType::ShellSlide, { text, {32,0,16,16}, 32, 1 , 1.0f });
	sprite->addSpriteConfig(StateType::DeadElse, { text, {32,0,16,-16}, 32, 1 , 1.0f });

	Vector2 size = { 16,16 };

	return new Enemy(EnemyType::beezybettle, fsm, sprite, size, {});
}

Enemy* EnemyManager::spawnCheepCheep()
{
	FiniteStateMachine* fsm;
	FSMBuilder			builder;

	fsm = builder
		.addState(new SwimState(SWIMSPEED, FREQUENCY, MAGNITUDE))
		.addState(new DeadStateElse(GRAVITYPREMIUM))
		.addTransition(StateType::Swim, new ConditionFireBall(FIREBALLS), StateType::DeadElse)
		.setInitialState(StateType::Swim)
		.build();

	Texture2D text = enemyAsset::GetTexture(EnemyType::cheepcheep);

	SpriteEnemy* sprite = new SpriteEnemy();
	sprite->addSpriteConfig(StateType::Swim, { text, {0,0,16,16}, 0, 2 , 1.0f });
	sprite->addSpriteConfig(StateType::DeadElse, { text, {0,0,16,16}, 0, 1 , 1.0f });

	Vector2 size = { 16,16 };

	return new Enemy(EnemyType::beezybettle, fsm, sprite, size, {});
}
Enemy* EnemyManager::spawnBlooper()
{
	FiniteStateMachine* fsm;
	FSMBuilder			builder;

	fsm = builder
		.addState(new FallState(BLOOPERGRAVITY))
		.addState(new ChaseState(CHASESPEED, m_player))
		.addState(new DeadStateElse(GRAVITYPREMIUM))
		.addTransition(StateType::Fall, new ConditionTimer(CHASETIMER), StateType::Chase)
		.addTransition(StateType::Chase, new ConditionTimer(CHASETIMER), StateType::Fall)
		.addTransition(StateType::Fall, new ConditionFireBall(FIREBALLS), StateType::DeadElse)
		.addTransition(StateType::Chase, new ConditionFireBall(FIREBALLS), StateType::DeadElse)
		.setInitialState(StateType::Fall)
		.build();

	Texture2D text = enemyAsset::GetTexture(EnemyType::blooper);

	SpriteEnemy* sprite = new SpriteEnemy();
	sprite->addSpriteConfig(StateType::Fall, { text, {16,0,16,24}, 16, 1 , 1.0f });
	sprite->addSpriteConfig(StateType::Chase, { text, {0,0,16,24}, 0, 1 , 1.0f });
	sprite->addSpriteConfig(StateType::DeadElse, { text, {16,0,16,-24}, 16, 16 , 1.0f });

	Vector2 size = { 16,24 };

	return new Enemy(EnemyType::blooper, fsm, sprite, size, {});
}
Enemy* EnemyManager::spawnHammerBro()
{
	FiniteStateMachine* fsm;
	FSMBuilder			builder;

	fsm = builder
		.addState(new PatrolState(RANDOMBOUNDARY, WALKSPEED))
		.addState(new AttackState(this, new AttackThrowHammer(this)))
		.addState(new DeadStateElse(GRAVITYPREMIUM))
		.addTransition(StateType::Patrol, new ConditionFireBall(FIREBALLS), StateType::DeadElse)
		.addTransition(StateType::Attack, new ConditionFireBall(FIREBALLS), StateType::DeadElse)
		.setInitialState(StateType::Patrol)
		.build();

	Texture2D text = enemyAsset::GetTexture(EnemyType::hammerbro);

	SpriteEnemy* sprite = new SpriteEnemy();
	sprite->addSpriteConfig(StateType::Patrol, { text, {0,0,16,24}, 0, 2 , 1.0f });
	sprite->addSpriteConfig(StateType::Attack, { text, {64,0,16,32}, 64, 2 , 1.0f });
	sprite->addSpriteConfig(StateType::DeadElse, { text, {0,0,16,-24}, 0, 1 , 1.0f });

	Vector2 size = { 16,24 };

	return new Enemy(EnemyType::hammerbro, fsm, sprite, size, {});
}
Enemy* EnemyManager::spawnHammer()
{
	FiniteStateMachine* fsm;
	FSMBuilder			builder;

	fsm = builder
		.addState(new WalkState(ATTACKSPEED,GRAVITY))
		.addState(new DeadStateStomp())
		.addTransition(StateType::Walk ,new ConditionGrounded(*m_level), StateType::DeadStomp)
		.setInitialState(StateType::Walk)
		.build();

	Texture2D text = enemyAsset::GetTexture(EnemyType::hammer);

	SpriteEnemy* sprite = new SpriteEnemy();
	sprite->addSpriteConfig(StateType::Walk, { text, { 0,0,16,16 }, 0, 4, 0.5f });
	sprite->addSpriteConfig(StateType::DeadStomp, { text, { 0,0,0,0 }, 0, 1, 0.5f });

	Vector2 size = { 16,16 };

	Enemy* hemmer = new Enemy(EnemyType::hammer, fsm, sprite, size, {});
	hemmer->setVelocityY(-HOPPOWER);
	return hemmer;
}
Enemy* EnemyManager::spawnPiranhaPlant()
{
	FiniteStateMachine* fsm;
	FSMBuilder			builder;

	fsm = builder
		.addState(new PiranhaState(PIRANHAMAGNITUDE, FREQUENCY))
		.addState(new DeadStateElse(GRAVITYPREMIUM))
		.addTransition(StateType::Piranha, new ConditionFireBall(FIREBALLS), StateType::DeadElse)
		.setInitialState(StateType::Piranha)
		.build();

	Texture2D text = enemyAsset::GetTexture(EnemyType::piranhaplant);

	SpriteEnemy* sprite = new SpriteEnemy();
	sprite->addSpriteConfig(StateType::Piranha, { text, { 0,0,16,24 }, 0, 2, 1.0f });
	sprite->addSpriteConfig(StateType::DeadElse, { text, { 0,0,16,-24 }, 0, 1, 1.5f });

	Vector2 size = { 16,24 };

	Enemy* hemmer = new Enemy(EnemyType::piranhaplant, fsm, sprite, size, {});
	return hemmer;
}

Enemy* EnemyManager::spawnBowser()
{
	FiniteStateMachine* fsm;
	FSMBuilder			builder;

	fsm = builder

		.build();

	Texture2D text = enemyAsset::GetTexture(EnemyType::bowser);

	SpriteEnemy* sprite = new SpriteEnemy();

	Vector2 hitbox = {};

	return new Enemy(EnemyType::bowser, fsm, sprite, hitbox, {});
}