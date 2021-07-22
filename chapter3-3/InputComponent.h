#pragma once
#include "MoveComponent.h"
#include <cstdint>

class InputComponent : public MoveComponent
{
public:
	InputComponent(class Actor* owner);

	void ProcessInput(const uint8_t* keyState) override;

	//private ������ �����ϱ� ����  getter / setter �Լ���
	float GetMaxForward() const { return mMaxForwardSpeed; }
	float GetMaxAngular() const { return mMaxAngularSpeed; }
	int GetForwardKey() const { return mForwardKey; }
	int GetBackKey() const { return mBackKey; }
	int GetClockwiseKey() const { return mClockwiseKey; }
	int GetCounterClockwiseKey() const { return mCounterClockwiseKey; }

	void SetMaxForwardSpeed(float speed) { mMaxForwardSpeed = speed; }
	void SetMaxAngularSpeed(float speed) { mMaxAngularSpeed = speed; }
	void SetForwardKey(int key) { mForwardKey = key; }
	void SetBackKey(int key) { mBackKey = key; }
	void SetClockwiseKey(int key) { mClockwiseKey = key; }
	void SetCounterClockwiseKey(int key) { mCounterClockwiseKey = key; }

	// ���� 3.3
	void SetMaxForce(float force) { mMaxForce = force; }

private:
	// �ִ� ���� �ӵ� / �ִ� �� �ӵ�
	float mMaxForwardSpeed;
	float mMaxAngularSpeed;
	// ���� �� ������ ���� Ű
	int mForwardKey;
	int mBackKey;
	// �� ��� ���� Ű
	int mClockwiseKey;
	int mCounterClockwiseKey;

	// ���� 3.3
	float mMaxForce;
};
