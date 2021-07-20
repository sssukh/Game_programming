#pragma once
#include "MoveComponent.h"

class InputComponent : public MoveComponent
{
	InputComponent(class Actor* owner);

	void ProcessInput(const uint8_t* keyState) override;

	//private 변수에 접근하기 위한  getter / setter 함수들

private:
	// 최대 전방 속도 / 최대 각 속도
	float mMaxForwardSpeed;
	float mMaxAngularSpeed;
	// 전진 및 후진을 위한 키
	int mForwardKey;
	int mBackKey;
	// 각 운동을 위한 키
	int mClockwiseKey;
	int mCounterClockwiseKey;
};
