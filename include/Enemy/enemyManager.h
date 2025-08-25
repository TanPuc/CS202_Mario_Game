#pragma once

#include <vector>
#include <memory>
#include "raylib.h"

#include "Enemy/enemyEnum.h"
#include "Enemy/enemyAsset.h"

using namespace std;

class Character;
class Enemy;
class Level;
class FireBall;
class PlayingState;


class EnemyManager
{
public:
	EnemyManager(Character* player, Level* level, PlayingState* ps, const vector<shared_ptr<FireBall>>& fireballs);
	void spawnEnemyAt(EnemyType type, Vector2 position);
	void update();
	void draw();
private:
	PlayingState* m_playingState;
	Level* m_level;
	Character* m_player;
	const vector<shared_ptr<FireBall>>& m_fireballs;
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