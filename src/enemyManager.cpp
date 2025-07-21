#include "enemyManager.h"
#include "enemy.h"
#include "enemyState.h"

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
		e = new Enemy(type, position,
			new AliveState()
		);
		break;
	}

	case EnemyType::koopa:
	{
		e = new Enemy(type, position,
			new AliveState()
		);

		break;
	}
	default:
		break;
	}

	m_toSpawn.push_back(e);
}