#pragma once

#include "vector"
#include "raylib.h"

#include "enemyEnum.h"

using std::vector;


class Enemy;

class EnemyManager
{
public:
	void spawnEnemyAt(EnemyType type, Vector2 position);
	void update();
private:
	vector<Enemy*> m_enemies;
	vector<Enemy*> m_toSpawn;

	Enemy* spawnGooba();
	Enemy* spawnKoopa();
	Enemy* spawnSpiny();
	Enemy* spawnLakitu();
	Enemy* spawnParatroopa();
	Enemy* spawnBeezyBettle();
	Enemy* spawnCheepCheep();
	Enemy* spawnBlooper();
	Enemy* spawnHammerBro();
	Enemy* spawnBowser();
	Enemy* spawnHammer();

};