#include "Enemy/enemyManager.h"

#include "Enemy/enemy.h"
#include "Enemy/enemyState.h"
#include "Enemy/enemyAttackStrategy.h"
#include "Enemy/enemyFSMBuilder.h"
#include "Enemy/enemyStateTransition.h"
#include "Enemy/enemyStateCondition.h"
#include "Enemy/enemySprite.h"

#include "Enemy/enemyEnum.h"

#include "FireBallManager.h"
#include "Character.h"

#include "algorithm"
using namespace std;

const float WALKSPEED = 50;
const float SHELLSPEED = 200;
const float RANDOMSPEED = 80;
const float RANDOMBOUNDARY = 150;
const float DISTANCESPEED = 500;
const float CHASESPEED = 300;
const float SWIMSPEED = 20;
const float FREQUENCY = 5;
const float MAGNITUDE = 20;
const float PIRANHAMAGNITUDE = 100;
const float GRAVITYPREMIUM = 300;
const float HOPPOWER = 500;
const float ATTACKSPEED = 100;
const float BLOOPERGRAVITY = 100;

const Vector2 OFFSET = {300, 300};
vector<FireBall *> FIREBALLS = {};

const float CHASETIMER = 1.0f;
const float ATTACKTIMER = 0.75f;
const float HAMMERCOOLDOWNTIMER = 1;
const float FIREBALLCOOLDOWNTIMER = 3;
const float JUMPCOOLDOWNTIMER = 2;
const float SPINYCOOLDOWNTIMER = 2;

EnemyManager::EnemyManager(Character *mario, Level *level, const vector<shared_ptr<FireBall>> &fireballs) : m_player(mario), m_level(level), m_fireballs(fireballs) {}
void EnemyManager::update()
{
	for (auto e : m_toSpawn)
	{
		m_enemies.push_back(e);
	}
	m_toSpawn.clear();

	auto isNotActive = [this](Enemy *e)
	{
		return !e->isActive();
	};

	m_enemies.erase(remove_if(m_enemies.begin(), m_enemies.end(), isNotActive), m_enemies.end());

	for (auto e : m_enemies)
	{
		e->Update(*m_level);
		if (m_player->isDead)
			return;
		if (!e->CheckIsDead() && CheckCollisionRecs(e->getHitBox(), m_player->rect))
		{
			m_player->Die();
		}

		if (!e->CheckIsDead() && !e->CheckHasNoHurtBox() && CheckCollisionRecs(e->getHurtBox(), m_player->rect))
		{
			std::cout << "Enemy collided with Mario" << std::endl;
			m_player->velocity.y = -500.0f;
			e->setHitBox({0,0,e->getHitBox().width, e->getHitBox().height});
		}
	}
}

void EnemyManager::addShell(Enemy *e)
{
	m_shells.push_back(e);
}
void EnemyManager::removeShell(Enemy *e)
{
	m_shells.erase(remove(m_shells.begin(), m_shells.end(), e), m_shells.end());
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
	Enemy *e = nullptr;

	switch (type)
	{
	case EnemyType::goopa:
	{
		e = spawnGooba(position);
		break;
	}

	case EnemyType::koopa:
	{
		e = spawnKoopa(position);
		break;
	}

	case EnemyType::spiny:
	{
		e = spawnSpiny(position);
		break;
	}

	case EnemyType::lakitu:
	{
		e = spawnLakitu(position);
		break;
	}

	case EnemyType::paratroopa:
	{
		e = spawnParatroopa(position);
		break;
	}

	case EnemyType::beezybettle:
	{
		e = spawnBeezyBettle(position);
		break;
	}

	case EnemyType::cheepcheep:
	{
		e = spawnCheepCheep(position);
		break;
	}

	case EnemyType::blooper:
	{
		e = spawnBlooper(position);
		break;
	}

	case EnemyType::hammerbro:
	{
		e = spawnHammerBro(position);
		break;
	}

	case EnemyType::bowser:
	{
		e = spawnBowser(position);
		break;
	}

	case EnemyType::hammer:
	{
		e = spawnHammer(position);
		break;
	}

	case EnemyType::piranhaplant:
	{
		e = spawnPiranhaPlant(position);
		break;
	}

	case EnemyType::fireball:
	{
		e = spawnFireBall(position);
		break;
	}
	default:
		break;
	}

	// e->setPosition(position);

	m_toSpawn.push_back(e);
}

Enemy *EnemyManager::spawnGooba(Vector2 pos)
{
	FiniteStateMachine *fsm;
	FSMBuilder builder;

	fsm = builder
			  .addState(new WalkState(WALKSPEED, GRAVITY))
			  .addState(new DeadStateStomp())
			  .addState(new DeadStateElse(GRAVITYPREMIUM))
			  .addTransition(StateType::Walk, new ConditionStomped(*m_player), StateType::DeadStomp)
			  .addTransition(StateType::Walk, new ConditionFireBall(m_fireballs), StateType::DeadElse)
			  .addTransition(StateType::Walk, new ConditionShell(m_shells), StateType::DeadElse)
			  .setInitialState(StateType::Walk)
			  .build();

	Texture2D text = enemyAsset::GetTexture(EnemyType::goopa);
	SpriteEnemy *sprite = new SpriteEnemy();
	sprite->addSpriteConfig(StateType::Walk, {text, {0, 0, 16, 16}, 0, 2, 1.0f});
	sprite->addSpriteConfig(StateType::DeadStomp, {text, {32, 0, 16, 16}, 32, 1, 1.0f});
	sprite->addSpriteConfig(StateType::DeadElse, {text, {0, 0, 16, -16}, 0, 1, 1.0f});

	Vector2 size = {16, 16};

	return new Enemy(EnemyType::goopa, fsm, sprite, size, pos);
}
Enemy *EnemyManager::spawnKoopa(Vector2 pos)
{
	FiniteStateMachine *fsm;
	FSMBuilder builder;

	fsm = builder
			  .addState(new WalkOnLedgeState(WALKSPEED, GRAVITY))
			  .addState(new ShellState(GRAVITY))
			  .addState(new ShellSlidingState(SHELLSPEED, GRAVITY, *m_player, this))
			  .addState(new DeadStateElse(GRAVITYPREMIUM))
			  .addTransition(StateType::Walk, new ConditionStomped(*m_player), StateType::Shell)
			  .addTransition(StateType::Shell, new ConditionKicked(*m_player), StateType::ShellSlide)
			  .addTransition(StateType::ShellSlide, new ConditionStomped(*m_player), StateType::Shell)
			  .addTransition(StateType::Walk, new ConditionFireBall(m_fireballs), StateType::DeadElse)
			  .addTransition(StateType::Walk, new ConditionShell(m_shells), StateType::DeadElse)
			  .setInitialState(StateType::Walk)
			  .build();

	Texture2D text = enemyAsset::GetTexture(EnemyType::koopa);

	SpriteEnemy *sprite = new SpriteEnemy();
	sprite->addSpriteConfig(StateType::Walk, {text, {0, 0, 16, 24}, 0, 2, 1.0f});
	sprite->addSpriteConfig(StateType::Shell, {text, {32, 8, 16, 16}, 32, 1, 0.5f});
	sprite->addSpriteConfig(StateType::ShellSlide, {text, {32, 8, 16, 16}, 32, 1, 0.5f});
	sprite->addSpriteConfig(StateType::DeadElse, {text, {48, 8, 16, -16}, 48, 1, 1.0f});

	Vector2 size = {16, 24};

	return new Enemy(EnemyType::koopa, fsm, sprite, size, pos);
}
Enemy *EnemyManager::spawnSpiny(Vector2 pos)
{
	FiniteStateMachine *fsm;
	FSMBuilder builder;

	fsm = builder
			  .addState(new FallState(GRAVITY))
			  .addState(new WalkState(WALKSPEED, GRAVITY, m_player))
			  .addState(new DeadStateElse(GRAVITYPREMIUM))
			  .addTransition(StateType::Fall, new ConditionGrounded(*m_level), StateType::Walk)
			  .addTransition(StateType::Walk, new ConditionFireBall(m_fireballs), StateType::DeadElse)
			  .addTransition(StateType::Walk, new ConditionShell(m_shells), StateType::DeadElse)
			  .setInitialState(StateType::Fall)
			  .build();

	Texture2D text = enemyAsset::GetTexture(EnemyType::spiny);

	SpriteEnemy *sprite = new SpriteEnemy();
	sprite->addSpriteConfig(StateType::Fall, {text, {0, 0, 16, 16}, 0, 2, 0.5f});
	sprite->addSpriteConfig(StateType::Walk, {text, {32, 0, 16, 16}, 32, 2, 1.0f});
	sprite->addSpriteConfig(StateType::DeadElse, {text, {32, 0, 16, -16}, 32, 1, 0.5f});

	Vector2 size = {16, 16};

	Enemy *emmy = new Enemy(EnemyType::spiny, fsm, sprite, size, pos);
	emmy->SwitchNoHurtBox();
	return emmy;
}

Enemy *EnemyManager::spawnLakitu(Vector2 pos)
{
	FiniteStateMachine *fsm;
	FSMBuilder builder;

	fsm = builder
			  .addState(new HoverState(RANDOMSPEED, RANDOMBOUNDARY, DISTANCESPEED, OFFSET, m_player))
			  .addState(new AttackState(this, new AttackStrat(this, EnemyType::spiny)))
			  .addState(new DeadStateElse(GRAVITYPREMIUM))
			  .addTransition(StateType::Hover, new ConditionTimer(SPINYCOOLDOWNTIMER), StateType::Attack)
			  .addTransition(StateType::Attack, new ConditionTimer(ATTACKTIMER), StateType::Hover)
			  .addTransition(StateType::Attack, new ConditionStomped(*m_player), StateType::DeadElse)
			  .addTransition(StateType::Hover, new ConditionStomped(*m_player), StateType::DeadElse)
			  .addTransition(StateType::Attack, new ConditionFireBall(m_fireballs), StateType::DeadElse)
			  .addTransition(StateType::Hover, new ConditionFireBall(m_fireballs), StateType::DeadElse)
			  .setInitialState(StateType::Hover)
			  .build();

	Texture2D text = enemyAsset::GetTexture(EnemyType::lakitu);

	SpriteEnemy *sprite = new SpriteEnemy(m_player);
	sprite->addSpriteConfig(StateType::Hover, {text, {0, 0, 16, 24}, 0, 1, 1.5f});
	sprite->addSpriteConfig(StateType::Attack, {text, {16, 0, 16, 24}, 16, 1, 1.5f});
	sprite->addSpriteConfig(StateType::DeadElse, {text, {0, 0, 16, -24}, 0, 1, 0.5f});

	Vector2 size = {16, 24};

	return new Enemy(EnemyType::lakitu, fsm, sprite, size, pos);
}

Enemy *EnemyManager::spawnParatroopa(Vector2 pos)
{
	FiniteStateMachine *fsm;
	FSMBuilder builder;

	fsm = builder
			  .addState(new HopState(HOPPOWER, WALKSPEED, GRAVITY))
			  .addState(new WalkOnLedgeState(WALKSPEED, GRAVITY))
			  .addState(new ShellState(GRAVITY))
			  .addState(new ShellSlidingState(SHELLSPEED, GRAVITY, *m_player, this))
			  .addState(new DeadStateStomp())
			  .addState(new DeadStateElse(GRAVITYPREMIUM))
			  .addTransition(StateType::Hop, new ConditionStomped(*m_player), StateType::Walk)
			  .addTransition(StateType::Walk, new ConditionStomped(*m_player), StateType::Shell)
			  .addTransition(StateType::Shell, new ConditionKicked(*m_player), StateType::ShellSlide)
			  .addTransition(StateType::ShellSlide, new ConditionStomped(*m_player), StateType::Shell)
			  .addTransition(StateType::Hop, new ConditionFireBall(m_fireballs), StateType::DeadElse)
			  .addTransition(StateType::Walk, new ConditionShell(m_shells), StateType::DeadElse)
			  .addTransition(StateType::Walk, new ConditionFireBall(m_fireballs), StateType::DeadElse)
			  .addTransition(StateType::Shell, new ConditionShell(m_shells), StateType::DeadElse)
			  .addTransition(StateType::Shell, new ConditionFireBall(m_fireballs), StateType::DeadElse)
			  .addTransition(StateType::ShellSlide, new ConditionFireBall(m_fireballs), StateType::DeadElse)
			  .setInitialState(StateType::Hop)
			  .build();

	Texture2D text = enemyAsset::GetTexture(EnemyType::paratroopa);

	SpriteEnemy *sprite = new SpriteEnemy();
	sprite->addSpriteConfig(StateType::Hop, {text, {32, 0, 16, 24}, 32, 2, 1.0f});
	sprite->addSpriteConfig(StateType::Walk, {text, {0, 0, 16, 24}, 0, 2, 1.0f});
	sprite->addSpriteConfig(StateType::Shell, {text, {48, 8, 16, 16}, 64, 1, 0.5f});
	sprite->addSpriteConfig(StateType::ShellSlide, {text, {48, 8, 16, 16}, 64, 1, 0.5f});
	sprite->addSpriteConfig(StateType::DeadElse, {text, {80, 8, 16, -16}, 80, 1, 1.0f});

	Vector2 size = {16, 24};

	return new Enemy(EnemyType::paratroopa, fsm, sprite, size, pos);
}
Enemy *EnemyManager::spawnBeezyBettle(Vector2 pos)
{
	FiniteStateMachine *fsm;
	FSMBuilder builder;

	fsm = builder
			  .addState(new WalkState(WALKSPEED, GRAVITY))
			  .addState(new ShellState(GRAVITY))
			  .addState(new ShellSlidingState(SHELLSPEED, GRAVITY, *m_player, this))
			  .addState(new DeadStateElse(GRAVITYPREMIUM))
			  .addTransition(StateType::Walk, new ConditionStomped(*m_player), StateType::Shell)
			  .addTransition(StateType::Shell, new ConditionKicked(*m_player), StateType::ShellSlide)
			  .addTransition(StateType::ShellSlide, new ConditionStomped(*m_player), StateType::Shell)
			  .addTransition(StateType::Walk, new ConditionFireBall(m_fireballs), StateType::DeadElse)
			  .addTransition(StateType::Walk, new ConditionShell(m_shells), StateType::DeadElse)
			  .addTransition(StateType::Shell, new ConditionShell(m_shells), StateType::DeadElse)
			  .setInitialState(StateType::Walk)
			  .build();

	Texture2D text = enemyAsset::GetTexture(EnemyType::beezybettle);

	SpriteEnemy *sprite = new SpriteEnemy();
	sprite->addSpriteConfig(StateType::Walk, {text, {0, 0, 16, 16}, 0, 2, 1.0f});
	sprite->addSpriteConfig(StateType::Shell, {text, {32, 0, 16, 16}, 32, 1, 1.0f});
	sprite->addSpriteConfig(StateType::ShellSlide, {text, {32, 0, 16, 16}, 32, 1, 1.0f});
	sprite->addSpriteConfig(StateType::DeadElse, {text, {32, 0, 16, -16}, 32, 1, 1.0f});

	Vector2 size = {16, 16};

	return new Enemy(EnemyType::beezybettle, fsm, sprite, size, pos);
}

Enemy *EnemyManager::spawnCheepCheep(Vector2 pos)
{
	FiniteStateMachine *fsm;
	FSMBuilder builder;

	fsm = builder
			  .addState(new SwimState(SWIMSPEED, FREQUENCY, MAGNITUDE, m_player))
			  .addState(new DeadStateElse(GRAVITYPREMIUM))
			  .addTransition(StateType::Swim, new ConditionFireBall(m_fireballs), StateType::DeadElse)
			  .setInitialState(StateType::Swim)
			  .build();

	Texture2D text = enemyAsset::GetTexture(EnemyType::cheepcheep);

	SpriteEnemy *sprite = new SpriteEnemy();
	sprite->addSpriteConfig(StateType::Swim, {text, {0, 0, 16, 16}, 0, 2, 1.0f});
	sprite->addSpriteConfig(StateType::DeadElse, {text, {0, 0, 16, 16}, 0, 1, 1.0f});

	Vector2 size = {16, 16};

	return new Enemy(EnemyType::beezybettle, fsm, sprite, size, pos);
}
Enemy *EnemyManager::spawnBlooper(Vector2 pos)
{
	FiniteStateMachine *fsm;
	FSMBuilder builder;

	fsm = builder
			  .addState(new FallState(BLOOPERGRAVITY))
			  .addState(new ChaseState(CHASESPEED, m_player))
			  .addState(new DeadStateElse(GRAVITYPREMIUM))
			  .addTransition(StateType::Fall, new ConditionTimer(CHASETIMER), StateType::Chase)
			  .addTransition(StateType::Chase, new ConditionTimer(CHASETIMER), StateType::Fall)
			  .addTransition(StateType::Fall, new ConditionFireBall(m_fireballs), StateType::DeadElse)
			  .addTransition(StateType::Chase, new ConditionFireBall(m_fireballs), StateType::DeadElse)
			  .setInitialState(StateType::Fall)
			  .build();

	Texture2D text = enemyAsset::GetTexture(EnemyType::blooper);

	SpriteEnemy *sprite = new SpriteEnemy();
	sprite->addSpriteConfig(StateType::Fall, {text, {16, 0, 16, 24}, 16, 1, 1.0f});
	sprite->addSpriteConfig(StateType::Chase, {text, {0, 0, 16, 24}, 0, 1, 1.0f});
	sprite->addSpriteConfig(StateType::DeadElse, {text, {16, 0, 16, -24}, 16, 1, 1.0f});

	Vector2 size = {16, 24};

	return new Enemy(EnemyType::blooper, fsm, sprite, size, pos);
}
Enemy *EnemyManager::spawnHammerBro(Vector2 pos)
{
	FiniteStateMachine *fsm;
	FSMBuilder builder;

	fsm = builder
			  .addState(new PatrolState(RANDOMBOUNDARY, WALKSPEED, HOPPOWER, JUMPCOOLDOWNTIMER))
			  .addState(new AttackState(this, new AttackStrat(this, EnemyType::hammer, 3)))
			  .addState(new DeadStateElse(GRAVITYPREMIUM))
			  .addTransition(StateType::Patrol, new ConditionTimer(HAMMERCOOLDOWNTIMER), StateType::Attack)
			  .addTransition(StateType::Attack, new ConditionTimer(ATTACKTIMER), StateType::Patrol)
			  .addTransition(StateType::Patrol, new ConditionFireBall(m_fireballs), StateType::DeadElse)
			  .addTransition(StateType::Patrol, new ConditionShell(m_shells), StateType::DeadElse)
			  .addTransition(StateType::Attack, new ConditionFireBall(m_fireballs), StateType::DeadElse)
			  .addTransition(StateType::Attack, new ConditionShell(m_shells), StateType::DeadElse)
			  .setInitialState(StateType::Attack)
			  .build();

	Texture2D text = enemyAsset::GetTexture(EnemyType::hammerbro);

	SpriteEnemy *sprite = new SpriteEnemy(m_player);
	sprite->setOffSetPosition({0, -8, 1, 1});
	sprite->addSpriteConfig(StateType::Patrol, {text, {0, 0, 16, 32}, 0, 2, 1.0f});
	sprite->addSpriteConfig(StateType::Attack, {text, {64, 0, 16, 32}, 64, 2, 1.0f});
	sprite->addSpriteConfig(StateType::DeadElse, {text, {0, 0, 16, -32}, 0, 1, 1.0f});

	Vector2 size = {16, 24};

	return new Enemy(EnemyType::hammerbro, fsm, sprite, size, pos);
}
Enemy *EnemyManager::spawnHammer(Vector2 pos)
{
	FiniteStateMachine *fsm;
	FSMBuilder builder;

	fsm = builder
			  .addState(new WalkState(ATTACKSPEED, GRAVITY, m_player))
			  .addState(new DeadStateStomp())
			  .addTransition(StateType::Walk, new ConditionGrounded(*m_level), StateType::DeadStomp)
			  .setInitialState(StateType::Walk)
			  .build();

	Texture2D text = enemyAsset::GetTexture(EnemyType::hammer);

	SpriteEnemy *sprite = new SpriteEnemy();
	sprite->setOffSetPosition({-4, -4, 2, 2});
	sprite->addSpriteConfig(StateType::Walk, {text, {0, 0, 16, 16}, 0, 4, 0.5f});
	sprite->addSpriteConfig(StateType::DeadStomp, {text, {0, 0, 0, 0}, 0, 1, 0.5f});

	Vector2 size = {8, 8};

	Enemy *hemmer = new Enemy(EnemyType::hammer, fsm, sprite, size, pos);
	hemmer->setVelocityY(-HOPPOWER);
	hemmer->SwitchNoHurtBox();
	return hemmer;
}
Enemy *EnemyManager::spawnPiranhaPlant(Vector2 pos)
{
	FiniteStateMachine *fsm;
	FSMBuilder builder;

	fsm = builder
			  .addState(new PiranhaState(PIRANHAMAGNITUDE, FREQUENCY))
			  .addState(new DeadStateElse(GRAVITYPREMIUM))
			  .addTransition(StateType::Piranha, new ConditionFireBall(m_fireballs), StateType::DeadElse)
			  .setInitialState(StateType::Piranha)
			  .build();

	Texture2D text = enemyAsset::GetTexture(EnemyType::piranhaplant);

	SpriteEnemy *sprite = new SpriteEnemy();
	sprite->addSpriteConfig(StateType::Piranha, {text, {0, 0, 16, 24}, 0, 2, 1.0f});
	sprite->addSpriteConfig(StateType::DeadElse, {text, {0, 0, 16, -24}, 0, 1, 1.5f});

	Vector2 size = {16, 24};

	Enemy *hemmer = new Enemy(EnemyType::piranhaplant, fsm, sprite, size, pos);
	hemmer->SwitchNoHitBox();
	return hemmer;
}

Enemy *EnemyManager::spawnBowser(Vector2 pos)
{
	FiniteStateMachine *fsm;
	FSMBuilder builder;

	ConditionFireBall *condiFire = new ConditionFireBall(m_fireballs, 10);

	fsm = builder
			  .addState(new PatrolState(RANDOMBOUNDARY, RANDOMSPEED, HOPPOWER, JUMPCOOLDOWNTIMER))
			  .addState(new AttackState(this, new AttackStrat(this, EnemyType::hammer), 6, 0.5f))
			  .addState(new AttackOffState(this, new AttackStrat(this, EnemyType::fireball)))
			  .addState(new DeadStateElse(GRAVITYPREMIUM))
			  .addTransition(StateType::Patrol, new ConditionTimer(HAMMERCOOLDOWNTIMER), StateType::Attack)
			  .addTransition(StateType::Attack, new ConditionTimer(ATTACKTIMER), StateType::Patrol)
			  .addTransition(StateType::Patrol, new ConditionTimer(FIREBALLCOOLDOWNTIMER), StateType::attackOff)
			  .addTransition(StateType::attackOff, new ConditionTimer(ATTACKTIMER), StateType::Patrol)
			  .addTransition(StateType::Patrol, condiFire, StateType::DeadElse)
			  .addTransition(StateType::attackOff, condiFire, StateType::Patrol)
			  .addTransition(StateType::Attack, condiFire, StateType::Patrol)
			  .setInitialState(StateType::attackOff)
			  .build();

	Texture2D text = enemyAsset::GetTexture(EnemyType::bowser);

	SpriteEnemy *sprite = new SpriteEnemy(m_player);
	sprite->setOffSetPosition({0, -10, 1, 1});
	sprite->addSpriteConfig(StateType::Patrol, {text, {64, 0, 32, 42}, 64, 2, 1.0f});
	sprite->addSpriteConfig(StateType::Attack, {text, {128, 0, 32, 42}, 128, 1, 1.0f});
	sprite->addSpriteConfig(StateType::attackOff, {text, {0, 0, 32, 42}, 0, 2, 1.0f});
	sprite->addSpriteConfig(StateType::DeadElse, {text, {0, 0, 32, -42}, 0, 2, 1.0f});

	Vector2 hitbox = {32, 32};

	return new Enemy(EnemyType::bowser, fsm, sprite, hitbox, pos);
}

Enemy *EnemyManager::spawnFireBall(Vector2 pos)
{
	FiniteStateMachine *fsm;
	FSMBuilder builder;

	Vector2 random = {0, 0};

	switch (GetRandomValue(1, 2))
	{
	case 1:
	{
		random.x = 2.0f;
		random.y = SCALE * 32;
	}
	case 2:
	{
		break;
	}
	default:
		break;
	}

	fsm = builder
			  .addState(new SwimState(ATTACKSPEED, random.x, random.y, m_player))
			  .addState(new DeadStateStomp())
			  .addTransition(StateType::Swim, new ConditionTimer(15), StateType::DeadStomp)
			  .setInitialState(StateType::Swim)
			  .build();

	Texture2D text = enemyAsset::GetTexture(EnemyType::fireball);

	SpriteEnemy *sprite = new SpriteEnemy();
	// sprite->setOffSetPosition({ -4,-4,2,2 });
	sprite->addSpriteConfig(StateType::Swim, {text, {0, 0, -24, 8}, 0, 2, 0.5f});
	sprite->addSpriteConfig(StateType::DeadStomp, {text, {0, 0, 0, 0}, 0, 1, 0.5f});

	Vector2 size = {24, 8};

	Enemy *hemmer = new Enemy(EnemyType::fireball, fsm, sprite, size, pos);
	hemmer->SwitchNoHurtBox();
	return hemmer;
}