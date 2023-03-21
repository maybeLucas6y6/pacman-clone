#include "Pacman.h"
#include <string>
#include <iostream>
constexpr auto MAX_SCORE = 240;

           Pacman::Pacman(const char* texturePath, Vector2 firstPosition, Vector2 pivotPoint) {
	speed = 100;
	score = 0;
	sprite = LoadTexture(texturePath);
	pivot = { pivotPoint.x * 32 * scale,pivotPoint.y * 32 * scale };
	spriteRec = { 0,0,32,32 };
	screenRec = { firstPosition.x,firstPosition.y,sprite.width * scale,sprite.height * scale };
	collider = { screenRec.x - pivot.x / 2 + 1, screenRec.y - pivot.y / 2 + 1, 14, 14 };
	sides[0] = { collider.x, collider.y - 2, 14, 2};
	sides[1] = { collider.x + 14, collider.y, 2, 14 };
	sides[2] = { collider.x, collider.y + 14, 14, 2 };
	sides[3] = { collider.x - 2, collider.y, 2, 14 };
	active = 0;
	velocity = vturn = { 0,-1 };
	turning = 0;
}
           Pacman::~Pacman() {
			  UnloadTexture(sprite);
		  }
void       Pacman::UpdateColliders() {
	collider.x = screenRec.x - pivot.x / 2 + 1;
	collider.y = screenRec.y - pivot.y / 2 + 1;
	sides[0].x = collider.x;
	sides[0].y = collider.y - 2;
	sides[1].x = collider.x + 14;
	sides[1].y = collider.y;
	sides[2].x = collider.x;
	sides[2].y = collider.y + 14;
	sides[3].x = collider.x - 2;
	sides[3].y = collider.y;
}
void       Pacman::UpdatePosition() {
	screenRec.x += velocity.y * speed * deltaTime;
	screenRec.y += velocity.x * speed * deltaTime;
	if (CheckCollisionWithWall({ screenRec.x - pivot.x / 2 + 1, screenRec.y - pivot.y / 2 + 1,14,14 })) {
		screenRec.x -= velocity.y * speed * deltaTime;
		screenRec.y -= velocity.x * speed * deltaTime;
		velocity = { 0,0 };
	}
	pacmanPos.x = (int)screenRec.y / 16;
	pacmanPos.y = (int)screenRec.x / 16;
	UpdateColliders();
}
void       Pacman::Move() {
	Interact();
	int key = GetKeyPressed();
	Vector2Int arrow{};
	if (key) switch (key) {
	case (int)KeyboardKey::KEY_W:
		arrow = { -1,0 };
		active = 0;
		break;
	case (int)KeyboardKey::KEY_D:
		arrow = { 0,1 };
		active = 1;
		break;
	case (int)KeyboardKey::KEY_S:
		arrow = { 1,0 };
		active = 2;
		break;
	case (int)KeyboardKey::KEY_A:
		arrow = { 0,-1 };
		active = 3;
		break;
	}

	if (turning > 0) {
		turning -= deltaTime;
		if (!CheckCollisionWithWall(sides[active])) {
			turning = 0;
			velocity = vturn;
			//vturn = { 0,0 };
		}
		UpdatePosition();
		return;
	}

	if (arrow.x != 0 || arrow.y != 0) {
		if (velocity.x == 0 && velocity.y == 0) {
			velocity = arrow;
		}
		else {
			turning = .3;
			vturn = arrow;
			return;
		}
	}
	if(velocity.x != 0 || velocity.y != 0) UpdatePosition();
}
void       Pacman::Interact() {
	Vector2Int tile = ScreenToMap({ screenRec.x,screenRec.y });
	if (screen[tile.x][tile.y] == 7) {
		screen[tile.x][tile.y] = 16;
		score++;
		if (score == MAX_SCORE) {
			pause = true;
		}
	}
	else if (screen[tile.x][tile.y] == 17) {
		screen[tile.x][tile.y] = 16;
		panic = 10;
	}
}
void       Pacman::Render(bool debugging) {
	if (debugging) {
		DrawRectangleLinesEx(collider, 1.0f, RED);
		DrawRectangleLinesEx(sides[0], 1.0f, RED);
		DrawRectangleLinesEx(sides[1], 1.0f, RED);
		DrawRectangleLinesEx(sides[2], 1.0f, RED);
		DrawRectangleLinesEx(sides[3], 1.0f, RED);
		DrawRectangleLinesEx(sides[active], 1.0f, GREEN);

		std::string str = "Player x: ";
		Vector2Int mapPos = ScreenToMap({ screenRec.x,screenRec.y });
		str += std::to_string(mapPos.x);
		str += ", y: ";
		str += std::to_string(mapPos.y);
		str += "\n";
		DrawText(str.c_str(), 0, 0, 20, WHITE);
	}
	else {
		DrawTexturePro(sprite, spriteRec, screenRec, pivot, 0, WHITE);

		std::string str = "Score: ";
		str += std::to_string(score);
		DrawText(str.c_str(), 0, 0, 40, WHITE);
	}
}
Vector2Int Pacman::GetTile() {
	return { (int)screenRec.y / 16,(int)screenRec.x / 16 };
}