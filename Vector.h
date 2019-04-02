#pragma once
#include<cmath>
#include "Array.h"

namespace CLib {
	enum VectorDimensions {
		x = 1,
		y = 2,
		z = 3,
		a = 4,
		b = 5,
		c = 6
	};
	template<int a, typename T>
	struct Vector {
		Array<T> data;

		Vector() {
			data = Array<T>(a);
		}
		//T operator[char index]{
		//}
		T operator[](int index){
			return data[index];
		};
		T operator[](VectorDimensions index){
			return data[index - 1];
		};

	/*	double dotProduct(Vector<T> other) {
			double res = 0;
			for (T& a : dimensions){
				res += other[]
			}
		}*/
	};
	template<typename T>
	struct Vector4 {
		static Vector4<T> zero;
		T x;
		T y;
		T z;
		T d;
		Vector4() {
			x = y = z = d = 0;
		}

		Vector4(T m_x, T m_y) {
			x = m_x;
			y = m_y;
			z = d = 0;
		}
		Vector4(T m_x, T m_y, T m_z) {
			x = m_x;
			y = m_y;
			z = m_z;
			d = 0;
		}
		Vector4(T m_x, T m_y, T m_z, T m_d) {
			x = m_x;
			y = m_y;
			z = m_z;
			d = m_z;
		}

		Vector4<T>& operator=(Vector4<T>& original) {
			x = original.x;
			y = original.y;
			z = original.z;
			d = original.d;
			return *this;
		}
		Vector4<T>& operator=(Vector4<T>&& original) {
			Vector4& a = original;
			return *this = a;
		}

		Vector4<T> operator *(Vector4<T>& v) {
			Vector4<T> result;
			result.x = x * v.x;
			result.y = y * v.y;
			result.z = z * v.z;
			result.d = d * v.d;
			return result;
		}

		double magnitude() {
			return std::sqrt(dotProduct());
		}

		double dotProduct(Vector4<T>& other) {
			return (x * other.x + y* other.y + z * other.z + d * other.d);
		}

		Vector4<T>& normalize() {
			double max = magnitude();
			x /= max;
			y /= max;
			z /= max;
			d /= max;
			return *this;
		}
	};

	template<typename T>
	struct Vector3 {
		T x;
		T y;
		T z;
	};
	
	template<typename T>
	struct Vector2 {
		T x;
		T y;
	};

	template<typename T>
	Vector4<T> Vector4<T>::zero(0, 0, 0, 0);

}