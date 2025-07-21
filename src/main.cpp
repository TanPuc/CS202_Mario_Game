#include <vector>
#include <iostream>
#include "raylib.h"
#include "Mario.h"
#include "Level.h"

int main(void)
{
	int width = 1280, height = 720;
	InitWindow(width, height, "Mario");
	SetTargetFPS(60);

	bool pause = false;

	Mario player;
	Level level;

	while (!WindowShouldClose())
	{
		if (IsKeyPressed(KEY_P))
		{
			pause = !pause;
		}

		player.HandleInput();
		player.Update();

		BeginDrawing();
		ClearBackground(DARKGRAY);

		level.Draw();
		player.Draw();

		EndDrawing();
	}

	CloseWindow();

	return 0;
}