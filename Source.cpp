#include <iostream>
#include <raylib.h>
#include "Vector2.hpp"
#include "Node.hpp"
#include "Pacman.hpp"

int main() {
	const int rows = 36, cols = 28, cellSize = 16;

	InitWindow(cols * cellSize, rows * cellSize, "Pacman");
	ClearWindowState(FLAG_WINDOW_RESIZABLE);

	Node nodes[7]{
		{80, 80, nullptr, &nodes[1], &nodes[2], nullptr},
		{160, 80, nullptr, nullptr, &nodes[3], &nodes[0]},
		{80, 160, &nodes[0], &nodes[3], &nodes[5], nullptr},
		{160, 160, &nodes[1], &nodes[4], nullptr, &nodes[2]},
		{208, 160, nullptr, nullptr, &nodes[6], &nodes[3]},
		{80, 320, &nodes[2], &nodes[6], nullptr, nullptr},
		{208, 320, &nodes[4], nullptr, nullptr, &nodes[5]}
	};

	Pacman player{ &nodes[2] };

	while (!WindowShouldClose()) {
		player.Move(GetFrameTime());

		BeginDrawing();

		ClearBackground(BLACK);
		for (auto& node : nodes) {
			node.Render();
		}
		player.Render();

		EndDrawing();
	}

	CloseWindow();
}