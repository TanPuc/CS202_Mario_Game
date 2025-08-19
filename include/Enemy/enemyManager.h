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
	vector<Enemy*> m_shells;

	Enemy* spawnGooba(Vector2);
	Enemy* spawnKoopa(Vector2);
	Enemy* spawnSpiny(Vector2);
	Enemy* spawnLakitu(Vector2);
	Enemy* spawnParatroopa(Vector2);
	Enemy* spawnBeezyBettle(Vector2);
	Enemy* spawnCheepCheep(Vector2);
	Enemy* spawnBlooper(Vector2);
	Enemy* spawnHammerBro(Vector2);
	Enemy* spawnBowser(Vector2);
	Enemy* spawnHammer(Vector2);
	Enemy* spawnPiranhaPlant(Vector2);
	Enemy* spawnFireBall(Vector2);
};