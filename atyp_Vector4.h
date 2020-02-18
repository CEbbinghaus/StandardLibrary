#pragma once
#include "atyp_Vector2.h"
#include "atyp_Vector3.h"
#include <memory>

template <
	typename T = float,
	std::enable_if<std::is_arithmetic_v<T>, T> * = nullptr
>
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
			T x, y, z, w;
		};
		T data[4];
	};

	Vector4() {
		x = y = z = w = T(0);
	}

	Vector4(Vector2<T> v, T z, T w) {
		x = v.x;
		y = v.y;
		
		this->z = z;
		this->w = w;
	}

	Vector4(Vector3<T> v, T w) {
		x = v.x;
		y = v.y;
		z = v.z;
		
		this->w = w;
	}

	Vector4(T a_x, T a_y, T a_z, T a_w) {
		x = a_x;
		y = a_y;
		z = a_z;
		w = a_w;
	}

	void Print(){
		printf("%.2f, %.2f, %.2f, %.2f\n", x, y, z, w);
	}

	Vector4<T> copy() const {
		return Vector4<T>(x, y, z, w);
	}

	T magnitude() {
		return sqrtf(x * x + y * y + z * z + w + w);
	}

	T magnitudeSqr() {
		return x * x + y * y + z * z + w + w;
	}

	Vector4<T>& normalise() {
		T mod = magnitude();
		x /= mod;
		y /= mod;
		z /= mod;
		w /= mod;
		return *this;
	}

	T dot(const Vector4<T>& rhs) {
		return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
	}

	Vector4<T> operator+(const Vector4<T>& rhs) {
		return Vector4<T>(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
	}

	Vector4<T> operator-(const Vector4<T>& rhs) {
		return Vector4<T>(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
	}

	Vector4<T> operator*(T rhs) {
		return Vector4<T>(x * rhs, y * rhs, z * rhs, w * rhs);
	}

	Vector4<T> operator/(T rhs) {
		return Vector4<T>(x / rhs, y / rhs, z / rhs, w / rhs);
	}


	Vector4<T>& operator+=(const Vector4<T>& rhs) {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		w += rhs.w;
		return *this;
	}

	Vector4<T>& operator-=(const Vector4<T>& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		w -= rhs.w;
		return *this;
	}

	Vector4<T>& operator*=(T rhs) {
		x *= rhs;
		y *= rhs;
		z *= rhs;
		w *= rhs;
		return *this;
	}

	Vector4<T>& operator/=(T rhs) {
		x /= rhs;
		y /= rhs;
		z /= rhs;
		w /= rhs;
		return *this;
	}

	T& operator[](int index) {
		return *((T*)this + index);
	}

	operator T* () {
		return (T*)this;
	}
	
	operator Vector3<T>() {
		return Vector3(x, y, z);
	}
	
	operator Vector2<T>() {
		return Vector2(x, y);
	}

	Vector4<T> cross(const Vector4<T>& rhs) {
		Vector4<T> result(*this);
		*((Vector3*)& result) = (*((Vector3*)& result)).cross(*((Vector3*)& rhs));
		result.w = 0;
		return  result;
	}

	Vector4<T>& operator-() {
		x = -x;
		y = -y;
		z = -z;
		w = -w;
		return *this;
	}
};

template <
	typename T = float,
	std::enable_if<std::is_arithmetic_v<T>, T> * = nullptr
>
inline Vector4<T> operator*(T lhs, Vector4<T> rhs) {
	return Vector4<T>(rhs.x * lhs, rhs.y * lhs, rhs.z * lhs, rhs.w * lhs);
}