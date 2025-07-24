#include <vector>
#include <iostream>
#include "raylib.h"
#include "Mario.h"
#include "Level.h"

int main(void)
{
	InitWindow(800, 512, "Mario");
	SetTargetFPS(60);

	Texture2D marioTexture = LoadTexture("assets/mario.png");
	Mario *player = new Mario(marioTexture, {(float)GetScreenWidth() / 2 - 16, 0});

	Level *level = new Level();
	level->LoadFromFile("assets/level1.map");

	bool pause = false;

	while (!WindowShouldClose())
	{
		/// UPDATE
		if (IsKeyPressed(KEY_P))
		{
			pause = !pause;
		}

		player->Update();
		player->CheckCollision(*level);

		/// RENDER
		Camera2D camera = {0};
		camera.target = (Vector2){(float)player->position.x + player->rect.width / 2, 0};
		camera.offset = (Vector2){200, (float)GetScreenHeight() / 2};
		camera.zoom = 0.5f;

		BeginDrawing();
		ClearBackground(SKYBLUE);
		BeginMode2D(camera);

		level->Draw(camera);
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