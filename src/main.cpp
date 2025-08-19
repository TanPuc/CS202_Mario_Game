#include "raylib.h"
#include "Mario.h"
#include "Level.h"
#include "DGameObjects/Coin.h"
#include "DGameObjects/Mushroom.h"
#include "DGameState/GameStateManager.h"
#include "DGameState/MenuState.h"
#include "DCore/ResourceManager.h"
#include "DCore/SoundManager.h"

// #define MARIO_SKYBLUE (Color){68, 145, 190, 255}
#define MARIO_SKYBLUE (Color{68, 145, 190, 225})
// #define MARIO_SKYBLUE (Color){148, 148, 255, 255}
#define MARIO_SKYBLACK (Color){0, 0, 0, 255}

int main(void)
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	InitWindow(SCREEN_WIDTH * SCALE, SCREEN_HEIGHT * SCALE, "Mario");
	InitAudioDevice();
	SetTargetFPS(60);

	ResourceManager::GetInstance().LoadGameFont("assets/Super Mario Bros. 2.ttf");
	ResourceManager::GetInstance().LoadBackgroundTexture("assets/menu_background.png");
	SoundManager::getInstance().load();

	float initialPosX = 0.0f;
	Vector2 CameraPos = {0, 0};
	Mario *player = new Mario({initialPosX, 0.0f});
	Level level("./assets/Levels/world_1.1.txt");

	while (!WindowShouldClose())
	{
		/// UPDATE GAME
		player->HandleInput();
		player->Update(level); // Handling player collision and movement
		level.update(*player);

		/// RENDER GAME
		Camera2D camera = {0};
		Vector2 playerPos = player->GetPosition();
		if (playerPos.x > CameraPos.x)
		{
			CameraPos.x = playerPos.x;
		}
		camera.target = (Vector2){float(CameraPos.x + player->rect.width / 2), float(GetScreenHeight() / 2)};
		camera.offset = (Vector2){float(GetScreenWidth() / 2), float(GetScreenHeight() / 2)};
		camera.zoom = 1.0f;

		BeginDrawing();
		ClearBackground(MARIO_SKYBLUE);
		// ClearBackground(SKYBLUE);
		Texture2D background = ResourceManager::GetInstance().GetBackgroundTexture();
		float bgAspectRatio = (float)background.width / (float)background.height;
		float bgScreenWidth = (float)GetScreenWidth() + 15;
		float bgScreenHeight = bgScreenWidth / bgAspectRatio;

		Rectangle sourceRec = {0.0f, 0.0f, (float)background.width, (float)background.height};
		Rectangle destRec = {0.0f, 0.0f, bgScreenWidth, bgScreenHeight};
		Vector2 origin = {0, 0};

		DrawTexturePro(background, sourceRec, destRec, origin, 0.0f, WHITE);

		gsm.draw();

		ClearBackground(MARIO_SKYBLACK);
		BeginMode2D(camera);

		level->render();
		player->Draw();

		EndMode2D();
		EndDrawing();
	}
	SoundManager::getInstance().unload();
	ResourceManager::GetInstance().UnloadResources();

	CloseAudioDevice();
	if (player)
		delete player;
	if (level)
		delete level;
	CloseWindow();

	return 0;
}