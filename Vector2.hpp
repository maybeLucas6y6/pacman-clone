#pragma once

#include <math.h>
#include <iostream>

class vector2 {
public:
	float x, y;
	vector2(float x = 0., float y = 0.) : 
		x{ x }, y{ y } {
		
	}
	vector2 operator + (vector2 vec) {
		return { x + vec.x, y + vec.y };
	}
	vector2 operator - (vector2 vec) {
		return { x - vec.x, y - vec.y };
	}
	vector2 operator + (float scalar) {
		return { x + scalar, y + scalar };
	}
	vector2 operator - (float scalar) {
		return { x - scalar, y - scalar };
	}
	vector2 operator * (vector2 vec) {
		return { x * vec.x, y * vec.y };
	}
	vector2 operator / (vector2 vec) {
		return { x / vec.x, y / vec.y };
	}
	vector2 operator * (float scalar) {
		return { x * scalar, y * scalar };
	}
	vector2 operator / (float scalar) {
		if(scalar != 0)
			return { x / scalar, y / scalar };
	}
	bool operator == (vector2 vec) {
		return x == vec.x && y == vec.y;
	}
	bool operator != (vector2 vec) {
		return x != vec.x || y != vec.y;
	}
	bool equalAnd(const vector2& vec, float thresh) const {
		if (fabsf(x - vec.x) <= thresh && fabsf(y - vec.y) <= thresh) return true;
		else return false;
	}
	bool equalOr(const vector2& vec, float thresh) const {
		if (fabsf(x - vec.x) <= thresh || fabsf(y - vec.y) <= thresh) return true;
		else return false;
	}
	float magnitudeSquared() const  {
		return x * x + y * y;
	}
	float magnitude() const  {
		return sqrtf(magnitudeSquared());
	}
	// TODO: return as tuple
	friend std::ostream& operator << (std::ostream& os, vector2 const& vec) {
		os << "x: " << vec.x << " y: " << vec.y << "\n";
		return os;
	}
	static vector2 Up() {
		return { 0,-1 };
	}
	static vector2 Right() {
		return { 1,0 };
	}
	static vector2 Down() {
		return { 0,1 };
	}
	static vector2 Left() {
		return { -1,0 };
	}
	static vector2 Zero() {
		return { 0,0 };
	}
	static float Distance(vector2 a, vector2 b) {
		return sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	}

	// not necessary
	Vector2 RaylibVector2() {
		return { x, y };
	}
	static vector2 AdditionResult(vector2 a, vector2 b, vector2 origin = vector2::Zero()) {
		return { 2 * (a.x + b.x) - origin.x, 2 * (a.y + b.y) - origin.y };
	}
};