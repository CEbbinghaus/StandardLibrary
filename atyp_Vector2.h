#pragma once
//#include <assert.h>
#include <memory>

class Vector2{
public:
	enum class position{
		x,
		y
	};

	union{
		struct{
			float x, y;
		};
		float data[2];
	};

	Vector2() {
		memset(data, 0, sizeof(float) * 2);
	}

	Vector2(float a_x, float a_y) {
		x = a_x;
		y = a_y;
	}


	Vector2 copy() const {
		return Vector2(x, y);
	}

	Vector2 inverse(){
		return Vector2(-x, -y);
	}

	float magnitude() {
		return sqrtf(x * x + y * y);
	}

	float magnitudeSqr() {
		return x * x + y * y;
	}

	Vector2& normalise() {
		float mag = magnitude();
		//assert(mag != 0.0f && "Magnitude is 0. Cannot Divide");
		x /= mag;
		y /= mag;
		return *this;
	}

	float dot(const Vector2& rhs) {
		return x * rhs.x + y * rhs.y;
	}

	Vector2 right() {
		return Vector2(y, -x);
	}

	Vector2 operator+(const Vector2& rhs) {
		return Vector2(x + rhs.x, y + rhs.y);
	}

	Vector2 operator-(const Vector2& rhs) {
		return Vector2(x - rhs.x, y - rhs.y);
	}

	Vector2 operator*(float rhs) {
		return Vector2(x * rhs, y * rhs);
	}

	Vector2 operator/(float rhs) {
		return Vector2(x / rhs, y / rhs);
	}

	Vector2& operator+=(const Vector2& rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	Vector2& operator-=(const Vector2& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	Vector2& operator*=(float rhs) {
		x *= rhs;
		y *= rhs;
		return *this;
	}

	Vector2& operator/=(float rhs) {
		x /= rhs;
		y /= rhs;
		return *this;
	}

	float& operator[](int index) {
		return *((float*)this + index);
	}

	operator float* () {
		return (float*)this;
	}
};

inline Vector2 operator*(float lhs, Vector2 rhs) {
	return Vector2(rhs.x * lhs, rhs.y * lhs);
}