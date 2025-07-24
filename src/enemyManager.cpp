#include "enemyManager.h"
#include "enemy.h"
#include "enemyState.h"
#include "enemyAttackStrategy.h"

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

void EnemyManager::spawnEnemyAt(int type, Vector2 position)
{
	Enemy* e = nullptr;
	switch (type)
	{
	case EnemyType::goopa:
	{
		e = new Enemy(type, position,new WanderState());
		break;
	}

	case EnemyType::koopa:
	{
		e = new Enemy(type, position,new KoopaState());
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