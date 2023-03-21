#include <iostream>
#include <raylib.h>
#include "Vector2.hpp"

int main() {
	const int rows = 36, cols = 28, cellSize = 16;

	InitWindow(cols * cellSize, rows * cellSize, "Pacman");
	ClearWindowState(FLAG_WINDOW_RESIZABLE);

	while (!WindowShouldClose()) {
		BeginDrawing();

		ClearBackground(BLACK);

		EndDrawing();
	}

	CloseWindow();
}