#include <vector>
#include <iostream>
#include "raylib.h"
#include "Mario.h"
#include "Tile.h"

int main(void)
{
	InitWindow(screenWidth * SCALE, screenHeight * SCALE, "Mario");
	SetTargetFPS(60);

	bool pause = false;

	Mario player;
	World1_1 world1_1("./assets/tiles/world_1.1.txt");

	//===============================
	// std::vector<Rectangle> vRects;
	// vRects.push_back(Rectangle{170.0f, 70.0f, 10.0f, 40.0f});
	// vRects.push_back(Rectangle{150.0f, 50.0f, 20.0f, 20.0f});
	// vRects.push_back(Rectangle{150.0f, 150.0f, 75.0f, 20.0f});
	// vRects.push_back(Rectangle{170.0f, 50.0f, 20.0f, 20.0f});
	// vRects.push_back(Rectangle{190.0f, 50.0f, 20.0f, 20.0f});
	// vRects.push_back(Rectangle{110.0f, 50.0f, 20.0f, 20.0f});
	// vRects.push_back(Rectangle{50.0f, 130.0f, 20.0f, 20.0f});
	// vRects.push_back(Rectangle{50.0f, 150.0f, 20.0f, 20.0f});
	// vRects.push_back(Rectangle{50.0f, 170.0f, 20.0f, 20.0f});
	// vRects.push_back(Rectangle{150.0f, 100.0f, 10.0f, 1.0f});
	// vRects.push_back(Rectangle{200.0f, 100.0f, 20.0f, 60.0f});
	// Vector2 velocity = {0.0f, 0.0f};
	//===============================

	while (!WindowShouldClose())
	{
		if (IsKeyPressed(KEY_P))
		{
			pause = !pause;
		}

		player.HandleInput();
		world1_1.update( player );
		player.Update();

		BeginDrawing();
		ClearBackground(DARKGRAY);
		BeginMode2D(player.camera);

		world1_1.render();
		player.Draw();

		EndMode2D();

		//===============================
		// float et = GetFrameTime();
		// Vector2 vMouse = GetMousePosition();
		// Vector2 vPoint = { 128.0f, 120.0f };
		// if ( IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
		// 	float a = ( vMouse.x - vPoint.x ) * ( vMouse.x - vPoint.x ) + ( vMouse.y - vPoint.y ) * ( vMouse.y - vPoint.y );
		// 	float b = Q_rsqrt(a);
		// 	velocity.x += (vMouse.x - vPoint.x) * 100.0f * et * b;
		// 	velocity.y += (vMouse.y - vPoint.y) * 100.0f * et * b;
		// }

		// for ( const auto& r : vRects )
		// 	DrawRectangle(r.x, r.y, r.width, r.height, WHITE);

		// // CHECK AND SOLVE
		// Vector2 cp, cn;
		// float t = 0.0f;
		// std::vector<std::pair<int, float>> z;
		// for ( size_t i = 1; i < vRects.size(); i++ ) {
		// 	if ( aabb::CheckCollisionStaticRectDynamicRect(&vRects[0], velocity, vRects[i], cp, cn, t, et)) {
		// 		z.push_back({ i, t });
		// 	}
		// }
		// std::sort(z.begin(), z.end(), compare);
		// for ( auto j : z ) 
		// 	aabb::ResolveStaticRectDynamicRect(&vRects[0], velocity, et, &vRects[j.first]);

		// // UPDATE POSITION
		// vRects[0].x += velocity.x * et;
		// vRects[0].y += velocity.y * et;
		//===============================

		EndDrawing();
	}

	CloseWindow();

	return 0;
}