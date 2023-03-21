#include "Screen.h"
#include "Pacman.h"
#include "Ghost.h"

#define HALFGRAY CLITERAL(Color){ 130, 130, 130, 100 }
bool debugging = false;

int main() {
	InitWindow(wWidth, wHeight, "Pacman");
	ClearWindowState(FLAG_WINDOW_RESIZABLE);
	LoadMap("resources/tilemap.png");

	Pacman player("resources/pacman.png", MapToScreen({ 26,13 }));
	Ghost Blinky("resources/ghosts.png", MapToScreen({ 14,13 }));

	while (!WindowShouldClose()) {
		deltaTime = GetFrameTime();
		if (!pause) {
			player.Move();
			Blinky.Move();
		}
		if (panic > 0) {
			panic -= deltaTime;
		}
		if (IsKeyPressed((int)KeyboardKey::KEY_G)) debugging = !debugging;

		BeginDrawing();
		ClearBackground(BLACK);

		if (debugging) WriteMousePosition(GetMousePosition());

		if (debugging) DrawGrid2D(36, 28, HALFGRAY);
		RenderMap();
		if (debugging) DrawRectangles(walls);

		player.Render(debugging);
		Blinky.Render(debugging);

		EndDrawing();
	}
	UnloadMap();
	CloseWindow();
}