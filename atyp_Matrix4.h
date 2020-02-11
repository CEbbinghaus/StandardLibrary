#pragma once
#include "atyp_Vector4.h"
#include <memory>
#include <cmath>


class Matrix4
{

	float Get11() const { return data[0];	}
	float Get12() const { return data[4];	}
	float Get13() const { return data[8];	}
	float Get14() const { return data[12];	}
	float Get21() const { return data[1];	}
	float Get22() const { return data[5];	}
	float Get23() const { return data[9];	}
	float Get24() const { return data[13];	}
	float Get31() const { return data[2];	}
	float Get32() const { return data[6];	}
	float Get33() const { return data[10];	}
	float Get34() const { return data[14];	}
	float Get41() const { return data[3];	}
	float Get42() const { return data[7];	}
	float Get43() const { return data[11];	}
	float Get44() const { return data[15];	}
	void Set11(const float& val){ data[0]  = val; }
	void Set12(const float& val){ data[4]  = val; }
	void Set13(const float& val){ data[8]  = val; }
	void Set14(const float& val){ data[12] = val; }
	void Set21(const float& val){ data[1]  = val; }
	void Set22(const float& val){ data[5]  = val; }
	void Set23(const float& val){ data[9]  = val; }
	void Set24(const float& val){ data[13] = val; }
	void Set31(const float& val){ data[2]  = val; }
	void Set32(const float& val){ data[6]  = val; }
	void Set33(const float& val){ data[10] = val; }
	void Set34(const float& val){ data[14] = val; }
	void Set41(const float& val){ data[3]  = val; }
	void Set42(const float& val){ data[7]  = val; }
	void Set43(const float& val){ data[11] = val; }
	void Set44(const float& val){ data[15] = val; }
public:
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

	Matrix4& setScale(float x, float y, float z) {
		data[0] = x;
		data[5] = y;
		data[10] = z;
		return *this;
	}
	
	Matrix4& setScale(Vector3 scale) {
		data[0] = scale.x;
		data[5] = scale.y;
		data[10] = scale.z;
		return *this;
	}

	Matrix4& setPosition(float x, float y, float z) {
		data[12] = x;
		data[13] = y;
		data[14] = z;
		return *this;
	}
	
	Matrix4& setPosition(Vector3 position) {
		data[12] = position.x;
		data[13] = position.y;
		data[14] = position.z;
		return *this;
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

	static Matrix4 FromScale(Vector3 scale){
		return Matrix4().setScale(scale);
	}

	static Matrix4 FromPosition(Vector3 position){
		return Matrix4().setPosition(position);
	}

	static Matrix4 Projection(float fov, float aspect, float near_p, float far_p){
		Matrix4 m = Matrix4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

		float f = 1.0f / tan(fov / 2.0f);
		float nf = 1.0f / (near_p - far_p);
		m.data[0] = f / aspect;
		m.data[5] = f;
		m.data[10] = (far_p + near_p) * nf;
		m.data[11] = -1.0f;
		m.data[14] = 2.0f * far_p * near_p * nf;

		return m;
	}

	Matrix4 Invert(){
		Matrix4 inverse;
		inverse.Set11(
			Get22() * Get33() * Get44() -
			Get22() * Get34() * Get43() -
			Get32() * Get23() * Get44() +
			Get32() * Get24() * Get43() +
			Get42() * Get23() * Get34() -
			Get42() * Get24() * Get33()
		);

		inverse.Set21(
			-Get21() * Get33() * Get44() +
			Get21() * Get34() * Get43() +
			Get31() * Get23() * Get44() -
			Get31() * Get24() * Get43() -
			Get41() * Get23() * Get34() +
			Get41() * Get24() * Get33()
		);

		inverse.Set31(
			Get21() * Get32() * Get44() -
			Get21() * Get34() * Get42() -
			Get31() * Get22() * Get44() +
			Get31() * Get24() * Get42() +
			Get41() * Get22() * Get34() -
			Get41() * Get24() * Get32()
		);

		inverse.Set41(
			-Get21() * Get32() * Get43() 
			+Get21() * Get33() * Get42()
			+Get31() * Get22() * Get43()
			-Get31() * Get23() * Get42()
			-Get41() * Get22() * Get33()
			+Get41() * Get23() * Get32()
		);

		inverse.Set12(
			-Get12() * Get33() * Get44() +
			Get12() * Get34() * Get43() +
			Get32() * Get13() * Get44() -
			Get32() * Get14() * Get43() -
			Get42() * Get13() * Get34() +
			Get42() * Get14() * Get33()
		);

		inverse.Set22(
			Get11() * Get33() * Get44() -
			Get11() * Get34() * Get43() -
			Get31() * Get13() * Get44() +
			Get31() * Get14() * Get43() +
			Get41() * Get13() * Get34() -
			Get41() * Get14() * Get33()
		);

		inverse.Set32(
			-Get11() * Get32() * Get44() +
			Get11() * Get34() * Get42() +
			Get31() * Get12() * Get44() -
			Get31() * Get14() * Get42() -
			Get41() * Get12() * Get34() +
			Get41() * Get14() * Get32()
		);

		inverse.Set42(
			Get11() * Get32() * Get43() -
			Get11() * Get33() * Get42() -
			Get31() * Get12() * Get43() +
			Get31() * Get13() * Get42() +
			Get41() * Get12() * Get33() -
			Get41() * Get13() * Get32()
		);

		inverse.Set13(
			Get12() * Get23() * Get44() -
			Get12() * Get24() * Get43() -
			Get22() * Get13() * Get44() +
			Get22() * Get14() * Get43() +
			Get42() * Get13() * Get24() -
			Get42() * Get14() * Get23()
		);

		inverse.Set23(
			-Get11() * Get23() * Get44() +
			Get11() * Get24() * Get43() +
			Get21() * Get13() * Get44() -
			Get21() * Get14() * Get43() -
			Get41() * Get13() * Get24() +
			Get41() * Get14() * Get23()
		);

		inverse.Set33(
			Get11() * Get22() * Get44() -
			Get11() * Get24() * Get42() -
			Get21() * Get12() * Get44() +
			Get21() * Get14() * Get42() +
			Get41() * Get12() * Get24() -
			Get41() * Get14() * Get22()
		);

		inverse.Set43(
			-Get11() * Get22() * Get43() +
			Get11() * Get23() * Get42() +
			Get21() * Get12() * Get43() -
			Get21() * Get13() * Get42() -
			Get41() * Get12() * Get23() +
			Get41() * Get13() * Get22()
		);

		inverse.Set14(
			-Get12() * Get23() * Get34() +
			Get12() * Get24() * Get33() +
			Get22() * Get13() * Get34() -
			Get22() * Get14() * Get33() -
			Get32() * Get13() * Get24() +
			Get32() * Get14() * Get23()
		);

		inverse.Set24(
			Get11() * Get23() * Get34() -
			Get11() * Get24() * Get33() -
			Get21() * Get13() * Get34() +
			Get21() * Get14() * Get33() +
			Get31() * Get13() * Get24() -
			Get31() * Get14() * Get23()
		);

		inverse.Set34(
			-Get11() * Get22() * Get34() +
			Get11() * Get24() * Get32() +
			Get21() * Get12() * Get34() -
			Get21() * Get14() * Get32() -
			Get31() * Get12() * Get24() +
			Get31() * Get14() * Get22()
		);

		inverse.Set44(
			Get11() * Get22() * Get33() -
			Get11() * Get23() * Get32() -
			Get21() * Get12() * Get33() +
			Get21() * Get13() * Get32() +
			Get31() * Get12() * Get23() -
			Get31() * Get13() * Get22()
		);

		float determinant =
			Get11() * inverse.Get11() + Get12() * inverse.Get21() + Get13() * inverse.Get31() + Get14() * inverse.Get41();


		if (determinant == 0)
			return Matrix4();


		float determinantInverse = 1.0f / determinant;

		for (int i = 0; i < 16; i++)
		{
			inverse.data[i] *= determinantInverse;
		}

		return inverse;
	}
	void Print(){
		for(int i = 0; i < 16; ++i){
			if(i != 0 && (i % 4) == 0)printf("\n");
			printf("%.2f ", data[i]);
		}
		printf("\n");
	}

};