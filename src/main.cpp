#include <vector>
#include <iostream>
#include "raylib.h"
#include "Mario.h"
#include "Level.h"

// #define MARIO_SKYBLUE (Color){68, 145, 190, 255}
#define MARIO_SKYBLUE (Color){148, 148, 255, 255}
#define MARIO_SKYBLACK (Color){0 ,0 ,0 ,255}

int main(void)
{
	InitWindow(SCREEN_WIDTH * SCALE, SCREEN_HEIGHT * SCALE, "Mario");
	SetTargetFPS(60);

	float initialPosX = 0.0f;
	Vector2 CameraPos = {0, 0};
	Mario* player = new Mario({initialPosX, 5 * TILE_SIZE * SCALE});
	Level_1_4* level = new Level_1_4("./assets/Levels/world_1.4.txt");

	while (!WindowShouldClose())
	{
		/// UPDATE GAME
		player->HandleInput();
		player->Update(*level); // Handling player collision and movement
		level->update(*player);

		/// RENDER GAME
		Camera2D camera = {0};
		Vector2 playerPos = player->GetPosition();
		if (playerPos.x > CameraPos.x)
		{
			CameraPos.x = playerPos.x;
		}
		camera.target = (Vector2){float(CameraPos.x + player->rect.width / 2), float(GetScreenHeight()/2)};
		camera.offset = (Vector2){float(GetScreenWidth() / 2), float(GetScreenHeight() / 2)};
		camera.zoom = 1.0f;

		BeginDrawing();

		ClearBackground(MARIO_SKYBLACK);
		BeginMode2D(camera);

		level->render();
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