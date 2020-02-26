#pragma once
#include "atyp_Vector3.h"
#include "atyp_Vector2.h"
#include <memory>

/*
	0, 3, 6
	1, 4, 7
	2, 5, 8
*/

class Matrix3
{
public:
	union{
		struct{
			Vector3 AxisX;
			Vector3 AxisY;
			Vector3 Pos;
		};
		float data[9];
	};


	Matrix3(){
		memset(data, 0, sizeof(float) * 9);
		data[0] = data[4] = data[8] = 1;
	}

	Matrix3(Vector3 XAx, Vector3 YAx, Vector3 PosAx){
		memcpy(data, &XAx, sizeof(float) * 3);
		memcpy(data + 3, &YAx, sizeof(float) * 3);
		memcpy(data + 6, &PosAx, sizeof(float) * 3);
	}

	Matrix3(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8){
		data[0] = m0;
		data[1] = m1;
		data[2] = m2;
		data[3] = m3;
		data[4] = m4;
		data[5] = m5;
		data[6] = m6;
		data[7] = m7;
		data[8] = m8;
	}

	Matrix3 operator*(const Matrix3& rhs){
		Matrix3 ret = Matrix3(
			rhs.data[0] * data[0] + rhs.data[1] * data[3] + rhs.data[2] * data[6],
			rhs.data[0] * data[1] + rhs.data[1] * data[4] + rhs.data[2] * data[7],
			rhs.data[0] * data[2] + rhs.data[1] * data[5] + rhs.data[2] * data[8],

			rhs.data[3] * data[0] + rhs.data[4] * data[3] + rhs.data[5] * data[6],
			rhs.data[3] * data[1] + rhs.data[4] * data[4] + rhs.data[5] * data[7],
			rhs.data[3] * data[2] + rhs.data[4] * data[5] + rhs.data[5] * data[8],

			rhs.data[6] * data[0] + rhs.data[7] * data[3] + rhs.data[8] * data[6],
			rhs.data[6] * data[1] + rhs.data[7] * data[4] + rhs.data[8] * data[7],
			rhs.data[6] * data[2] + rhs.data[7] * data[5] + rhs.data[8] * data[8]
		);
		return ret;
	}

	Vector3 operator*(const Vector3 & rhs){
		return Vector3(
			rhs.x * data[0] + rhs.y * data[3] + rhs.z * data[6],
			rhs.x * data[1] + rhs.y * data[4] + rhs.z * data[7],
			rhs.x * data[2] + rhs.y * data[5] + rhs.z * data[8]
		);
	}

	Vector3& operator[](int index){
		return *(Vector3*)(data + (index * 3));
	}

	operator float*(){
		return data;
	}


	void setPostion(float x, float y){
		Pos.x = x;
		Pos.y = y;
	}
	void setPostion(Vector2 pos){
		setScale(pos.x, pos.y);
	}

	void setScale(float x, float y){
		AxisX.x = x;
		AxisY.y = y;
	}

	void setScale(Vector2 a_scale){
		setScale(a_scale.x, a_scale.y);
	}

	void setRotateZ(float rot){
		float cos = cosf(rot);
		float sin = sinf(rot);
		data[0] = cos;
		data[3] = -sin;
		data[1] = sin;
		data[4] = cos;
	}

	void setRotateX(float rot){
		float cos = cosf(rot);
		float sin = sinf(rot);
		data[4] = cos;
		data[7] = -sin;
		data[5] = sin;
		data[8] = cos;
	}
	void setRotateY(float rot){
		float cos = cosf(rot);
		float sin = sinf(rot);
		data[0] = cos;
		data[6] = sin;
		data[2] = -sin;
		data[8] = cos;
	}

	Matrix3 Transposed(){
		return Matrix3(data[0], data[3], data[6],
					   data[1], data[4], data[7],
					   data[2], data[5], data[8]);
	}

	static Matrix3 Inverse(const Matrix3& v){
		Matrix3 inv;

		//	0, 3, 6
		//	1, 4, 7
		//	2, 5, 8

		//Calculate the matrix of minors
		 inv.data[0] = ((v.data[4] * v.data[8]) - (v.data[7] * v.data[5]));
		 inv.data[1] = ((v.data[3] * v.data[8]) - (v.data[6] * v.data[5]));
		 inv.data[2] = ((v.data[3] * v.data[7]) - (v.data[6] * v.data[4]));

		 inv.data[3] = ((v.data[1] * v.data[8]) - (v.data[7] * v.data[2]));
		 inv.data[4] = ((v.data[0] * v.data[8]) - (v.data[6] * v.data[2]));
		 inv.data[5] = ((v.data[0] * v.data[7]) - (v.data[6] * v.data[1]));

		 inv.data[6] = ((v.data[1] * v.data[5]) - (v.data[4] * v.data[2]));
		 inv.data[7] = ((v.data[0] * v.data[5]) - (v.data[3] * v.data[2]));
		 inv.data[8] = ((v.data[0] * v.data[4]) - (v.data[3] * v.data[1]));

		//Calculate the matrix of cofactors
		 inv.data[1] *= -1;
		 inv.data[3] *= -1;
		 inv.data[5] *= -1;
		 inv.data[7] *= -1;

		//Calculate the determinant
		float det = (v.data[0] *  inv.data[0]) + (v.data[3] *  inv.data[3]) + (v.data[6] *  inv.data[6]);
		if(det == 0.0f){
			return Matrix3();
		}

		//Calculate the adjugate of the matrix
		inv = inv.Transposed();

		//Multiply the adjugate and the determinant reciprocal
		float inverseDeterminant = (1 / det);

		for (int i = 0; i < 9; i++)
		{
			inv.data[i] *= inverseDeterminant;
		}

		return inv;
	}
};