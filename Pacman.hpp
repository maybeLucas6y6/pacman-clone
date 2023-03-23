#pragma once

#include <raylib.h>
#include "Vector2.hpp"
#include "Node.hpp"

class Pacman {
private:
	vector2 position;
	float speed;
	Node* currentNode;
	Node* targetNode;
	vector2 direction;
	bool OvershotTarget() {
		if (targetNode) {
			vector2 start2dest = targetNode->Position() - currentNode->Position();
			vector2 pos2dest = position - currentNode->Position();
			return pos2dest.magnitudeSquared() >= start2dest.magnitudeSquared();
		}
		return false; // change this ???
	}
	Node* GetNewTarget(vector2& direction, Node* node) {
		if (direction == vector2::Up() && node->ngh.Up) { return node->ngh.Up; }
		else if (direction == vector2::Right() && node->ngh.Right) { return node->ngh.Right; }
		else if (direction == vector2::Down() && node->ngh.Down) { return node->ngh.Down; }
		else if (direction == vector2::Left() && node->ngh.Left) { return node->ngh.Left; }
		else { return nullptr; }
	}
	vector2 GetNewDirection() const {
		auto key = GetKeyPressed();
		switch (key) {
			case KeyboardKey::KEY_W: return vector2::Up();
			case KeyboardKey::KEY_D: return vector2::Right();
			case KeyboardKey::KEY_S: return vector2::Down();
			case KeyboardKey::KEY_A: return vector2::Left();
			default: return vector2::Zero();
		}
	}
public:
	Pacman(Node* startNode) :
		position{ startNode->Position() },
		currentNode{ startNode },
		targetNode{ startNode },
		direction{} {
		speed = 75.;
	}
	void Move(float deltaTime) {
		position = position + (direction * speed * deltaTime); 
		vector2 newDirection{ GetNewDirection() };
		if (direction != 0 && newDirection == direction * -1) {
			direction = direction * -1;
			std::swap(currentNode, targetNode);
		}
		if (OvershotTarget()) {
			currentNode = targetNode;
			position = currentNode->Position();
			Node* newTarget = GetNewTarget(direction, currentNode);
			if (newTarget == nullptr) {
				direction = vector2::Zero();
			}
			else {
				targetNode = newTarget;
			}
		}
		if (newDirection == vector2::Zero() || direction == newDirection) {
			return;
		}
		if (targetNode->Position().equal(position, 10.)) {
			Node* newTarget = GetNewTarget(newDirection, targetNode);
			if (newTarget != nullptr) {
				currentNode = targetNode;
				targetNode = newTarget;
				direction = newDirection;
				position = currentNode->Position();
				return;
			}
		}
		if (currentNode->Position().equal(position, 10.)) {
			Node* newTarget = GetNewTarget(newDirection, currentNode);
			if (newTarget != nullptr) {
				targetNode = newTarget;
				direction = newDirection;
				position = currentNode->Position();
				return;
			}
		}
	}
	void Render() {
		DrawCircle(position.x, position.y, 10., YELLOW);
	}
};