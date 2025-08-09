#include <vector>
#include <iostream>
#include "raylib.h"
#include "Mario.h"
#include "Tile.h"

int main(void)
{
	int width = 256 * scale, height = 240 * scale;
	InitWindow(width, height, "Mario");
	SetTargetFPS(60);

	bool pause = false;

	Mario player;
	World1_1 world1_1("./assets/tiles/world_1.1.txt");

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
		BeginMode2D(player.camera);

		world1_1.update( player );
		world1_1.render();
		player.Draw();

		EndMode2D();

		EndDrawing();
	}

	CloseWindow();

	return 0;
}