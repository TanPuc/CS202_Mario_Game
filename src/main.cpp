#include "raylib.h"
#include "Mario.h"
#include "Level.h"
#include "items/Coin.h"
#include "items/Mushroom.h"

#define MARIO_SKYBLUE (Color){68, 145, 190, 255}
#include "DGameState/GameStateManager.h"
#include "DGameState/MenuState.h"
#include "DCore/ResourceManager.h"

int main(void)
{
	InitWindow(800, 512, "Mario");
	InitAudioDevice();
	SetTargetFPS(60);

	Vector2 CameraPos = {0, 0};
	Mario *player = new Mario({float(GetScreenWidth() / 2 - 16), 0.0f});
	Level *level = new Level();
	Coin *coin = new Coin({200, 100});
	Mushroom *mushroom = new Mushroom({300, 100});

	level->LoadFromFile("assets/level1.map");
	// No exit key
	SetExitKey(KEY_NULL);

	ResourceManager::GetInstance().LoadGameFont("assets/Super Mario Bros. 2.ttf");

	GameStateManager gsm;

	gsm.changeState(new MenuState(&gsm));

	while (!WindowShouldClose() && !gsm.isExiting())
	{
		/// UPDATE GAME
		player->HandleInput();
		player->Update(*level); // Handling player collision and movement
		coin->Update(*level, *player);
		mushroom->Update(*level, *player);

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
		gsm.update();

		BeginDrawing();
		ClearBackground(SKYBLUE);

		gsm.draw();

		ClearBackground(MARIO_SKYBLUE);
		BeginMode2D(camera);

		level->Draw();
		player->Draw();
		coin->Draw();
		mushroom->Draw();

		EndMode2D();
		EndDrawing();
	}
	ResourceManager::GetInstance().UnloadResources();

	CloseAudioDevice();
	CloseWindow();

	return 0;
}

// int main(void)
// {
// 	InitWindow(800, 512, "Mario");
// 	SetTargetFPS(60);

// 	Texture2D marioTexture = LoadTexture("assets/mario.png");
// 	Mario *player = new Mario(marioTexture, {float(GetScreenWidth() / 2 - 16), 0.0f});

// 	Level *level = new Level();
// 	level->LoadFromFile("assets/level1.map");

// 	bool pause = false;

// 	while (!WindowShouldClose())
// 	{
// 		/// UPDATE
// 		if (IsKeyPressed(KEY_P))
// 		{
// 			pause = !pause;
// 		}

// 		player->Update();
// 		player->CheckCollision(*level);

// 		/// RENDER
// 		Camera2D camera = {0};
// 		camera.target = Vector2{float(player->position.x + player->rect.width / 2), 0.0f};
// 		camera.offset = Vector2{200.0f, float(GetScreenHeight() / 2)};
// 		camera.zoom = 0.5f;

// 		BeginDrawing();
// 		ClearBackground(SKYBLUE);
// 		BeginMode2D(camera);

// 		level->Draw(camera);
// 		player->Draw();

// 		EndMode2D();
// 		EndDrawing();
// 	}
// 	if (player)
// 		delete player;
// 	if (level)
// 		delete level;
// 	CloseWindow();

// 	return 0;
// }