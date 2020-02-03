#pragma once
#include <memory>


#include "atyp_Vector4.h"

/*
	0 4 8  12
	1 5 9  13
	2 6 10 14
	3 7 11 15
*/

struct Matrix4
{

	union{
		struct{
			Vector4 XAxis;
			Vector4 YAxis;
			Vector4 ZAxis;
			Vector4 Pos;
		};
		float data[4 * 4];
	};

	Matrix4() {
		memset(data, 0, sizeof(float) * 16);
		data[0] = data[5] = data[10] = data[15] = 1;
	}

	Matrix4(float m0, float m1, float m2, float m3,
			float m4, float m5, float m6, float m7,
			float m8, float m9, float m10, float m11,
			float m12, float m13, float m14, float m15) {

		data[0] = m0;
		data[1] = m1;
		data[2] = m2;
		data[3] = m3;
		data[4] = m4;
		data[5] = m5;
		data[6] = m6;
		data[7] = m7;
		data[8] = m8;
		data[9] = m9;
		data[10] = m10;
		data[11] = m11;
		data[12] = m12;
		data[13] = m13;
		data[14] = m14;
		data[15] = m15;
	}

	Matrix4 operator*(const Matrix4& rhs) {
		return Matrix4(
			data[0] * rhs.data[0] + data[4] * rhs.data[1] + data[8] * rhs.data[2] + data[12] * rhs.data[3],
			data[1] * rhs.data[0] + data[5] * rhs.data[1] + data[9] * rhs.data[2] + data[13] * rhs.data[3],
			data[2] * rhs.data[0] + data[6] * rhs.data[1] + data[10] * rhs.data[2] + data[14] * rhs.data[3],
			data[3] * rhs.data[0] + data[7] * rhs.data[1] + data[11] * rhs.data[2] + data[15] * rhs.data[3],

			data[0] * rhs.data[4] + data[4] * rhs.data[5] + data[8] * rhs.data[6] + data[12] * rhs.data[7],
			data[1] * rhs.data[4] + data[5] * rhs.data[5] + data[9] * rhs.data[6] + data[13] * rhs.data[7],
			data[2] * rhs.data[4] + data[6] * rhs.data[5] + data[10] * rhs.data[6] + data[14] * rhs.data[7],
			data[3] * rhs.data[4] + data[7] * rhs.data[5] + data[11] * rhs.data[6] + data[15] * rhs.data[7],

			data[0] * rhs.data[8] + data[4] * rhs.data[9] + data[8] * rhs.data[10] + data[12] * rhs.data[11],
			data[1] * rhs.data[8] + data[5] * rhs.data[9] + data[9] * rhs.data[10] + data[13] * rhs.data[11],
			data[2] * rhs.data[8] + data[6] * rhs.data[9] + data[10] * rhs.data[10] + data[14] * rhs.data[11],
			data[3] * rhs.data[8] + data[7] * rhs.data[9] + data[11] * rhs.data[10] + data[15] * rhs.data[11],

			data[0] * rhs.data[12] + data[4] * rhs.data[13] + data[8] * rhs.data[14] + data[12] * rhs.data[15],
			data[1] * rhs.data[12] + data[5] * rhs.data[13] + data[9] * rhs.data[14] + data[13] * rhs.data[15],
			data[2] * rhs.data[12] + data[6] * rhs.data[13] + data[10] * rhs.data[14] + data[14] * rhs.data[15],
			data[3] * rhs.data[12] + data[7] * rhs.data[13] + data[11] * rhs.data[14] + data[15] * rhs.data[15]
		);
	}

	Vector4 operator*(const Vector4& rhs) {
		return Vector4(
			rhs.x * data[0] + rhs.y * data[4] + rhs.z * data[8] + rhs.w * data[12],
			rhs.x * data[1] + rhs.y * data[5] + rhs.z * data[9] + rhs.w * data[13],
			rhs.x * data[2] + rhs.y * data[6] + rhs.z * data[10] + rhs.w * data[14],
			rhs.x * data[3] + rhs.y * data[7] + rhs.z * data[11] + rhs.w * data[15]
		);
	}


	Vector4& operator[](int index) {
		return *((Vector4*)(data + (index * 4)));
	}

	operator float* () {
		return (float*)this;
	}

	void setScale(float x, float y, float z) {
		data[0] = x;
		data[5] = y;
		data[10] = z;
	}

	void setPosition(float x, float y, float z) {
		data[12] = x;
		data[13] = y;
		data[14] = z;
	}

	void setRotateX(float radians) {
		float cos = cosf(radians);
		float sin = sinf(radians);
		data[5] = cos;
		data[6] = sin;
		data[9] = -sin;
		data[10] = cos;
	}
	void setRotateY(float radians) {
		float cos = cosf(radians);
		float sin = sinf(radians);
		data[0] = cos;
		data[8] = sin;
		data[2] = -sin;
		data[10] = cos;
	}

	void setRotateZ(float radians) {
		float cos = cosf(radians);
		float sin = sinf(radians);
		data[0] = cos;
		data[4] = -sin;
		data[1] = sin;
		data[5] = cos;
	}
};