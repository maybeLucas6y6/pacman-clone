#pragma once
#include "raylib.h"
#include <vector>

extern float deltaTime;
extern bool pause;
extern float scale;
extern const float wWidth, wHeight;
extern unsigned short screen[36][28];
extern Texture2D tileMap;
extern Rectangle tiles[10][10];
extern std::vector<Rectangle> walls;
extern Vector2Int pacmanPos;
extern float panic;

void DrawGrid2D(unsigned short rows, unsigned short columns, Color color);
void LoadMap(const char* path);
void UnloadMap();
void RenderMap();
Vector2Int ScreenToMap(Vector2 pos);
Vector2 MapToScreen(Vector2 pos);
void WriteMousePosition(Vector2 pos);
void DrawRectangles(std::vector<Rectangle> list);
bool CheckCollisionWithWall(Rectangle rec);