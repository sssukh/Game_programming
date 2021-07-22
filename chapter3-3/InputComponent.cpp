#include "InputComponent.h"
#include "Actor.h"

InputComponent::InputComponent(class Actor* owner)
	:MoveComponent(owner)
	, mForwardKey(0)
	, mBackKey(0)
	, mClockwiseKey(0)
	, mCounterClockwiseKey(0)
	, mMaxForce(0)
{}


void InputComponent::ProcessInput(const uint8_t* keyState)
{
	// MoveComponent �� ���� ���� �ӵ� ���
	//float forwardSpeed = 0.0f;
	float force = 0.0f;
	if (keyState[mForwardKey])
	{
		//forwardSpeed += mMaxForwardSpeed;

		force += mMaxForce;
	}
	if (keyState[mBackKey])
	{
		//forwardSpeed -= mMaxForwardSpeed;
		force -= mMaxForce;
	}
	//SetForwardSpeed(forwardSpeed);
	AddForce(force);

	// MoveComponent �� ���� �� �ӵ� ���
	float angularSpeed = 0.0f;
	if (keyState[mClockwiseKey])
	{
		angularSpeed += mMaxAngularSpeed;
	}
	if (keyState[mCounterClockwiseKey])
	{
		angularSpeed -= mMaxAngularSpeed;
	}
	SetAngularSpeed(angularSpeed);
}