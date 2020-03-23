#pragma once
#include <memory>
#include "atyp_Vector3.h"
#include "atyp_Matrix4.h"

class Quaternion
{
	union {
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
		float data[4];
	};

public:
	Quaternion()
	{
		*this = Quaternion::identity();
	}

	Quaternion(Vector3 src)
	{
		*this = Quaternion::euler(src);
	}

	Quaternion(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	~Quaternion() {}

	void Print(){
		printf("X: %.4f, Y: %.4f, Z: %.4f, W: %.4f\n", x, y, z, w);
	}

	static Quaternion identity()
	{
		return Quaternion(0, 0, 0, 1);
	}

	float magnitude()
	{
		return sqrtf(x * x + y * y + z * z + w * w);
	}

	Quaternion normalized()
	{
		float magnitude = this->magnitude();
		return Quaternion(x / magnitude, y / magnitude, z / magnitude, w / magnitude);
	}

	static Quaternion euler(float x, float y, float z)
	{
		float cy = cosf(z * 0.5f);
		float sy = sinf(z * 0.5f);

		float cp = cosf(y * 0.5f);
		float sp = sinf(y * 0.5f);

		float cr = cosf(x * 0.5f);
		float sr = sinf(x * 0.5f);

		return Quaternion(
				   cy * cp * sr - sy * sp * cr,
				   sy * cp * sr + cy * sp * cr,
				   sy * cp * cr - cy * sp * sr,
				   cy * cp * cr + sy * sp * sr)
			.normalized();
	}

	static Quaternion aroundAngle(Vector3 axis, float angle)
	{
		// Here we calculate the sin( theta / 2) once for optimization
		float factor = sinf((float)angle / 2.0f);

		// Calculate the x, y and z of the quaternion
		float x = axis.x * factor;
		float y = axis.y * factor;
		float z = axis.z * factor;

		// Calcualte the w value by cos( theta / 2 )
		float w = cosf((float)angle / 2.0f);

		return Quaternion(x, y, z, w).normalized();

	}
		//return Quaternion(
		//	direction.x * sin(rotation / 2),
		//	direction.y * sin(rotation / 2),
		//	direction.z * sin(rotation / 2),
		//	cos(rotation / 2));

	static Quaternion euler(Vector3 euler)
	{
		float x = euler.x;
		float y = euler.y;
		float z = euler.z;

		float cy = cosf(z * 0.5f);
		float sy = sinf(z * 0.5f);
		float cp = cosf(y * 0.5f);
		float sp = sinf(y * 0.5f);
		float cr = cosf(x * 0.5f);
		float sr = sinf(x * 0.5f);

		return Quaternion(
				   cy * cp * sr - sy * sp * cr,
				   sy * cp * sr + cy * sp * cr,
				   sy * cp * cr - cy * sp * sr,
				   cy * cp * cr + sy * sp * sr)
			.normalized();
	}

	Quaternion operator*(Quaternion b)
	{
		Quaternion a = *this;
		return Quaternion(
			a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z,
			a.w * b.x + a.x * b.w + a.y * b.z + a.z * b.y,
			a.w * b.y - a.x * b.z - a.y * b.w - a.z * b.x,
			a.w * b.z + a.x * b.y + a.y * b.x + a.z * b.w);
	}

	Quaternion& operator*=(Quaternion b)
	{
		Quaternion a = *this;

		this->x = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z;
		this->y = a.w * b.x + a.x * b.w + a.y * b.z + a.z * b.y;
		this->z = a.w * b.y - a.x * b.z - a.y * b.w - a.z * b.x;
		this->w = a.w * b.z + a.x * b.y + a.y * b.x + a.z * b.w;

		return *this;
	}

	Matrix4 toMatrix()
	{
		Quaternion q = *this;

		Matrix4 a = Matrix4(
			q.w, q.z, -q.y, q.x,
			-q.z, q.w, q.x, q.y,
			q.y, -q.x, q.w, q.z,
			-q.x, -q.y, -q.z, q.w
		);

		Matrix4 b = Matrix4(
			q.w, q.z, -q.y, -q.x,
			-q.z, q.w, q.x, -q.y,
			q.y, -q.x, q.w, -q.z,
			q.x, q.y, q.z, q.w
		);

		return a * b;
	}

	operator Matrix4()
	{
		return toMatrix();
	}

	Quaternion operator=(Vector3 &rhs)
	{
		return *this = Quaternion::euler(rhs);
	}
};