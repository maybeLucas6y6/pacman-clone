#pragma once

#include <math.h>
#include <iostream>

class vector2 {
private:
	float x, y;
public:
	vector2(float x, float y) {
		this->x = x;
		this->y = y;
	}
	vector2 operator + (vector2& vec) {
		return { x + vec.x, y + vec.y };
	}
	vector2 operator - (vector2& vec) {
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
	bool equal(vector2& vec, float thresh) {
		if (fabs(x - vec.x) <= thresh) {
			if (fabs(y - vec.y) <= thresh) {
				return true;
			}
		}
		return false;
	}
	float magnitudeSquared() {
		return x * x + y * y;
	}
	float magnitude() {
		return sqrtf(magnitudeSquared());
	}
	friend std::ostream& operator << (std::ostream& os, vector2 const& vec) {
		os << "x: " << vec.x << " y: " << vec.y << "\n";
		return os;
	}
	// TODO: return as tuple
};