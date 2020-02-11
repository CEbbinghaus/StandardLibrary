#pragma once
#include <memory>
#include "atyp_Array.h"
#include "atyp_Vector3.h"
#include "atyp_Vector2.h"
#include "atyp_Matrix4.h"
#include "atyp_Quaternion.h"

class Transform{

	Matrix4 globalMatrix;
	Matrix4 localMatrix;

public:

	const Matrix4& updateTransform(){
		Matrix4 _pos = Matrix4::FromPosition(Position);
		Matrix4 _scale = Matrix4::FromScale(Scale);

		localMatrix = _pos * Rotation * _scale;
		//localMatrix = _scale * Rotation * _pos;

		if(Parent)
			globalMatrix = (Parent->globalMatrix) * localMatrix;
		else
			globalMatrix = localMatrix;

		return globalMatrix;
	}

	//static Transform* root;

	Array<Transform*> children;

	Transform* Parent;

	void TransferParent(Transform* next){
		if(Parent)
			Parent->children.remove(this);

		Parent = next;

		if(Parent)
			Parent->children.push(this);
	}

	void SetParent(Transform* p){
		TransferParent(p);
	}

	void SetParent(std::nullptr_t){
		TransferParent(nullptr);
	}

	Vector3 Position;
	Vector3 Scale;
	Quaternion Rotation;

	Transform(){
		Parent = nullptr;
		Position = Vector3(0.0f, 0.0f, 0.0f);
		Scale = Vector3(1.0f, 1.0f, 1.0f);
		Rotation = Quaternion();
	}

	Transform(Matrix4 src){
		Parent = nullptr;
		Position = Vector3(0.0f, 0.0f, 0.0f);
		Scale = Vector3(1.0f, 1.0f, 1.0f);
		Rotation = Quaternion();

		//TODO: Read out Position/Rotation/Scale out of the Matrix;
		globalMatrix = src;
	}


	Transform(Vector3 position, Vector3 scale, Quaternion rotation){
		Parent = nullptr;
		Position = position;
		Scale = scale;
		Rotation = rotation;
	}

	~Transform(){
		if(Parent)
			Parent->children.remove(this);
	}

	Vector3 right() {
		return -globalMatrix.XAxis.normalise();
	}

	Vector3 up() {
		return -globalMatrix.YAxis.normalise();
	}

	Vector3 forward() {
		return -globalMatrix.ZAxis.normalise();
	}

	operator Matrix4(){
		return globalMatrix;
	}
};

//Transform* Transform::root = nullptr;
