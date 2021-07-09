#pragma once
#include "atyp_Vector2.h"
#include "atyp_Vector4.h"
#include <memory>

class Vector4
{
public:
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

	
	static Vector4 one() {
		return Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	}
	
	static Vector4 zero() {
		return Vector4(0.0, 0.0, 0.0, 0.0f);
	}

	static Vector4 right() {
		return Vector4(1.0f, 0.0, 0.0, 0.0f);
	}

	static Vector4 up() {
		return Vector4(0.0f, 1.0f, 0.0f, 0.0f);
	}

	static Vector4 forward() {
		return Vector4(0.0, 0.0, 1.0f, 0.0f);
	}

	static float dot(const Vector4& a, const Vector4& b) {
		return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
	}

	static Vector4 clamp(const Vector4& value, const Vector4& min, const Vector4& max){
		Vector4 result;
		result.x = (value.x < min.x ? min.x : (value.x > max.x ? max.x : value.x));
		result.y = (value.y < min.y ? min.y : (value.y > max.y ? max.y : value.y));
		result.z = (value.z < min.z ? min.z : (value.z > max.z ? max.z : value.z));
		result.w = (value.w < min.w ? min.w : (value.w > max.w ? max.w : value.w));
		return result;
	}

	static Vector4 Abs(const Vector4& value){
		return Vector4(abs(value.x), abs(value.y), abs(value.z), abs(value.w));
	}

	Vector4() {
		x = y = z = w = 0;
	}

	Vector4(const Vector2& v, float z, float w) {
		x = v.x;
		y = v.y;
		
		this->z = z;
		this->w = w;
	}

	Vector4(const Vector3& v, float w) {
		x = v.x;
		y = v.y;
		z = v.z;
		
		this->w = w;
	}

	Vector4(float a_x, float a_y, float a_z, float a_w) {
		x = a_x;
		y = a_y;
		z = a_z;
		w = a_w;
	}

  #ifdef _CSTDIO_
	void Print() const{
		printf("%.2f, %.2f, %.2f, %.2f\n", x, y, z, w);
	}
  #endif

	Vector4 copy() const {
		return Vector4(x, y, z, w);
	}

	float magnitude() const {
		return sqrtf(x * x + y * y + z * z + w + w);
	}

	float magnitudeSqr() const {
		return x * x + y * y + z * z + w + w;
	}

	Vector4& normalise() {
		float mod = magnitude();
		if(mod == 0.0)return *this;
		x /= mod;
		y /= mod;
		z /= mod;
		w /= mod;
		return *this;
	}

	Vector4 normalise() const {
		float mod = magnitude();
		if(mod == 0.0)return *this;
		return Vector4(x / mod, y / mod, z / mod, w / mod);
	}

	float dot(const Vector4& rhs) const {
		return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
	}

	Vector4 operator+(const Vector4& rhs) const {
		return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
	}

	Vector4 operator-(const Vector4& rhs) const {
		return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
	}

	Vector4 operator*(float rhs) const {
		return Vector4(x * rhs, y * rhs, z * rhs, w * rhs);
	}

	Vector4 operator/(float rhs) const {
		return Vector4(x / rhs, y / rhs, z / rhs, w / rhs);
	}


	Vector4& operator+=(const Vector4& rhs) {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		w += rhs.w;
		return *this;
	}

	Vector4& operator-=(const Vector4& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		w -= rhs.w;
		return *this;
	}

	Vector4& operator*=(float rhs) {
		x *= rhs;
		y *= rhs;
		z *= rhs;
		w *= rhs;
		return *this;
	}

	Vector4& operator/=(float rhs) {
		x /= rhs;
		y /= rhs;
		z /= rhs;
		w /= rhs;
		return *this;
	}

	bool operator==(const Vector4& rhs) const{
		return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
	}
	
	bool operator!=(const Vector4& rhs) const{
		return !(*this == rhs);
	}

	float& operator[](int index) const {
		return *((float*)this + index);
	}

	operator float* () const {
		return (float*)this;
	}
	
	operator Vector3() const {
		return Vector3(x, y, z);
	}
	
	operator Vector2() const {
		return Vector2(x, y);
	}

	Vector4 cross(const Vector4& rhs) const {
		Vector4 result(*this);
		*((Vector4*)& result) = (*((Vector4*)& result)).cross(*((Vector4*)& rhs));
		result.w = 0;
		return  result;
	}

	Vector4 operator-() const {
		return Vector4(-x, -y, -z, -w);
	}
};

inline Vector4 operator*(float lhs, Vector4 rhs) {
	return Vector4(rhs.x * lhs, rhs.y * lhs, rhs.z * lhs, rhs.w * lhs);
}