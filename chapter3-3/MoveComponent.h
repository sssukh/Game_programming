#pragma once
#include "Component.h"

class MoveComponent : public Component
{
public:
	//먼저 업데이트 되도록 갱신 순서값을 낮춤
	MoveComponent(class Actor* owner, int updateOrder = 10);

	void Update(float deltaTime) override;

	float GetAngularSpeed() const { return mAngularSpeed; }
	float GetForwardSpeed() const { return mForwardSpeed; }
	void SetAngularSpeed(float speed) { mAngularSpeed = speed; }
	void SetForwardSpeed(float speed) { mForwardSpeed = speed; }

	// 연습 3.3
	void AddForce(float power) { mForce = power; }
	void SetMass(float mass) { mMass = mass; }
private:
	// 회전을 제어(초당 라디안)
	float mAngularSpeed;
	// 전방 이동을 제어(초당 단위)
	float mForwardSpeed;
	float mMass;
	float mForce;
};
