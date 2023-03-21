#pragma once
#include "raylib.h"
#include "Screen.h"
#include <iostream>

class Ghost {
private:
	unsigned short speed;
    Texture2D sprite;
    Vector2 pivot;
    Rectangle spriteRec, screenRec;
    Rectangle collider, sides[4];
    unsigned short active;
    Vector2Int velocity, vturn, arrows[4];
    float turning;

    void UpdateColliders();
    void UpdatePosition();
public:
    bool isDead;
    Ghost(const Ghost& obj) = delete;
    Ghost(const char* texturePath, Vector2 firstPosition, Vector2 pivotPoint = { 0.5f,0.5f });
    ~Ghost();
    void Move();
    void Interact();
    void Render(bool debugging);
};