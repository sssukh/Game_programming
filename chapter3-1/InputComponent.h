#pragma once
#include "MoveComponent.h"

class InputComponent : public MoveComponent
{
	InputComponent(class Actor* owner);

	void ProcessInput(const uint8_t* keyState) override;

	//private ������ �����ϱ� ����  getter / setter �Լ���

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
};
