#pragma once
#include <memory>
#include "atyp_Array.h"
#include "atyp_Vector3.h"
#include "atyp_Vector2.h"
#include "atyp_Matrix4.h"
#include "atyp_Quaternion.h"

class Transform{

public:
	void updateLocalTransform(){
		Matrix4 _pos;
		Matrix4 _scale;

		_pos.setPosition(Position.x, Position.y, Position.z);
		_scale.setScale(Scale.x, Scale.y, Scale.z);

		localTransform = _pos * Rotation * _scale;
	}

	void updateGlobalTransform(){
		updateLocalTransform();

		if(Parent)
			globalTransform = (Parent->globalTransform) * localTransform;
		else
			globalTransform = localTransform;
	}

	Matrix4 globalTransform;
	Matrix4 localTransform;

	static Transform* root;

	atyp::Array<Transform*> children;

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
		TransferParent(root);
	}

	Vector3 Position;
	Vector3 Scale;
	Quaternion Rotation;

	Transform(){
		Parent = nullptr;
		SetParent(nullptr);
		Position = Vector3(0.0f, 0.0f, 0.0f);
		Scale = Vector3(1.0f, 1.0f, 1.0f);
		Rotation = Quaternion();
	}

	Transform(Matrix4 src){
		Parent = nullptr;
		SetParent(nullptr);
		Position = Vector3(0.0f, 0.0f, 0.0f);
		Scale = Vector3(1.0f, 1.0f, 1.0f);
		Rotation = Quaternion();
		globalTransform = src;
	}


	Transform(Vector3 position, Vector3 scale, Quaternion rotation){
		Parent = nullptr;
		SetParent(nullptr);
		Position = position;
		Scale = scale;
		Rotation = rotation;
	}

	~Transform(){
		if(Parent)
			Parent->children.remove(this);
	}

	Transform operator*(Transform& other){
		return Transform(globalTransform * other.localTransform);
	}

	Matrix4 operator*(Matrix4& other){
		return Matrix4(globalTransform * other);
	}

	operator Matrix4(){
		return globalTransform;
	}
};

Matrix4 operator*(Matrix4& lhs, Transform& rhs){
	return Matrix4(lhs * rhs.globalTransform);
}

Transform* Transform::root = nullptr;
