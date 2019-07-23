#pragma once
#include <assert.h>
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
	Vector2();
	Vector2(float, float);

	Vector2 copy() const;
	Vector2 inverse();

	float magnitude();
	float magnitudeSqr();
	Vector2& normalise();

	float dot(const Vector2& rhs);
	Vector2 right();

	Vector2 operator+(const Vector2& rhs);
	Vector2 operator-(const Vector2& rhs);
	Vector2 operator*(float rhs);
	Vector2 operator/(float rhs);

	Vector2& operator+=(const Vector2& rhs);
	Vector2& operator-=(const Vector2& rhs);
	Vector2& operator*=(float rhs);
	Vector2& operator/=(float rhs);

	float& operator[](int index);

	operator float*();
};

Vector2 operator*(float lhs, Vector2 rhs);

/*


Vector2::Vector2(){
	memset(data, 0, sizeof(float) * 2);
}

Vector2::Vector2(float a_x, float a_y){
	x = a_x;
	y = a_y;
}

Vector2 Vector2::copy() const
{
	return Vector2(x, y);
}

Vector2 Vector2::inverse()
{
	return Vector2(-x, -y);
}

float Vector2::magnitude(){
	return sqrtf(x * x + y * y);
}

float Vector2::magnitudeSqr(){
	return x * x + y * y;
}

Vector2& Vector2::normalise(){
	float mag = magnitude();
	assert(mag != 0.0f && "Magnitude is 0. Cannot Divide");
	x /= mag;
	y /= mag;
	return *this;
}

float Vector2::dot(const Vector2 & rhs){
	return x * rhs.x + y * rhs.y;
}

Vector2 Vector2::right(){
	return Vector2(y, -x);
}

Vector2 Vector2::operator+(const Vector2 & rhs){
	return Vector2(x + rhs.x, y + rhs.y);
}

Vector2 Vector2::operator-(const Vector2 & rhs){
	return Vector2(x - rhs.x, y - rhs.y);
}

Vector2 Vector2::operator*(float rhs){
	return Vector2(x * rhs, y * rhs);
}

Vector2 Vector2::operator/(float rhs){
	return Vector2(x / rhs, y / rhs);
}

Vector2& Vector2::operator+=(const Vector2 & rhs){
	x += rhs.x;
	y += rhs.y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2 & rhs){
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

Vector2& Vector2::operator*=(float rhs){
	x *= rhs;
	y *= rhs;
	return *this;
}

Vector2& Vector2::operator/=(float rhs){
	x /= rhs;
	y /= rhs;
	return *this;
}

float & Vector2::operator[](int index){
	return *((float*)this + index);
}

Vector2::operator float*(){
	return (float*)this;
}

Vector2 operator*(float lhs, Vector2 rhs){
	return Vector2(rhs.x * lhs, rhs.y * lhs);
}
