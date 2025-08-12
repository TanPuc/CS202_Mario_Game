#pragma once

#include "vector"
#include "raylib.h"

#include "enemyEnum.h"
#include "enemyAsset.h"

using std::vector;

class Mario;
class Enemy;
class Level;

class EnemyManager
{
public:
	EnemyManager(Mario* player, Level* level);
	void spawnEnemyAt(EnemyType type, Vector2 position);
	void update();
	void draw();
private:
	Level* m_level;
	Mario* m_player;
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