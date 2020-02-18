#pragma once
#include <cmath>
#include <cstdio>

template <
	typename T = float,
	std::enable_if<std::is_arithmetic_v<T>, T> * = nullptr
>
class Vector2{

public:
	enum class position{
		x,
		y
	};

	union{
		struct{
			T x, y;
		};
		T data[2];
	};

	Vector2() {
		data[0] = data[1] = 0;
	}

	Vector2(T a_x, T a_y) {
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

	T magnitude() {
		return sqrt(x * x + y * y);
	}

	T magnitudeSqr() {
		return x * x + y * y;
	}

	Vector2& normalise() {
		T mag = magnitude();
		if(mag == 0.0f)
			throw "Cannot Divide by 0";
		//assert(mag != 0.0f && "Magnitude is 0. Cannot Divide");
		x /= mag;
		y /= mag;
		return *this;
	}

	T dot(const Vector2& rhs) {
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

	Vector2 operator*(T rhs) {
		return Vector2(x * rhs, y * rhs);
	}

	Vector2 operator/(T rhs) {
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

	Vector2& operator*=(T rhs) {
		x *= rhs;
		y *= rhs;
		return *this;
	}

	Vector2& operator/=(T rhs) {
		x /= rhs;
		y /= rhs;
		return *this;
	}

	T& operator[](int index) {
		return *((T*)this + index);
	}

	operator T* () {
		return (T*)this;
	}
};

template <
	typename T = float,
	std::enable_if<std::is_arithmetic_v<T>, T> * = nullptr
>
inline Vector2<T> operator*(T lhs, Vector2<T> rhs) {
	return Vector2(rhs.x * lhs, rhs.y * lhs);
}