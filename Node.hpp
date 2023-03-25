#pragma once

#include "Vector2.hpp"
#include <raylib.h>

class Node {
private:
	vector2 position;
public:
	struct neighbours {
		Node* Up;
		Node* Right;
		Node* Down;
		Node* Left;
	} ngh;
	Node(float x, float y, Node* up, Node* right, Node* down, Node* left) :
		position{ x, y },
		ngh{ up, right, down, left } {

	}
	void Render() {
		DrawCircle(position.x, position.y, 12., DARKGRAY);
		if (ngh.Up) DrawLine(position.x, position.y, ngh.Up->position.x, ngh.Up->position.y, GRAY);
		if (ngh.Right) DrawLine(position.x, position.y, ngh.Right->position.x, ngh.Right->position.y, GRAY);
		if (ngh.Down) DrawLine(position.x, position.y, ngh.Down->position.x, ngh.Down->position.y, GRAY);
		if (ngh.Left) DrawLine(position.x, position.y, ngh.Left->position.x, ngh.Left->position.y, GRAY);
	}
	vector2 Position() const {
		return position;
	}
};