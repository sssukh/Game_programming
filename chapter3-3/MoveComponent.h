#pragma once
#include "Component.h"

class MoveComponent : public Component
{
public:
	//���� ������Ʈ �ǵ��� ���� �������� ����
	MoveComponent(class Actor* owner, int updateOrder = 10);

	void Update(float deltaTime) override;

	float GetAngularSpeed() const { return mAngularSpeed; }
	float GetForwardSpeed() const { return mForwardSpeed; }
	void SetAngularSpeed(float speed) { mAngularSpeed = speed; }
	void SetForwardSpeed(float speed) { mForwardSpeed = speed; }

	// ���� 3.3
	void AddForce(float power) { mForce = power; }
	void SetMass(float mass) { mMass = mass; }
private:
	// ȸ���� ����(�ʴ� ����)
	float mAngularSpeed;
	// ���� �̵��� ����(�ʴ� ����)
	float mForwardSpeed;
	float mMass;
	float mForce;
};
