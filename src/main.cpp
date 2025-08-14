#include "raylib.h"
#include "Mario.h"
#include "Level.h"
#include "DGameObjects/Coin.h"
#include "DGameObjects/Mushroom.h"

#define MARIO_SKYBLUE (Color){68, 145, 190, 255}
#include "DGameState/GameStateManager.h"
#include "DGameState/MenuState.h"
#include "DCore/ResourceManager.h"

int main(void)
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	InitWindow(800, 512, "Mario");
	InitAudioDevice();
	SetTargetFPS(60);

	Vector2 CameraPos = {0, 0};
	// No exit key
	SetExitKey(KEY_NULL);

	ResourceManager::GetInstance().LoadGameFont("assets/Super Mario Bros. 2.ttf");

	GameStateManager gsm;

	gsm.changeState(new MenuState(&gsm));

	while (!WindowShouldClose() && !gsm.isExiting())
	{
		gsm.update();

		BeginDrawing();
		ClearBackground(MARIO_SKYBLUE);
		// ClearBackground(SKYBLUE);

		gsm.draw();
		EndDrawing();
	}
	ResourceManager::GetInstance().UnloadResources();

	CloseAudioDevice();
	CloseWindow();

	return 0;
}