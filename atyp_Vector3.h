#pragma once
#include <memory>
#include "atyp_Vector2.h"

class Quaternion;
template <
	typename T = float,
	std::enable_if<std::is_arithmetic_v<T>, T> * = nullptr
>
class Vector3{
public:
	enum class position{
		x,
		y,
		z
	};

	union{
		struct{
			T x, y, z;
		};
		struct{
			T x, y, z;
		} pos;
		struct{
			T r, g, b;
		} colRGB;
		struct{
			T s, t, q;
		};
		struct{
			T u, v, w;
		} textcoord;
		struct{
			T h, s;
			union{
				T l, v;
			};
		} colHSL;
		T data[3];
	};

	static Vector3<T> FaceNormal(Vector3<T> a, Vector3<T> b, Vector3<T> c){
		return Vector3<T>::cross(b - a, c - a);
	}

	static Vector3<T> cross(const Vector3<T>& a, const Vector3<T>& b){
		return Vector3<T>(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
		);
	}


	static Vector3<T> one(){
		return Vector3<T>(1.0, 1.0, 1.0);
	}

	static Vector3<T> zero(){
		return Vector3<T>(0.0, 0.0, 0.0);
	}

	static Vector3<T> right(){
		return Vector3<T>(1, 0.0, 0.0);
	}

	static Vector3<T> up(){
		return Vector3<T>(0.0, 1, 0.0);
	}

	static Vector3<T> forward(){
		return Vector3<T>(0.0, 0.0, 1);
	}

	Vector3(){
		x = y = z = T(0);
	}

	Vector3(T s){
		x = y = z = s;
	}

	Vector3(Vector2 v, T s){
		x = v.x;
		y = v.y;
		z = s;
	}

	Vector3(T* ptr){
		memcpy(data, ptr, sizeof(T) * 3);
	}

	Vector3(T a_x, T a_y, T a_z){
		x = a_x;
		y = a_y;
		z = a_z;
	}

	void Print(){
		printf("%.2f, %.2f, %.2f\n", x, y, z);
	}

	T magnitude(){
		return sqrt(x * x + y * y + z * z);
	}

	T magnitudeSqr(){
		return x * x + y * y + z * z;
	}

	Vector3<T>& normalise(){
		T mag = magnitude();
		x /= mag;
		y /= mag;
		z /= mag;
		return *this;
	}

	T dot(const Vector3<T>& rhs){
		return (x * rhs.x + y * rhs.y + z * rhs.z);
	}

	Vector3<T> copy() const{
		return Vector3<T>(x, y, z);
	}

	Vector3<T> operator+(const Vector3<T>& rhs){
		return Vector3<T>(x + rhs.x, y + rhs.y, z + rhs.z);
	}

	Vector3<T> operator-(const Vector3<T>& rhs){
		return Vector3<T>(x - rhs.x, y - rhs.y, z - rhs.z);
	}

	Vector3<T> operator*(T rhs){
		return Vector3<T>(x * rhs, y * rhs, z * rhs);
	}

	Vector3<T> operator*(Vector3<T> rhs){
		return Vector3<T>(x * rhs.x, y * rhs.y, z * rhs.z);
	}

	Vector3<T> operator/(T rhs){
		return Vector3<T>(x / rhs, y / rhs, z / rhs);
	}

	Vector3<T> operator/(Vector3<T> rhs){
		return Vector3<T>(x / rhs.x, y / rhs.y, z / rhs.z);
	}


	Vector3<T>& operator+=(const Vector3<T>& rhs){
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	Vector3<T>& operator-=(const Vector3<T>& rhs){
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	Vector3<T>& operator*=(T rhs){
		x *= rhs;
		y *= rhs;
		z *= rhs;
		return *this;
	}

	Vector3<T>& operator*=(Vector3<T> rhs){
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		return *this;
	}

	Vector3<T>& operator/=(T rhs){
		x /= rhs;
		y /= rhs;
		z /= rhs;
		return *this;
	}

	Vector3<T>& operator/=(Vector3<T> rhs){
		x /= rhs.x;
		y /= rhs.y;
		z /= rhs.z;
		return *this;
	}

	bool operator==(const Vector3<T>& b){
		bool xEquality = x == b.x;
		bool yEquality = y == b.y;
		bool zEquality = z == b.z;

		return (xEquality && yEquality && zEquality);
	}

	T& operator[](int index){
		return *((T*)this + index);
	}

	operator T* (){
		return (T*)this;
	}

	operator Vector2<T>(){
		return Vector2<T>(x, y);
	}

	Vector3<T> cross(const Vector3<T>& other){
		return Vector3<T>(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x
		);
	}

	Vector3<T>& operator-(){
		x = -x;
		y = -y;
		z = -z;
		return *this;
	}
};
template <
	typename T = float,
	std::enable_if<std::is_arithmetic_v<T>, T> * = nullptr
>
inline Vector3<T> operator*(const T n, const Vector3<T>& rhs){
	return Vector3<T>(rhs.x * n, rhs.y * n, rhs.z * n);
}
