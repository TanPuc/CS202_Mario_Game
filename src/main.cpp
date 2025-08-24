#include "raylib.h"
#include "Character.h"
#include "Level.h"
#include "DGameObjects/Coin.h"
#include "DGameObjects/Mushroom.h"
#include "DGameState/GameStateManager.h"
#include "DGameState/MenuState.h"
#include "DCore/ResourceManager.h"
#include "DCore/SoundManager.h"
#include "Tile.h"
#include "Enemy/enemyManager.h"

// #define MARIO_SKYBLUE (Color{68, 145, 190, 255})
// #define MARIO_SKYBLUE (Color{68, 145, 190, 225})
#define MARIO_SKYBLUE (Color){148, 148, 255, 255}
#define MARIO_SKYBLACK (Color){0, 0, 0, 255}

int main(void)
{
	SetConfigFlags( FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	InitWindow(SCREEN_WIDTH * SCALE, SCREEN_HEIGHT * SCALE, "Mario");
	InitAudioDevice();
	SetTargetFPS(60);

	ResourceManager::GetInstance().LoadGameFont("assets/Super Mario Bros. 2.ttf");
	// ResourceManager::GetInstance().LoadBackgroundTexture("assets/menu_background.png");
	SoundManager::getInstance().load();

	float initialPosX = 0.0f;
	Vector2 CameraPos = {0, 0};
	// No exit key
	SetExitKey(KEY_NULL);
	GameStateManager gsm;
	SoundManager::getInstance().playMusic(MusicTrack::MAIN_THEME);
	gsm.changeState(new MenuState(&gsm));

	while (!WindowShouldClose() && !gsm.isExiting())
	{
		BeginDrawing();
		SoundManager::getInstance().updateMusicStreams();
		ClearBackground(SKYBLUE);
		gsm.update();
		Texture2D background = ResourceManager::GetInstance().GetBackgroundTexture();
		float bgAspectRatio = (float)background.width / (float)background.height;
		float bgScreenWidth = (float)GetScreenWidth() + 15;
		float bgScreenHeight = bgScreenWidth / bgAspectRatio;

		Rectangle sourceRec = {0.0f, 0.0f, (float)background.width, (float)background.height};
		Rectangle destRec = {0.0f, 0.0f, bgScreenWidth, bgScreenHeight};
		Vector2 origin = {0, 0};

		DrawTexturePro(background, sourceRec, destRec, origin, 0.0f, WHITE);

		gsm.draw();
		EndDrawing();
	}
	SoundManager::getInstance().unload();
	ResourceManager::GetInstance().UnloadResources();

	CloseAudioDevice();
	CloseWindow();

	return 0;
}