#pragma once
#include "atyp_Vector3.h"
#include <memory>
struct Vector4
{
	enum class position{
		x,
		y,
		z,
		w
	};

	union{
		struct {
			float x, y, z, w;
		};
		float data[4];
	};

	Vector4();
	Vector4(float x, float y, float z, float w);

	Vector4 copy()  const;

	float magnitude();
	float magnitudeSqr();
	Vector4& normalise();

	float dot(const Vector4& rhs);

	Vector4 operator+(const Vector4& rhs);
	Vector4 operator-(const Vector4& rhs);
	Vector4 operator*(float rhs);
	Vector4 operator/(float rhs);

	Vector4& operator+=(const Vector4& rhs);
	Vector4& operator-=(const Vector4& rhs);
	Vector4& operator*=(float rhs);
	Vector4& operator/=(float rhs);

	float& operator[](int index);
	operator float*();

	Vector4 cross(const Vector4&);
};

Vector4 operator*(float lhs, Vector4 rhs);

/*

#include "Vector4.h"



Vector4::Vector4(){
	x = y = z = w = 0;
}

Vector4::Vector4(float a_x, float a_y, float a_z, float a_w){
	x = a_x;
	y = a_y;
	z = a_z;
	w = a_w;
}

Vector4 Vector4::copy() const{
	return Vector4(x, y, z, w);
}

float Vector4::magnitude(){
	return sqrtf(x * x + y * y + z * z + w + w);
}

float Vector4::magnitudeSqr(){
	return x * x + y * y + z * z + w + w;
}

Vector4& Vector4::normalise(){
	float mod = magnitude();
	x /= mod;
	y /= mod;
	z /= mod;
	w /= mod;
	return *this;
}

float Vector4::dot(const Vector4 & rhs){
	return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
}

Vector4 Vector4::operator+(const Vector4 & rhs){
	return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

Vector4 Vector4::operator-(const Vector4 & rhs){
	return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

Vector4 Vector4::operator*(float rhs){
	return Vector4(x * rhs, y * rhs, z * rhs, w * rhs);
}

Vector4 Vector4::operator/(float rhs){
	return Vector4(x / rhs, y / rhs, z / rhs, w / rhs);
}

Vector4 & Vector4::operator+=(const Vector4 & rhs){
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	w += rhs.w;
	return *this;
}

Vector4 & Vector4::operator-=(const Vector4 & rhs){
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	w -= rhs.w;
	return *this;
}

Vector4& Vector4::operator*=(float rhs){
	x *= rhs;
	y *= rhs;
	z *= rhs;
	w *= rhs;
	return *this;
}

Vector4& Vector4::operator/=(float rhs){
	x /= rhs;
	y /= rhs;
	z /= rhs;
	w /= rhs;
	return *this;
}

float & Vector4::operator[](int index){
	return *((float*)this + index);
}
Vector4::operator float*(){
	return (float*)this;
}

Vector4 Vector4::cross(const Vector4& rhs){
	Vector4 result(*this);
	*((Vector3*)&result) = (*((Vector3*)&result)).cross(*((Vector3*)&rhs));
	result.w = 0;
	return  result;
}

Vector4 operator*(float lhs, Vector4 rhs){
	return Vector4(rhs.x * lhs, rhs.y * lhs, rhs.z * lhs, rhs.w * lhs);
}
