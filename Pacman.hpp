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
	bool normal = true; // don t forget to delete this
	bool OvershotTarget() {
		if (targetNode) {
			vector2 start2dest = targetNode->Position() - currentNode->Position();
			vector2 pos2dest = position - currentNode->Position();
			return pos2dest.magnitudeSquared() >= start2dest.magnitudeSquared();
		}
		else {
			return false; // change this ???
		}
	}
	bool IsDirectionValid(vector2& direction) {
		if (direction == vector2::Up() && (*currentNode).ngh.Up) { targetNode = currentNode->ngh.Up; return true; }
		else if (direction == vector2::Right() && (*currentNode).ngh.Right) { targetNode = currentNode->ngh.Right; return true; }
		else if (direction == vector2::Down() && (*currentNode).ngh.Down) { targetNode = currentNode->ngh.Down; return true; }
		else if (direction == vector2::Left() && (*currentNode).ngh.Left) { targetNode = currentNode->ngh.Left; return true; }
		else { targetNode = currentNode; return false; }
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
		speed = 10.;
	}
	void Move(float deltaTime) {
		normal = true;
		position = position + (direction * speed * deltaTime); 
		vector2 newDirection{ GetNewDirection() };
		if (targetNode->Position().equal(position, 10.)) {
			normal = false;
			SetNewTarget(newDirection);
			if (targetNode != currentNode) {
				direction = newDirection;
			}
			else {
				SetNewTarget(direction);
			}
			if (targetNode == currentNode) {
				direction = vector2::Zero();
			}
			position = currentNode->Position();
		}
		else {
			if (currentNode->Position().equal(position, 10.)) {
				normal = false;
				currentNode = targetNode;
				SetNewTarget(newDirection);
				if (targetNode != currentNode) {
					direction = newDirection;
				}
				else {
					SetNewTarget(direction);
				}
				if (targetNode == currentNode) {
					direction = vector2::Zero();
				}
				position = currentNode->Position();
			}
		}
		if (OvershotTarget()) {
			normal = false; 
			currentNode = targetNode;
			SetNewTarget(newDirection);
			if (targetNode != currentNode) {
				direction = newDirection;
			}
			else {
				SetNewTarget(direction);
			}
			if (targetNode == currentNode) {
				direction = vector2::Zero();
			}
			position = currentNode->Position();
		}
		else {
			if (direction != 0 && newDirection == direction * -1) {
				direction = direction * -1;
				std::swap(currentNode, targetNode);
			}
		}
	}
	void Render() {
		if (normal) {
			DrawCircle(position.x, position.y, 10., YELLOW);
		}
		else {
			DrawCircle(position.x, position.y, 10., RED);
		}
	}
};