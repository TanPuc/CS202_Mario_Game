#include "raylib.h"
#include "Mario.h"
#include "Level.h"
#include "DGameObjects/Coin.h"
#include "DGameObjects/Mushroom.h"

#define MARIO_SKYBLUE (Color{68, 145, 190, 225})
#include "DGameState/GameStateManager.h"
#include "DGameState/MenuState.h"
#include "DCore/ResourceManager.h"
#include "DCore/SoundManager.h"

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
	SoundManager::getInstance().load();

	GameStateManager gsm;

	SoundManager::getInstance().playMusic(MusicTrack::MAIN_THEME);

	gsm.changeState(new MenuState(&gsm));

	while (!WindowShouldClose() && !gsm.isExiting())
	{
		SoundManager::getInstance().updateMusicStreams();
		gsm.update();

		BeginDrawing();
		ClearBackground(MARIO_SKYBLUE);
		// ClearBackground(SKYBLUE);

		gsm.draw();
		EndDrawing();
	}
	SoundManager::getInstance().unload();
	ResourceManager::GetInstance().UnloadResources();

	CloseAudioDevice();
	CloseWindow();

	return 0;
}