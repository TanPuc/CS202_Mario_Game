#pragma once

#include "vector"
#include "raylib.h"

using std::vector;


class Enemy;

class EnemyManager
{
public:
	void spawnEnemyAt(int type, Vector2 position);
	void update();
private:
	vector<Enemy*> m_enemies;
	vector<Enemy*> m_toSpawn;
};