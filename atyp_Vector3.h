#pragma once
#include <memory>
#include "atyp_Vector2.h"

class Vector3
{
public:
	enum class position{
		x,
		y,
		z
	};

	union {
		struct{
			float x, y, z;
		};
		struct {
			float x, y, z;
		} pos;
		struct {
			float r, g, b;
		} colRGB;
		struct {
			float s, t, q;
		} ;
		struct {
			float u, v, w;
		} textcoord;
		struct {
			float h, s;
			union {
				float l, v;
			};
		} colHSL;
		float data[3];
	};

	Vector3();
	Vector3(float* data);
	Vector3(float x, float y, float z);

	float magnitude();
	float magnitudeSqr();
	Vector3& normalise();

	float dot(const Vector3& rhs);

	Vector3 copy() const;

	Vector3 operator+(const Vector3& rhs);
	Vector3 operator-(const Vector3& rhs);
	Vector3 operator*(float rhs);
	Vector3 operator/(float rhs);

	Vector3& operator+=(const Vector3& rhs);
	Vector3& operator-=(const Vector3& rhs);
	Vector3& operator*=(float rhs);
	Vector3& operator/=(float rhs);

	float& operator[](int index);
	operator float*();

	Vector3 cross(const Vector3&);
};

Vector3 operator*(const float, const Vector3&);

/*
#include <cmath>


Vector3::Vector3(){
	x = y = z = 0;
}

Vector3::Vector3(float* ptr){
	memcpy(data, ptr, sizeof(float) * 3);
}

Vector3::Vector3(float a_x, float a_y, float a_z){
	x = a_x;
	y = a_y;
	z = a_z;
}

float Vector3::magnitude(){
	return sqrtf(x * x + y * y + z * z);
}

float Vector3::magnitudeSqr(){
	return x * x + y * y + z * z;
}

Vector3& Vector3::normalise(){
	float mag = magnitude();
	x /= mag;
	y /= mag;
	z /= mag;
	return *this;
}

float Vector3::dot(const Vector3 & rhs){
	return (x * rhs.x + y * rhs.y + z * rhs.z);
}

Vector3 Vector3::copy() const{
	return Vector3(x, y, z);
}

Vector3 Vector3::operator+(const Vector3 & rhs){
	return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
}

Vector3 Vector3::operator-(const Vector3 & rhs){
	return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
}

Vector3 Vector3::operator*(float rhs){
	return Vector3(x * rhs, y * rhs, z * rhs);
}

Vector3 Vector3::operator/(float rhs){
	return Vector3(x / rhs, y / rhs, z / rhs);
}

Vector3 & Vector3::operator+=(const Vector3 & rhs){
	x += rhs.x;
	y += rhs.y;
	return *this;
}

Vector3 & Vector3::operator-=(const Vector3 & rhs){
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

Vector3& Vector3::operator*=(float rhs){
	x *= rhs;
	y *= rhs;
	return *this;
}

Vector3& Vector3::operator/=(float rhs){
	x /= rhs;
	y /= rhs;
	return *this;
}

float& Vector3::operator[](int index){
	return *((float*)this + index);
}

Vector3::operator float*(){
	return (float*)this;
}

Vector3 Vector3::cross(const Vector3& other)
{
	return Vector3(
		y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x
	);
}

Vector3 operator*(const float n, const Vector3& rhs){
	return Vector3(rhs.x * n, rhs.y * n, rhs.z * n);
}
