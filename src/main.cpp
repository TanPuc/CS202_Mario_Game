#include <vector>
#include <iostream>
#include "raylib.h"
#include "Mario.h"
#include "Tile.h"
#include "Enemy/enemyManager.h"

#define MARIO_SKYBLUE Color{68, 145, 190, 255}

int main(void)
{
	InitWindow(SCREEN_WIDTH * SCALE, SCREEN_HEIGHT * SCALE, "Mario");
	SetTargetFPS(60);

	Vector2 CameraPos = {0, 0};
	Mario *player = new Mario({float(GetScreenWidth() / 2 - 16), 0.0f});
	Level *level = new Level("./assets/tiles/world_1.1.txt");

	enemyAsset::Load();
	EnemyManager* manager = new EnemyManager(player, level);
	Vector2 posEnemy = { 700, 300};
	//manager->spawnEnemyAt(EnemyType::goopa, posEnemy);
	//manager->spawnEnemyAt(EnemyType::koopa, posEnemy);
	//manager->spawnEnemyAt(EnemyType::cheepcheep, posEnemy);
	//manager->spawnEnemyAt(EnemyType::beezybettle, posEnemy);
	//manager->spawnEnemyAt(EnemyType::blooper, posEnemy);
	//manager->spawnEnemyAt(EnemyType::spiny, posEnemy);
	//manager->spawnEnemyAt(EnemyType::lakitu, posEnemy);
	//manager->spawnEnemyAt(EnemyType::cheepcheep, posEnemy);
	//manager->spawnEnemyAt(EnemyType::paratroopa, posEnemy);
	//manager->spawnEnemyAt(EnemyType::hammer, posEnemy);
	//manager->spawnEnemyAt(EnemyType::piranhaplant, posEnemy);
	//manager->spawnEnemyAt(EnemyType::hammerbro, posEnemy);
	manager->spawnEnemyAt(EnemyType::bowser, posEnemy);

	while (!WindowShouldClose())
	{
		/// UPDATE GAME
		player->HandleInput();
		player->Update(*level); // Handling player collision and movement
		///ENEMY
		manager->update();

		/// RENDER GAME
		Camera2D camera = {0};
		Vector2 playerPos = player->GetPosition();
		if (playerPos.x > CameraPos.x)
		{
			CameraPos.x = playerPos.x;
		}
		camera.target = Vector2{float(CameraPos.x + player->rect.width / 2), float(GetScreenHeight()/2)};
		camera.offset = Vector2{float(GetScreenWidth() / 2), float(GetScreenHeight() / 2)};
		camera.zoom = 1.0f;

		BeginDrawing();

		ClearBackground(MARIO_SKYBLUE);
		BeginMode2D(camera);

		level->run(*player);
		manager->draw();
		player->Draw();
		

		EndMode2D();
		EndDrawing();
	}

	if (player)
		delete player;
	if (level)
		delete level;
	CloseWindow();

	return 0;
}