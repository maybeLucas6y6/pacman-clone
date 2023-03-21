#pragma once
#include "raylib.h"
#include "Screen.h"
class Pacman {
private:
    unsigned short speed;
    unsigned short score;
    Texture2D sprite;
    Vector2 pivot;
    Rectangle spriteRec, screenRec;
    Rectangle collider, sides[4];
    unsigned short active;
    Vector2Int velocity, vturn;
    float turning;

    void UpdateColliders();
    void UpdatePosition();
public:
    Pacman(const Pacman& obj) = delete;
    Pacman(const char* texturePath, Vector2 firstPosition = { 0,0 }, Vector2 pivotPoint = { 0.5f,0.5f });
    ~Pacman();
    void Move();
    void Interact();
    void Render(bool debugging);
    Vector2Int GetTile();
};