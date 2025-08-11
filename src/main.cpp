#include <vector>
#include <iostream>
#include "raylib.h"
#include "Mario.h"
#include "Level.h"
#include "enemyManager.h"

#define MARIO_SKYBLUE (Color){68, 145, 190, 255}

int main(void)
{
	InitWindow(800, 512, "Mario");
	SetTargetFPS(60);

	Vector2 CameraPos = {0, 0};
	Mario *player = new Mario({float(GetScreenWidth() / 2 - 16), 0.0f});
	Level *level = new Level();
	level->LoadFromFile("assets/level1.map");

	enemyAsset::Load();
	EnemyManager* manager = new EnemyManager();
	Vector2 posEnemy = { 300, 300 };
	manager->spawnEnemyAt(EnemyType::goopa, posEnemy);

	while (!WindowShouldClose())
	{
		/// UPDATE GAME
		player->HandleInput();
		player->Update(*level); // Handling player collision and movement

		/// RENDER GAME
		Camera2D camera = {0};
		Vector2 playerPos = player->GetPosition();
		if (playerPos.x > CameraPos.x)
		{
			CameraPos.x = playerPos.x;
		}
		camera.target = (Vector2){float(CameraPos.x + player->rect.width / 2), 0};
		camera.offset = (Vector2){float(GetScreenWidth() / 4), float(GetScreenHeight() / 2)};
		// camera.offset = (Vector2){200, 600};
		camera.zoom = 0.5f;

		///ENEMY
		manager->update();

		BeginDrawing();

		ClearBackground(MARIO_SKYBLUE);
		BeginMode2D(camera);

		level->Draw();
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