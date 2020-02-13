#pragma once
#include <memory>
#include "atyp_Vector2.h"

class Quaternion;

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

	static Vector3 FaceNormal(Vector3 a, Vector3 b, Vector3 c){
		return Vector3::cross(b - a, c - a);
	}

	static Vector3 cross(const Vector3& a, const Vector3& b){
		return Vector3(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
		);
	}


	static Vector3 one() {
		return Vector3(1.0, 1.0, 1.0);
	}
	
	static Vector3 zero() {
		return Vector3(0.0, 0.0, 0.0);
	}

	static Vector3 right() {
		return Vector3(1, 0.0, 0.0);
	}

	static Vector3 up() {
		return Vector3(0.0, 1, 0.0);
	}

	static Vector3 forward() {
		return Vector3(0.0, 0.0, 1);
	}

	Vector3() {
		x = y = z = 0;
	}
	
	Vector3(float s) {
		x = y = z = s;
	}
	
	Vector3(Vector2 v, float s) {
		x = v.x;
		y = v.y;
		z = s;
	}

	Vector3(float* ptr) {
		memcpy(data, ptr, sizeof(float) * 3);
	}

	Vector3(float a_x, float a_y, float a_z) {
		x = a_x;
		y = a_y;
		z = a_z;
	}

	void Print(){
		printf("%.2f, %.2f, %.2f\n", x, y, z);
	}

	float magnitude() {
		return sqrtf(x * x + y * y + z * z);
	}

	float magnitudeSqr() {
		return x * x + y * y + z * z;
	}

	Vector3& normalise() {
		float mag = magnitude();
		x /= mag;
		y /= mag;
		z /= mag;
		return *this;
	}

	float dot(const Vector3& rhs) {
		return (x * rhs.x + y * rhs.y + z * rhs.z);
	}

	Vector3 copy() const {
		return Vector3(x, y, z);
	}

	Vector3 operator+(const Vector3& rhs) {
		return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
	}

	Vector3 operator-(const Vector3& rhs) {
		return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
	}

	Vector3 operator*(float rhs) {
		return Vector3(x * rhs, y * rhs, z * rhs);
	}
	
	Vector3 operator*(Vector3 rhs) {
		return Vector3(x * rhs.x, y * rhs.y, z * rhs.z);
	}

	Vector3 operator/(float rhs) {
		return Vector3(x / rhs, y / rhs, z / rhs);
	}
	
	Vector3 operator/(Vector3 rhs) {
		return Vector3(x / rhs.x, y / rhs.y, z / rhs.z);
	}


	Vector3& operator+=(const Vector3& rhs) {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	Vector3& operator-=(const Vector3& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	Vector3& operator*=(float rhs) {
		x *= rhs;
		y *= rhs;
		z *= rhs;
		return *this;
	}

	Vector3& operator*=(Vector3 rhs) {
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		return *this;
	}

	Vector3& operator/=(float rhs) {
		x /= rhs;
		y /= rhs;
		z /= rhs;
		return *this;
	}

	Vector3& operator/=(Vector3 rhs) {
		x /= rhs.x;
		y /= rhs.y;
		z /= rhs.z;
		return *this;
	}

	bool operator==(const Vector3& b) {
		bool xEquality = x == b.x;
		bool yEquality = y == b.y;
		bool zEquality = z == b.z;

		return (xEquality && yEquality && zEquality);
	}

	float& operator[](int index) {
		return *((float*)this + index);
	}

	operator float* () {
		return (float*)this;
	}

	operator Vector2() {
		return Vector2(x, y);
	}

	Vector3 cross(const Vector3& other){
		return Vector3(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x
		);
	}

	Vector3& operator-(){
		x = -x;
		y = -y;
		z = -z;
		return *this;
	}
};

inline Vector3 operator*(const float n, const Vector3& rhs){
	return Vector3(rhs.x * n, rhs.y * n, rhs.z * n);
}