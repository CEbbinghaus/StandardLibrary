#pragma once
#include <cmath>
#include <cstdio>

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

	static Vector2 up() {
		return Vector2(0.0f, 1.0f);
	}

	static Vector2 right() {
		return Vector2(1.0f, 0.0f);
	}

	static Vector2 one() {
		return Vector2(1.0f);
	}

	static Vector2 zero() {
		return Vector2(0.0f);
	}

	static float dot(const Vector2& a, const Vector2& b) {
		return (a.x * b.x + a.y * b.y);
	}

	static Vector2 clamp(const Vector2& value, const Vector2& min, const Vector2& max){
		Vector2 result;
		result.x = (value.x < min.x ? min.x : (value.x > max.x ? max.x : value.x));
		result.y = (value.y < min.y ? min.y : (value.y > max.y ? max.y : value.y));
		return result;
	}

	static Vector2 Abs(const Vector2& value){
		return Vector2(abs(value.x), abs(value.y));
	}

	Vector2() {
		data[0] = data[1] = 0;
	}

	Vector2(float v) {
		data[0] = data[1] = v;
	}

	Vector2(float a_x, float a_y) {
		x = a_x;
		y = a_y;
	}

#ifdef _CSTDIO_

	void Print(){
		printf("%.2f, %.2f\n", x, y);
	}

#endif // _CSTDIO_

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
		if(mag == 0.0f)return *this;
		x /= mag;
		y /= mag;
		return *this;
	}

	float dot(const Vector2& rhs) {
		return x * rhs.x + y * rhs.y;
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