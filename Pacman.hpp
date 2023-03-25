#pragma once

#include <raylib.h>
#include "Vector2.hpp"
#include "Node.hpp"

class Pacman {
private:
	vector2 position;
	float speed;
	float actualSpeed;
	Node* currentNode;
	Node* targetNode;
	vector2 direction;
	vector2 turnDirection;
	bool OvershotTarget() {
		if (targetNode != nullptr) {
			vector2 start2dest = targetNode->Position() - currentNode->Position();
			vector2 pos2dest = position - currentNode->Position();
			return pos2dest.magnitudeSquared() >= start2dest.magnitudeSquared();
		}
		return false; // change this ???
	}
	Node* GetNewTarget(vector2& direction, Node* node) const {
		if (node == nullptr) return nullptr;
		if (direction == vector2::Up() && node->ngh.Up) { return node->ngh.Up; }
		if (direction == vector2::Right() && node->ngh.Right) { return node->ngh.Right; }
		if (direction == vector2::Down() && node->ngh.Down) { return node->ngh.Down; }
		if (direction == vector2::Left() && node->ngh.Left) { return node->ngh.Left; }
		return nullptr;
	}
	vector2 GetNewDirection() const {
		if (IsKeyDown(KeyboardKey::KEY_W)) return vector2::Up();
		if (IsKeyDown(KeyboardKey::KEY_D)) return vector2::Right();
		if (IsKeyDown(KeyboardKey::KEY_S)) return vector2::Down();
		if (IsKeyDown(KeyboardKey::KEY_A)) return vector2::Left();
		return vector2::Zero();
	}
public:
	Pacman(Node* startNode) :
		position{ startNode->Position() },
		currentNode{ startNode },
		targetNode{ startNode },
		direction{},
		turnDirection{} {
		speed = 75.;
		actualSpeed = 0;
	}
	void Move(float deltaTime) {
		actualSpeed = speed * deltaTime;
		if (actualSpeed > 0.02) actualSpeed = 0.02;
		position = position + ((direction + turnDirection) * actualSpeed);
		if (turnDirection != vector2::Zero()) {
			if (position.equalOr(targetNode->Position(), 0.02)) {
				direction = turnDirection;
				turnDirection = vector2::Zero();
			}
			return;
		}
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
		float position2target = vector2::Distance(position, targetNode->Position());
		if (position2target <= 6.) {
			Node* newTarget = GetNewTarget(newDirection, targetNode);
			if (newTarget != nullptr) {
				currentNode = targetNode;
				targetNode = newTarget;
				turnDirection = newDirection;
			}
		}
		float position2current = vector2::Distance(position, currentNode->Position());
		if (position2current <= 4.) {
			Node* newTarget = GetNewTarget(newDirection, currentNode);
			if (newTarget != nullptr) {
				targetNode = newTarget;
				direction = direction * -1;
				turnDirection = newDirection;
			}
		}
	}
	void Render() {
		DrawCircle(position.x, position.y, 10., YELLOW);
	}
};