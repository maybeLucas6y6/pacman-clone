#pragma once

#include <math.h>
#include <iostream>

class vector2 {
public:
	float x, y;
	vector2(float x = 0., float y = 0.) : 
		x{ x }, y{ y } {
		
	}
	vector2 operator + (const vector2& vec) {
		return { x + vec.x, y + vec.y };
	}
	vector2 operator - (const vector2& vec) {
		return { x - vec.x, y - vec.y };
	}
	vector2 operator + (float scalar) {
		return { x + scalar, y + scalar };
	}
	vector2 operator - (float scalar) {
		return { x - scalar, y - scalar };
	}
	vector2 operator * (float scalar) {
		return { x * scalar, y * scalar };
	}
	vector2 operator / (float scalar) {
		if(scalar != 0)
			return { x / scalar, y / scalar };
	}
	bool operator == (const vector2& vec) {
		return x == vec.x && y == vec.y;
		//return equal(vec, 0.0001f);
	}
	bool operator != (const vector2& vec) {
		return x != vec.x || y != vec.y;
		//return !equal(vec, 0.0001f);
	}
	bool equal(const vector2& vec, float thresh) const {
		if (fabs(x - vec.x) <= thresh) {
			if (fabs(y - vec.y) <= thresh) {
				return true;
			}
		}
		return false;
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
};