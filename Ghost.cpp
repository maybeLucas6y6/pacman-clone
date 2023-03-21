#include "Ghost.h"

Ghost::Ghost(const char* texturePath, Vector2 firstPosition, Vector2 pivotPoint) {
	speed = 50;
	sprite = LoadTexture(texturePath);
	pivot = { pivotPoint.x * 32 * scale,pivotPoint.y * 32 * scale };
	spriteRec = { 0,0,32,32 };
	screenRec = { firstPosition.x,firstPosition.y,32 * scale,32 * scale };
	collider = { screenRec.x - pivot.x / 2 + 1, screenRec.y - pivot.y / 2 + 1, 14, 14 };
	sides[0] = { collider.x, collider.y - 2, 14, 2 };
	sides[1] = { collider.x + 14, collider.y, 2, 14 };
	sides[2] = { collider.x, collider.y + 14, 14, 2 };
	sides[3] = { collider.x - 2, collider.y, 2, 14 };
	arrows[0] = { -1,0 };
	arrows[1] = { 0,1 };
	arrows[2] = { 1,0 };
	arrows[3] = { 0,-1 };
	SetRandomSeed(screenRec.x + screenRec.y * GetFileModTime("Source.cpp"));
	active = GetRandomValue(0, 3);
	velocity = vturn = arrows[active];
	turning = 0;
	isDead = false;
}
Ghost::~Ghost() {
	UnloadTexture(sprite);
}
void Ghost::UpdateColliders() {
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
void Ghost::UpdatePosition() {
	screenRec.x += velocity.y * speed * deltaTime;
	screenRec.y += velocity.x * speed * deltaTime;
	if (CheckCollisionWithWall({ screenRec.x - pivot.x / 2 + 1, screenRec.y - pivot.y / 2 + 1,14,14 })) {
		screenRec.x -= velocity.y * speed * deltaTime;
		screenRec.y -= velocity.x * speed * deltaTime;
		velocity = { 0,0 };
	}
	UpdateColliders();
}
void Ghost::Move() {
	if (isDead) return;
	Interact();
	for (unsigned short i = 0; i < 4; i++) {
		if (i == active || (i + 2) % 4 == active) continue;
		if (!CheckCollisionWithWall(sides[i])) {
			if (CheckCollisionWithWall(sides[active]) || GetRandomValue(0, 1)) {
				active = i;
				velocity = arrows[i];
				break;
			}
		}
	}
				std::cout << active << '\n';
	UpdatePosition();
}
void Ghost::Interact() {
	if ((int)screenRec.y / 16 == pacmanPos.x && (int)screenRec.x / 16 == pacmanPos.y) {
		if (panic > 0) {
			isDead = true;
		}
		else {
			pause = true;
		}
	}
}
void Ghost::Render(bool debugging) {
	if (isDead) return;
	if (debugging) {
		DrawRectangleLinesEx(collider, 1.0f, RED);
		DrawRectangleLinesEx(sides[0], 1.0f, RED);
		DrawRectangleLinesEx(sides[1], 1.0f, RED);
		DrawRectangleLinesEx(sides[2], 1.0f, RED);
		DrawRectangleLinesEx(sides[3], 1.0f, RED);
		DrawRectangleLinesEx(sides[active], 1.0f, GREEN);
	}
	else {
		DrawTexturePro(sprite, spriteRec, screenRec, pivot, 0, WHITE);
	}
}