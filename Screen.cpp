#include "Screen.h"
#include <string>
#include <iostream>

float deltaTime = 0;
bool pause = false;
float scale = 1.0f;
const float wWidth = 28 * 16, wHeight = 36 * 16;
unsigned short screen[36][28] = {
	{16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16},
	{16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16},
	{16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16},
	{ 2,10,10,10,10,10,10,10,10,10,10,10,10, 3, 2,10,10,10,10,10,10,10,10,10,10,10,10, 3},
	{ 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 1, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 1},
	{ 0, 7, 4,11,11, 5, 7, 4,11,11,11, 5, 7, 1, 0, 7, 4,11,11,11, 5, 7, 4,11,11, 5, 7, 1},
	{ 0,17, 1, 6, 6, 0, 7, 1, 6, 6, 6, 0, 7, 1, 0, 7, 1, 6, 6, 6, 0, 7, 1, 6, 6, 0,17, 1},
	{ 0, 7,14,10,10,15, 7,14,10,10,10,15, 7,14,15, 7,14,10,10,10,15, 7,14,10,10,15, 7, 1},
	{ 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 1},
	{ 0, 7, 4,11,11, 5, 7, 4, 5, 7, 4,11,11,11,11,11,11, 5, 7, 4, 5, 7, 4,11,11, 5, 7, 1},
	{ 0, 7,14,10,10,15, 7, 1, 0, 7,14,10,10, 3, 2,10,10,15, 7, 1, 0, 7,14,10,10,15, 7, 1},
	{ 0, 7, 7, 7, 7, 7, 7, 1, 0, 7, 7, 7, 7, 1, 0, 7, 7, 7, 7, 1, 0, 7, 7, 7, 7, 7, 7, 1},
	{12,11,11,11,11, 5, 7, 1,12,11,11, 5,16, 1, 0,16, 4,11,11,13, 0, 7, 4,11,11,11,11,13},
	{16,16,16,16,16, 0, 7, 1, 2,10,10,15,16,14,15,16,14,10,10, 3, 0, 7, 1,16,16,16,16,16},
	{16,16,16,16,16, 0, 7, 1, 0,16,16,16,16,16,16,16,16,16,16, 1, 0, 7, 1,16,16,16,16,16},
	{16,16,16,16,16, 0, 7, 1, 0,16, 4,11,11,16,16,11,11, 5,16, 1, 0, 7, 1,16,16,16,16,16},
	{10,10,10,10,10,15, 7,14,15,16, 1,16,16,16,16,16,16, 0,16,14,15, 7,14,10,10,10,10,10},
	{16,16,16,16,16,16, 7,16,16,16, 1,16,16,16,16,16,16, 0,16,16,16, 7,16,16,16,16,16,16},
	{11,11,11,11,11, 5, 7, 4, 5,16, 1,16,16,16,16,16,16, 0,16, 4, 5, 7, 4,11,11,11,11,11},
	{16,16,16,16,16, 0, 7, 1, 0,16,14,10,10,10,10,10,10,15,16, 1, 0, 7, 1,16,16,16,16,16},
	{16,16,16,16,16, 0, 7, 1, 0,16,16,16,16,16,16,16,16,16,16, 1, 0, 7, 1,16,16,16,16,16},
	{16,16,16,16,16, 0, 7, 1, 0,16, 4,11,11,11,11,11,11, 5,16, 1, 0, 7, 1,16,16,16,16,16},
	{ 2,10,10,10,10,15, 7,14,15,16,14,10,10, 3, 2,10,10,15,16,14,15, 7,14,10,10,10,10, 3},
	{ 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 1, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 1},
	{ 0, 7, 4,11,11, 5, 7, 4,11,11,11, 5, 7, 1, 0, 7, 4,11,11,11, 5, 7, 4,11,11, 5, 7, 1},
	{ 0, 7,14,10, 3, 0, 7,14,10,10,10,15, 7,14,15, 7,14,10,10,10,15, 7, 1, 2,10,15, 7, 1},
	{ 0,17, 7, 7, 1, 0, 7, 7, 7, 7, 7, 7, 7,16,16, 7, 7, 7, 7, 7, 7, 7, 1, 0, 7, 7,17, 1},
	{12,11, 5, 7, 1, 0, 7, 4, 5, 7, 4,11,11,11,11,11,11, 5, 7, 4, 5, 7, 1, 0, 7, 4,11,13},
	{ 2,10,15, 7,14,15, 7, 1, 0, 7,14,10,10, 3, 2,10,10,15, 7, 1, 0, 7,14,15, 7,14,10, 3},
	{ 0, 7, 7, 7, 7, 7, 7, 1, 0, 7, 7, 7, 7, 1, 0, 7, 7, 7, 7, 1, 0, 7, 7, 7, 7, 7, 7, 1},
	{ 0, 7, 4,11,11,11,11,13,12,11,11, 5, 7, 1, 0, 7, 4,11,11,13,12,11,11,11,11, 5, 7, 1},
	{ 0, 7,14,10,10,10,10,10,10,10,10,15, 7,14,15, 7,14,10,10,10,10,10,10,10,10,15, 7, 1},
	{ 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 1},
	{12,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,13},
	{16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16},
	{16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16}
};
Texture2D tileMap;
Rectangle tiles[10][10];
std::vector<Rectangle> walls = {
	{ 0,48,448,16 },
	{ 0,64,16,128 },
	{ 432,64,16,128 },
	{ 0,192,96,80 },
	{ 352,192,96,80 },
	{ 0,288,96,80 },
	{ 352,288,96,80 },
	{ 0,368,16,176 },
	{ 432,368,16,176 },
	{ 16,528,416,16 },
	{ 16,432,32,32 },
	{ 400,432,32,32 },
	{ 32,80,64,48 },
	{ 112,80,80,48 },
	{ 256,80,80,48 },
	{ 352,80,64,48 },
	{ 32,144,64,32 },
	{ 160,144,128,32 },
	{ 352,144,64,32 },
	{ 112,144,32,128 },
	{ 144,192,48,32 },
	{ 256,192,48,32 },
	{ 304,144,32,128 },
	{ 160,240,128,80 },
	{ 112,288,32,80 },
	{ 304,288,32,80 },
	{ 208,176,32,48 },
	{ 160,336,128,32 },
	{ 208,368,32,48 },
	{ 32,384,64,32 },
	{ 64,416,32,0 },
	{ 112,384,80,32 },
	{ 256,384,80,32 },
	{ 352,384,64,32 },
	{ 352,416,32,48 },
	{ 112,432,32,48 },
	{ 32,480,160,32 },
	{ 160,432,128,32 },
	{ 208,464,32,48 },
	{ 304,432,32,48 },
	{ 256,480,160,32 },
	{ 64,416,32,48 },
	{ 208,64,32,64 }
};
Vector2Int pacmanPos = { 0,0 };
float panic = 0;

void DrawGrid2D(unsigned short rows, unsigned short columns, Color color) {
	float cellWidth = wWidth / columns;
	float cellHeight = wHeight / rows;
	DrawLineEx({ 0,wHeight }, { wWidth,wHeight }, 1, color);
	DrawLineEx({ wWidth,0 }, { wWidth,wHeight }, 1, color);
	for (int i = 0; i < rows; i++) {
		DrawLineEx({ 0,i * cellHeight }, { wWidth,i * cellHeight }, 1, color);
	}
	for (int i = 0; i < columns; i++) {
		DrawLineEx({ i * cellWidth,0 }, { i * cellWidth,wHeight }, 1, color);
	}
}
void LoadMap(const char* path) {
	tileMap = LoadTexture(path);
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			tiles[i][j] = { j * 16.0f,i * 16.0f,16.0f,16.0f };
		}
	}
}
void UnloadMap() {
	UnloadTexture(tileMap);
}
void RenderMap() {
	for (int i = 0; i < 36; i++) {
		for (int j = 0; j < 28; j++) {
			DrawTextureRec(tileMap, tiles[screen[i][j] / 10][screen[i][j] % 10], { j * 16.0f,i * 16.0f }, WHITE);
		}
	}
}
Vector2Int ScreenToMap(Vector2 pos) {
	return { (int)pos.y / 16,(int)pos.x / 16 };
}
Vector2 MapToScreen(Vector2 pos) {
	return { pos.y * 16 + 8,pos.x * 16 + 8 };
}
void WriteMousePosition(Vector2 pos) {
	Vector2Int posMap = ScreenToMap(pos);
	std::string ptr = "Mouse x: ";
	ptr += std::to_string(posMap.x);
	ptr += ", y: ";
	ptr += std::to_string(posMap.y);
	ptr += "\n";
	DrawText(ptr.c_str(), wWidth / 2, 0, 20, WHITE);
}
void DrawRectangles(std::vector<Rectangle> list) {
	for (auto& x : list) {
		DrawRectangleLinesEx(x, 1, RED);
	}
}
bool CheckCollisionWithWall(Rectangle rec) {
	for (auto& x : walls) {
		if (CheckCollisionRecs(x, rec)) {
			return true;
		}
	}
	return false;
}